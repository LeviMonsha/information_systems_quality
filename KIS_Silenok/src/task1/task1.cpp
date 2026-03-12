#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <boost/math/distributions/chi_squared.hpp>

/*
Лабораторная работа 1.
Определение закона распределения времени между отказами
*/

/*
Подтвердить или опровергнуть гипотезу о законе распределения случайной величины,
    используя критерий согласия Пирсона.
*/

double mean(const std::vector<double> &data);
std::vector<double> calculate_expected_frequencies(const std::vector<std::pair<double, double>> &intervals, double lambda, int N);
double calculate_chi_squared(const std::vector<int> &freq, const std::vector<double> &expected_freq);

int main()
{
    const int N = 100;
    const int K = 10;
    const double LAMBDA = 0.1;
    const double ALPHA = 0.01;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> distrib(ALPHA);

    std::vector<double> rand_nums(N);
    for (int i = 0; i < N; ++i)
        rand_nums[i] = distrib(gen);

    double max_value = *std::max_element(rand_nums.begin(), rand_nums.end());
    std::vector<std::pair<double, double>> intervals(K);
    double interval_width = max_value / K;
    for (int i = 0; i < K; ++i)
    {
        intervals[i] = {i * interval_width, (i + 1) * interval_width};
    }
    intervals.back().second = std::numeric_limits<double>::infinity();

    std::vector<int> freq(K, 0);
    for (double num : rand_nums)
    {
        for (int j = 0; j < K; ++j)
        {
            if (num >= intervals[j].first && num < intervals[j].second)
            {
                freq[j]++;
                break;
            }
            if (j == K - 1 && num >= intervals[j].first && num <= intervals[j].second)
            {
                freq[j]++;
                break;
            }
        }
    }

    double mean_value = mean(rand_nums);
    double lambda = 1.0 / mean_value;

    std::vector<double> expected_freq = calculate_expected_frequencies(intervals, lambda, N);

    double chi_squared = calculate_chi_squared(freq, expected_freq);

    int degrees_of_freedom = K - 2;

    boost::math::chi_squared dist(degrees_of_freedom);

    double p_value = boost::math::cdf(boost::math::complement(dist, chi_squared));

    std::cout << "Chi-squared = " << chi_squared << std::endl;
    std::cout << "Degrees of freedom = " << degrees_of_freedom << std::endl;
    std::cout << "p-value = " << p_value << std::endl;

    if (p_value >= ALPHA)
        std::cout << "The hypothesis cannot be rejected" << std::endl;
    else
        std::cout << "The hypothesis is rejected" << std::endl;

    return 0;
}

double mean(const std::vector<double> &data)
{
    if (data.empty())
        return 0.0;
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

std::vector<double> calculate_expected_frequencies(const std::vector<std::pair<double, double>> &intervals, double lambda, int N)
{
    std::vector<double> expected_freq(intervals.size());
    for (size_t i = 0; i < intervals.size(); ++i)
    {
        double left = intervals[i].first;
        double right = intervals[i].second;
        double prob = std::exp(-lambda * left) - (right == std::numeric_limits<double>::infinity() ? 0 : std::exp(-lambda * right));
        expected_freq[i] = prob * N;
    }
    return expected_freq;
}

double calculate_chi_squared(const std::vector<int> &freq, const std::vector<double> &expected_freq)
{
    double chi_squared = 0.0;
    for (size_t i = 0; i < freq.size(); ++i)
    {
        if (expected_freq[i] > 0)
            chi_squared += std::pow(freq[i] - expected_freq[i], 2) / expected_freq[i];
    }
    return chi_squared;
}
