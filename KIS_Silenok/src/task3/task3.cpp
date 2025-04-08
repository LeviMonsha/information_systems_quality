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

class connection
{
private:
    /* data */
public:
    connection(/* args */);
    ~connection();
};

connection::connection(/* args */)
{
}

connection::~connection()
{
}

int main()
{
    std::vector<double> lambdas = {2.5, 2, 4, 0, 1.5, 2, 5, 3, 1.5, 2.5};

    return 0;
}
