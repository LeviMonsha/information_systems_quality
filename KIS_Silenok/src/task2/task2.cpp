#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

/*
Лабораторная работа 2.
КОЛИЧЕСТВЕННЫЕ ХАРАКТЕРИСТИКИ НАДЕЖНОСТИ
*/

void exs1();
void exs2();

struct MiniGraph
{
    std::vector<double> x;
    std::vector<double> y;
    std::string title;
    sf::Color color;
};

void exs3();
void draw_mini_graph(const MiniGraph& graph, sf::RenderWindow& window, sf::FloatRect viewport);
void draw_graphs(const std::vector<MiniGraph>& graphs, sf::RenderWindow& window);

int main()
{
    std::cout << "Quest 1" << std::endl;
    exs1();

    std::cout << "Quest 2" << std::endl;
    exs2();

    std::cout << "Quest 3" << std::endl;
    exs3();
    
    return 0;
}

/*
1. На испытание поставлено 1000 однотипных электронных приборов. За 3000 ч отказало 80 приборов.
Требуется определить вероятность безотказной работы и вероятность отказа электронных приборов в течение 3000 ч.
*/
void exs1()
{
    int count_units = 1000;
    int ti1 = 3000;
    int count_rejected_units = 80;

    double p_uptime = (count_units - count_rejected_units) * 1. / count_units;
    double p_unit_failure = 1 - p_uptime;

    std::cout << "P uptime: " << p_uptime << std::endl;
    std::cout << "P unit failure: " << p_unit_failure << std::endl;
}

/*
2. На испытание поставлено 1000 однотипных приборов.
За первые 3000 ч работы отказало 80 приборов, а за интервал 3000– 4000 ч отказало еще 50 ламп.
Определить частоту и интенсивность отказов электронных приборов в промежутке 3000–4000 ч работы
*/
void exs2()
{
    int count_units = 1000;
    int ti1 = 3000;
    int count_rejected_units_ti1 = 80;

    int ti2 = 4000;
    int count_rejected_units_ti2 = 50;

    double failure_frequency_units_ti12 = count_rejected_units_ti2 * 1. / (count_units * (ti2 - ti1));
    double failure_intensity_units_ti12 = count_rejected_units_ti2 * 1. / ((ti2 - ti1) * (count_units - count_rejected_units_ti1));

    std::cout << "failure frequency time interval 3000-4000 h: " << failure_frequency_units_ti12 << std::endl;
    std::cout << "failure intensity time interval 3000-4000 h: " << failure_intensity_units_ti12 << std::endl;
}

/*
3. На испытании находилось 1000 образцов неремонтируемой аппаратуры.
Число отказов n(∆t) фиксировалось через каждые 100 ч работы (∆t = 100 ч).
Данные об отказах при- 18 ведены в табл.1.
Требуется вычислить количественные характеристики и построить зависимость характеристик от времени.
*/
void exs3()
{
    int N = 30;
    int count_units = 1000;
    int sep_t = 100;

    std::vector<int> tis;
    for (int i = 0; i <= 3000; i += sep_t)
        tis.push_back(i);

    std::vector<int> nds = {50, 40, 32, 25, 20, 17, 16, 16, 15, 14,
                            15, 14, 14, 13, 14, 13, 13, 13, 14, 12,
                            12, 13, 12, 13, 14, 16, 20, 25, 30, 40};

    std::vector<int> ns;
    std::vector<double> Ps;
    std::vector<double> Qs;
    std::vector<double> as;
    std::vector<double> ns_mean;
    std::vector<double> lambdas;
    std::vector<double> times;

    int cumulative_nds = 0;

    for (int i = 0; i < N; ++i)
    {
        cumulative_nds += nds[i];

        ns.push_back(cumulative_nds + nds[i]);
        Ps.push_back((count_units - ns[i]) * 1. / count_units);
        Qs.push_back(1 - Ps[i]);
        as.push_back(nds[i] * 1. / (count_units * sep_t));
        ns_mean.push_back((count_units - ns[i] + count_units - (ns[i] - nds[i])) * 1. / 2);
        lambdas.push_back(nds[i] * 1. / (sep_t * (count_units - (ns[i] - nds[i]))));
        times.push_back(i * sep_t);
    }

    std::cout << "N\t" << "time\t\t" << "ns\t\t" << "Ps\t\t" << "Qs\t\t" << "as\t\t" << "ns_mean\t\t" << "lambdas" << std::endl;
    for (int i = 0; i < N; ++i)
        std::printf("%d\t%5d\t%10d\t%10.3lf\t%10.3lf\t%10.5lf\t%10.3lf\t%10.5lf\n", i, times[i], ns[i], Ps[i], Qs[i], as[i], ns_mean[i], lambdas[i]);

    std::vector<MiniGraph> graphs;

    graphs.push_back({times, Ps, "Probability of uptime", sf::Color::Green});
    graphs.push_back({times, Qs, "Probability of failure", sf::Color::Blue});
    graphs.push_back({times, as, "Failure rate", sf::Color::Red});
    graphs.push_back({times, lambdas, "Bounce rate", sf::Color::Yellow});

    sf::RenderWindow window(sf::VideoMode(800, 600), "Main graph");

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        draw_graphs(graphs, window);
        window.display();
    }
}

void draw_mini_graph(const MiniGraph& graph, sf::RenderWindow& window, sf::FloatRect viewport)
{
    double max_x = *std::max_element(graph.x.begin(), graph.x.end());
    double max_y = *std::max_element(graph.y.begin(), graph.y.end());
    if (max_x == 0) max_x = 1;
    if (max_y == 0) max_y = 1;

    auto scaleX = [&](double val) {
        return viewport.left + (val / max_x) * viewport.width;
    };
    auto scaleY = [&](double val) {
        return viewport.top + viewport.height - (val / max_y) * viewport.height;
    };

    sf::VertexArray axes(sf::Lines, 4);
    axes[0].position = sf::Vector2f(viewport.left, viewport.top + viewport.height);
    axes[0].color = sf::Color::White;
    axes[1].position = sf::Vector2f(viewport.left + viewport.width, viewport.top + viewport.height);
    axes[1].color = sf::Color::White;
    axes[2].position = sf::Vector2f(viewport.left, viewport.top + viewport.height);
    axes[2].color = sf::Color::White;
    axes[3].position = sf::Vector2f(viewport.left, viewport.top);
    axes[3].color = sf::Color::White;

    window.draw(axes);

    sf::VertexArray line(sf::LineStrip, graph.x.size());
    for (size_t i = 0; i < graph.x.size(); ++i) {
        float px = static_cast<float>(scaleX(graph.x[i]));
        float py = static_cast<float>(scaleY(graph.y[i]));
        line[i] = sf::Vertex(sf::Vector2f(px, py), graph.color);
    }
    window.draw(line);
}

void draw_graphs(const std::vector<MiniGraph>& graphs, sf::RenderWindow& window)
{
    int total = (int)graphs.size();
    int cols = (int)std::ceil(std::sqrt(total));
    int rows = (int)std::ceil((float)total / cols);

    float win_width = (float)window.getSize().x;
    float win_height = (float)window.getSize().y;

    float cell_w = win_width / cols;
    float cell_h = win_height / rows;

    for (int i = 0; i < total; ++i) {
        int col = i % cols;
        int row = i / cols;

        sf::FloatRect viewport(col * cell_w, row * cell_h, cell_w, cell_h);

        draw_mini_graph(graphs[i], window, viewport);
    }
}