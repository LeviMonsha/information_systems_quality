// #include <iostream>
// #include <vector>

// /*
// Лабораторная работа 2.
// КОЛИЧЕСТВЕННЫЕ ХАРАКТЕРИСТИКИ НАДЕЖНОСТИ
// */

// void exs1();
// void exs2();
// void exs3();

// int main()
// {
//     std::cout << "Quest 1" << std::endl;
//     exs1();

//     std::cout << "Quest 2" << std::endl;
//     exs2();

//     std::cout << "Quest 3" << std::endl;
//     exs3();
//     return 0;
// }

// /*
// 1. На испытание поставлено 1000 однотипных электронных приборов. За 3000 ч отказало 80 приборов.
// Требуется определить вероятность безотказной работы и вероятность отказа электронных приборов в течение 3000 ч.
// */
// void exs1()
// {
//     int count_units = 1000;
//     int ti1 = 3000;
//     int count_rejected_units = 80;

//     double p_uptime = (count_units - count_rejected_units) * 1. / count_units;
//     double p_unit_failure = 1 - p_uptime;

//     std::cout << "P uptime: " << p_uptime << std::endl;
//     std::cout << "P unit failure: " << p_unit_failure << std::endl;
// }

// /*
// 2. На испытание поставлено 1000 однотипных приборов.
// За первые 3000 ч работы отказало 80 приборов, а за интервал 3000– 4000 ч отказало еще 50 ламп.
// Определить частоту и интенсивность отказов электронных приборов в промежутке 3000–4000 ч работы
// */
// void exs2()
// {
//     int count_units = 1000;
//     int ti1 = 3000;
//     int count_rejected_units_ti1 = 80;

//     int ti2 = 4000;
//     int count_rejected_units_ti2 = 50;

//     double failure_frequency_units_ti12 = count_rejected_units_ti2 * 1. / (count_units * (ti2 - ti1));
//     double failure_intensity_units_ti12 = count_rejected_units_ti2 * 1. / ((ti2 - ti1) * (count_units - count_rejected_units_ti1));

//     std::cout << "failure frequency time interval 3000-4000 h: " << failure_frequency_units_ti12 << std::endl;
//     std::cout << "failure intensity time interval 3000-4000 h: " << failure_intensity_units_ti12 << std::endl;
// }

// /*
// 3. На испытании находилось 1000 образцов неремонтируемой аппаратуры.
// Число отказов n(∆t) фиксировалось через каждые 100 ч работы (∆t = 100 ч).
// Данные об отказах при- 18 ведены в табл.1.
// Требуется вычислить количественные характеристики и построить зависимость характеристик от времени.
// */
// void exs3()
// {
//     int N = 30;
//     int count_units = 1000;
//     int sep_t = 100;

//     std::vector<int> tis;
//     for (int i = 0; i <= 3000; i += sep_t)
//         tis.push_back(i);

//     std::vector<int> nds = {50, 40, 32, 25, 20, 17, 16, 16, 15, 14,
//                             15, 14, 14, 13, 14, 13, 13, 13, 14, 12,
//                             12, 13, 12, 13, 14, 16, 20, 25, 30, 40};

//     std::vector<int> ns;
//     std::vector<double> Ps;
//     std::vector<double> Qs;
//     std::vector<double> as;
//     std::vector<double> ns_mean;
//     std::vector<double> lambdas;

//     int cumulative_nds = 0;
//     // int decreasing_nds = count_units;

//     for (int i = 0; i < N; ++i)
//     {
//         cumulative_nds += nds[i];
//         ns.push_back(cumulative_nds + nds[i]);
//         Ps.push_back((count_units - ns[i]) * 1. / count_units);
//         Qs.push_back(1 - Ps[i]);
//         as.push_back(nds[i] * 1. / (count_units * sep_t));
//         ns_mean.push_back((count_units - ns[i] + count_units - (ns[i] - nds[i])) * 1. / 2);
//         lambdas.push_back(nds[i] * 1. / (sep_t * (count_units - (ns[i] - nds[i]))));

//         // decreasing_nds -= nds[i];
//     }

//     std::cout << "N\t" << "time\t\t" << "ns\t\t" << "Ps\t\t" << "Qs\t\t" << "as\t\t" << "ns_mean\t\t" << "lambdas" << std::endl;
//     for (int i = 0; i < N; ++i)
//         std::printf("%d\t%5d\t%10d\t%10.3lf\t%10.3lf\t%10.5lf\t%10.3lf\t%10.5lf\n", i, i * sep_t, ns[i], Ps[i], Qs[i], as[i], ns_mean[i], lambdas[i]);
// }

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Простой график SFML");

    // Пример точек графика (x, y)
    std::vector<sf::Vector2f> points = {
        {50.f, 500.f},
        {150.f, 400.f},
        {250.f, 300.f},
        {350.f, 350.f},
        {450.f, 200.f},
        {550.f, 250.f},
        {650.f, 150.f},
        {750.f, 100.f}};

    // Создаем VertexArray для линий графика
    sf::VertexArray graph(sf::LineStrip, points.size());
    for (size_t i = 0; i < points.size(); ++i)
    {
        graph[i].position = points[i];
        graph[i].color = sf::Color::Red;
    }

    // Создаем оси координат
    sf::VertexArray axes(sf::Lines, 4);
    // Ось X
    axes[0].position = sf::Vector2f(40.f, 550.f);
    axes[0].color = sf::Color::White;
    axes[1].position = sf::Vector2f(760.f, 550.f);
    axes[1].color = sf::Color::White;
    // Ось Y
    axes[2].position = sf::Vector2f(40.f, 550.f);
    axes[2].color = sf::Color::White;
    axes[3].position = sf::Vector2f(40.f, 50.f);
    axes[3].color = sf::Color::White;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::Black);

        // Рисуем оси
        window.draw(axes);

        // Рисуем график
        window.draw(graph);

        window.display();
    }

    return 0;
}
