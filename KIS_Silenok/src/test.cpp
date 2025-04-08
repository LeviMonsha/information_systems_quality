#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip> // std::fixed and std::setprecision

#ifdef _WIN32
#include <windows.h>
#endif

double mean(const std::vector<double> &data)
{
    if (data.empty())
        return 0.0;
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

std::vector<double> calculate_expected_frequencies(const std::vector<std::pair<double, double>> &intervals, double lambda, int N)
{
    std::vector<double> expected_frequencies(intervals.size(), 0.0);
    for (size_t i = 0; i < intervals.size(); ++i)
    {
        double left = intervals[i].first;
        double right = intervals[i].second;
        double prob = std::exp(-lambda * left) - std::exp(-lambda * right);
        expected_frequencies[i] = prob * N;
    }
    return expected_frequencies;
}

double calculate_chi_squared(const std::vector<int> &observed_frequencies, const std::vector<double> &expected_frequencies)
{
    double chi_squared = 0.0;
    for (size_t i = 0; i < observed_frequencies.size(); ++i)
    {
        if (expected_frequencies[i] > 0)
            chi_squared += std::pow(observed_frequencies[i] - expected_frequencies[i], 2) / expected_frequencies[i];
    }
    return chi_squared;
}

double calculate_p_value(double chi_squared, int degrees_of_freedom)
{
    double df = static_cast<double>(degrees_of_freedom);

    if (chi_squared < 0 || df <= 0)
    {
        std::cerr << "Error: Invalid input for p-value approximation." << std::endl;
        return 0.0;
    }

    double w = pow(chi_squared / df, 1.0 / 3.0);
    double approx = 1.0 - (w + (2.0 / (9.0 * df)) - 1) / (2.0 / (9.0 * df));

    return approx;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int N = 100;
    double interval_start = 0.0;
    double interval_end = 100.0;
    int K = 10;
    double ALPHA = 0.01;

    std::vector<std::pair<double, double>> intervals(K);
    double interval_width = (interval_end - interval_start) / K;
    for (int i = 0; i < K; ++i)
    {
        double left = interval_start + i * interval_width;
        double right = left + interval_width;
        intervals[i] = std::make_pair(left, right);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(interval_start, interval_end);

    std::vector<double> random_numbers(N);
    for (int i = 0; i < N; ++i)
        random_numbers[i] = distrib(gen);

    std::vector<int> observed_frequencies(K, 0);
    for (double num : random_numbers)
    {
        for (int j = 0; j < K; ++j)
        {
            if (num >= intervals[j].first && num < intervals[j].second)
            {
                observed_frequencies[j]++;
                break;
            }
            if (j == K - 1 && num >= intervals[j].first && num <= intervals[j].second)
            {
                observed_frequencies[j]++;
                break;
            }
        }
    }

    double mean_value = mean(random_numbers);
    double lambda = 1.0 / mean_value;

    std::vector<double> expected_frequencies = calculate_expected_frequencies(intervals, lambda, N);

    double chi_squared = calculate_chi_squared(observed_frequencies, expected_frequencies);

    int degrees_of_freedom = K - 2;

    double p_value = calculate_p_value(chi_squared, degrees_of_freedom);

    std::cout << "Chi-squared statistic = " << chi_squared << std::endl;
    std::cout << "Degrees of freedom = " << degrees_of_freedom << std::endl;
    std::cout << "p-value = " << p_value << std::endl;

    if (p_value >= 0.01)
        std::cout << "The hypothesis cannot be rejected" << std::endl;
    else
        std::cout << "The hypothesis is rejected" << std::endl;

    return 0;
}
