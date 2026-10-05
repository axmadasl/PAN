//==========================================
// Задача 8. Время набора высоты для нескольких самолётов
//   L   = 1/2 * rho * V^2 * S * C_L   
//   a_y = (L - m*g) / m               
//   t   = sqrt(2h / a_y)             
//==========================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>
#include <string>
#include <utility>    

const double G = 9.81;    
const double RHO = 1.225;   
const double V = 70.0;    

struct Aircraft
{
    std::string name;   
    double m;           
    double S;           
    double T;           
    double CL;          
    double CD;          

    double L = 0;           
    double ay = 0;           
    double t = 0;           
    bool canClimb = false;   
};


double calculateLift(double rho, double v, double S, double CL)
{
    return 0.5 * rho * v * v * S * CL;
}

double calculateVerticalAcceleration(double L, double m)
{
    return (L - m * G) / m;
}

double calculateClimbTime(double h, double ay)
{
    return std::sqrt(2.0 * h / ay);
}

double readPositive(const char* prompt)
{
    double value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "  Ошибка: нужно ввести число. Попробуй ещё раз.\n";
        }
        else if (value <= 0)
        {
            std::cout << "  Ошибка: значение должно быть больше нуля.\n";
        }
        else
        {
            return value;
        }
    }
}

bool shouldSwap(const Aircraft& left, const Aircraft& right)
{
    if (!left.canClimb && right.canClimb)   
        return true;

    if (left.canClimb && right.canClimb && left.t > right.t)   
        return true;

    return false;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed;

    const int N = 5;
    Aircraft planes[N] =
    {
        //  название       m, кг   S, м^2  T, Н     C_L   C_D
        { "Самолёт А",     5000,   30,     15000,   0.60, 0.040 },
        { "Самолёт Б",     8000,   40,     20000,   0.70, 0.050 },
        { "Самолёт В",    12000,   45,     30000,   0.80, 0.060 },
        { "Самолёт Г",     3000,   20,      9000,   0.55, 0.035 },
        { "Самолёт Д",    10000,   52,     25000,   0.70, 0.050 }
    };

    std::cout << "=== Задача 8. Время набора высоты для нескольких самолётов ===\n";
    std::cout << "Условия полёта: V = " << std::setprecision(1) << V << " м/с, rho = "
        << std::setprecision(3) << RHO << " кг/м^3\n\n";

    std::cout << "Исходные данные:\n";
    std::cout << "+-----------+---------+--------+---------+-------+-------+\n";
    std::cout << "| Самолёт   |   m, кг | S, м^2 |    T, Н |   C_L |   C_D |\n";
    std::cout << "+-----------+---------+--------+---------+-------+-------+\n";
    for (int i = 0; i < N; i++)
    {
        std::cout << "| " << planes[i].name
            << " | " << std::setw(7) << std::setprecision(0) << planes[i].m
            << " | " << std::setw(6) << std::setprecision(0) << planes[i].S
            << " | " << std::setw(7) << std::setprecision(0) << planes[i].T
            << " | " << std::setw(5) << std::setprecision(2) << planes[i].CL
            << " | " << std::setw(5) << std::setprecision(3) << planes[i].CD
            << " |\n";
    }
    std::cout << "+-----------+---------+--------+---------+-------+-------+\n\n";

    double h = readPositive("Высота, которую нужно набрать h, м: ");

    for (int i = 0; i < N; i++)
    {
        Aircraft& p = planes[i];   

        p.L = calculateLift(RHO, V, p.S, p.CL);
        p.ay = calculateVerticalAcceleration(p.L, p.m);

        if (p.ay > 0)
        {
            p.canClimb = true;
            p.t = calculateClimbTime(h, p.ay);
        }
        else
        {
            p.canClimb = false;
        }
    }

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (shouldSwap(planes[j], planes[j + 1]))
            {
                std::swap(planes[j], planes[j + 1]);   
            }
        }
    }

    std::cout << "\nРезультаты (по возрастанию времени набора " << std::setprecision(0) << h << " м):\n";
    std::cout << "+-------+-----------+------------+------------+\n";
    std::cout << "| Место | Самолёт   | a_y, м/с^2 |       t, с |\n";
    std::cout << "+-------+-----------+------------+------------+\n";

    for (int i = 0; i < N; i++)
    {
        const Aircraft& p = planes[i];

        if (p.canClimb)
        {
            std::cout << "| " << std::setw(5) << i + 1
                << " | " << p.name
                << " | " << std::setw(10) << std::setprecision(2) << p.ay
                << " | " << std::setw(10) << std::setprecision(2) << p.t
                << " |\n";
        }
        else
        {      
            std::cout << "|     - | " << p.name
                << " | " << std::setw(10) << std::setprecision(2) << p.ay
                << " | не наберёт |\n";
        }
    }
    std::cout << "+-------+-----------+------------+------------+\n";

    if (planes[0].canClimb)
    {
        std::cout << "\nБыстрее всех высоту наберёт " << planes[0].name
            << ": за " << std::setprecision(2) << planes[0].t << " с.\n";
    }
    else
    {
        std::cout << "\nНи один самолёт не может набрать высоту при этих условиях.\n";
    }

    return 0;
}