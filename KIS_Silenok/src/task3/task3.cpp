#include <iostream>
#include <cmath>
#include <vector>

/*
Лабораторная работа 3.
Расчёт надёжности невосстанавливаемых сложных систем с использованием различных методов.
*/

/*
Вариант 9.
*/

#define ACCURACY pow(10, -4)
#define TIME_WORK_SYSTEM 9
#define TIME_TO_RECOVERY 680

class Connection
{
public:
    std::vector<double> elements;

    Connection(std::vector<double> elements) : elements(elements) {}

    std::vector<double> prob_of_not_failure(double t)
    {
        std::vector<double> not_failure(elements.size());
        for (size_t i = 0; i < elements.size(); ++i)
        {
            not_failure[i] = exp(-elements[i] * t);
        }
        return not_failure;
    }

    std::vector<double> prob_of_failure(double t)
    {
        std::vector<double> not_failure = prob_of_not_failure(t);
        std::vector<double> failure(not_failure.size());
        for (size_t i = 0; i < not_failure.size(); ++i)
        {
            failure[i] = 1 - not_failure[i];
        }
        return failure;
    }
};

double mean_time_to_failure_system(const std::vector<Connection> &connections);
double calculate_system_reliability(const std::vector<Connection> &connections, double time, bool use_failure_prob);

void m_minimal_paths(std::vector<double> lbs);
void m_minimal_sections(std::vector<double> lbs);
void m_decomposition_relative(std::vector<double> lbs);

int main()
{
    std::vector<double> lambdas = {2.5, 2, 4, 0, 1.5, 2, 5, 3, 1.5, 2.5};
    for (int i = 0; i < lambdas.size(); ++i)
        lambdas[i] *= ACCURACY;

    m_minimal_paths(lambdas);
    m_minimal_sections(lambdas);
    m_decomposition_relative(lambdas);

    return 0;
}

double mean_time_to_failure_system(const std::vector<Connection> &connections)
{
    double sum_lambda = 0;
    for (const auto &connection : connections)
    {
        for (double element : connection.elements)
            sum_lambda += element;
    }
    double mtbf_system = 1 / sum_lambda + TIME_TO_RECOVERY;
    return mtbf_system;
}

double calculate_system_reliability(const std::vector<Connection> &connections, double time, bool use_failure_prob)
{
    double system_probability = 1.0;
    for (Connection connection : connections)
    {
        std::vector<double> element_probabilities;
        if (use_failure_prob)
            element_probabilities = connection.prob_of_failure(time);
        else
            element_probabilities = connection.prob_of_not_failure(time);

        double connection_probability = 1.0;
        for (double prob : element_probabilities)
            connection_probability *= prob;

        if (use_failure_prob)
            system_probability *= (1 - connection_probability);

        else
            system_probability *= (1 - connection_probability);
    }
    if (!use_failure_prob)
        system_probability = 1 - system_probability;

    return system_probability;
}

// Метод минимальных путей
void m_minimal_paths(std::vector<double> lbs)
{
    std::cout << "Method minimal paths" << std::endl;

    Connection min_path_1_3_5_7({lbs[0], lbs[2], lbs[4], lbs[6]});
    Connection min_path_2_3_4_7({lbs[1], lbs[2], lbs[3], lbs[6]});
    Connection min_path_1_4_7({lbs[0], lbs[3], lbs[6]});
    Connection min_path_2_5_7({lbs[1], lbs[4], lbs[6]});

    std::vector<Connection> paths = {min_path_1_3_5_7, min_path_2_3_4_7, min_path_1_4_7, min_path_2_5_7};
    double prob_work_system_paths = calculate_system_reliability(paths, TIME_WORK_SYSTEM, false);
    std::cout << "The probability of uptime of the system: " << prob_work_system_paths << std::endl;
    double mean_time_of_failure_paths = mean_time_to_failure_system(paths);
    std::cout << "Average operating time before failure: " << mean_time_of_failure_paths << std::endl;
}

// Метод минимальных сечений
void m_minimal_sections(std::vector<double> lbs)
{
    std::cout << "Method minimal sections" << std::endl;

    Connection min_section_1_2({lbs[0], lbs[1]});
    Connection min_section_7({lbs[6]});
    Connection min_section_3_4({lbs[2], lbs[3]});
    Connection min_section_5_6({lbs[4], lbs[5]});

    std::vector<Connection> sections = {min_section_1_2, min_section_7, min_section_3_4, min_section_5_6};
    double prob_work_system_sections = 1 - calculate_system_reliability(sections, TIME_WORK_SYSTEM, true);
    std::cout << "The probability of uptime of the system: " << prob_work_system_sections << std::endl;
    double mean_time_of_failure_sections = mean_time_to_failure_system(sections);
    std::cout << "Average operating time before failure: " << mean_time_of_failure_sections << std::endl;
}

// Метод разложения относительно особого элемента
void m_decomposition_relative(std::vector<double> lbs)
{
    std::cout << "Method decomposition relative" << std::endl;

    Connection min_path_1_3_5_7({lbs[0], lbs[2], lbs[4], lbs[6]});
    Connection min_path_2_3_4_7({lbs[1], lbs[2], lbs[3], lbs[6]});
    Connection min_path_1_4_7({lbs[0], lbs[3], lbs[6]});
    Connection min_path_2_5_7({lbs[1], lbs[4], lbs[6]});

    double q6 = 1 - exp(-lbs[5] * TIME_WORK_SYSTEM);
    std::vector<Connection> paths_selected_item_6 = {min_path_1_3_5_7, min_path_2_3_4_7, min_path_1_4_7, min_path_2_5_7};
    double prob_work_system_paths_q6 = calculate_system_reliability(paths_selected_item_6, TIME_WORK_SYSTEM, false);
    double prob_work_system_paths_with_q6 = (1 - prob_work_system_paths_q6) * q6;

    double p6 = exp(-lbs[5] * TIME_WORK_SYSTEM);
    Connection min_section_1_2_selected({lbs[0], lbs[1]});
    Connection min_section_7_selected({lbs[6]});
    Connection min_section_3_4_selected({lbs[2], lbs[3]});

    std::vector<Connection> sections_selected_item_6 = {min_section_1_2_selected, min_section_7_selected, min_section_3_4_selected};
    double prob_work_system_sections_p6 = 1 - calculate_system_reliability(sections_selected_item_6, TIME_WORK_SYSTEM, true);
    double prob_work_system_sections_with_p6 = prob_work_system_sections_p6 * p6;

    double prob_work = prob_work_system_sections_with_p6 + prob_work_system_paths_with_q6;
    std::cout << "The probability of uptime of the system: " << prob_work << std::endl;
    double mean_time_of_failure_sections_item_6 = mean_time_to_failure_system(sections_selected_item_6);
    double mean_time_of_failure_paths_item_6 = mean_time_to_failure_system(paths_selected_item_6);
    std::cout << "Average operating time before failure: " << (mean_time_of_failure_paths_item_6 + mean_time_of_failure_sections_item_6) / 2 << std::endl;
}