//==========================================
// Задача 5. Сравнение нескольких конфигураций ЛА
//
// Для каждого из трёх самолётов считаем:
//   L   = 1/2 * rho * V^2 * S * C_L   — подъёмная сила
//   D   = 1/2 * rho * V^2 * S * C_D   — сопротивление
//   a   = (T - D) / m                 — ускорение вдоль траектории
//   a_y = (L - m*g) / m               — вертикальное ускорение
//   t   = sqrt(2h / a_y)              — время набора высоты h
//==========================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>
#include <string>     

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
    double D = 0;      
    double a = 0;      
    double ay = 0;      
};


double calculateLift(double rho, double v, double S, double CL)
{
    return 0.5 * rho * v * v * S * CL;
}

double calculateDrag(double rho, double v, double S, double CD)
{
    return 0.5 * rho * v * v * S * CD;
}

double calculateAcceleration(double T, double D, double m)
{
    return (T - D) / m;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "=== Задача 5. Сравнение конфигураций ЛА ===\n";
    std::cout << "Условия полёта: V = " << V << " м/с, rho = "
        << std::setprecision(3) << RHO << std::setprecision(2)   
        << " кг/м^3\n\n";

    const int N = 3;
    Aircraft planes[N] =
    {
        { "Самолёт А",     5000,   30,     15000,   0.6,  0.04 },
        { "Самолёт Б",     8000,   40,     20000,   0.7,  0.05 },
        { "Самолёт В",    12000,   45,     30000,   0.8,  0.06 }
    };

    double h = readPositive("Высота, которую нужно набрать h, м: ");

    int bestIndex = -1;
    double bestTime = 0;

    for (int i = 0; i < N; i++)
    {
        Aircraft& p = planes[i];

        p.L = calculateLift(RHO, V, p.S, p.CL);
        p.D = calculateDrag(RHO, V, p.S, p.CD);
        p.a = calculateAcceleration(p.T, p.D, p.m);
        p.ay = calculateVerticalAcceleration(p.L, p.m);

        std::cout << "\n--- " << p.name << " ---\n";
        std::cout << "  m = " << p.m << " кг, S = " << p.S << " м^2, T = " << p.T
            << " Н, C_L = " << p.CL << ", C_D = " << p.CD << "\n";
        std::cout << "  Подъёмная сила        L   = " << p.L << " Н\n";
        std::cout << "  Сопротивление         D   = " << p.D << " Н\n";
        std::cout << "  Ускорение             a   = " << p.a << " м/с^2\n";
        std::cout << "  Вертикальное ускор.   a_y = " << p.ay << " м/с^2\n";

        if (p.ay > 0)
        {
            double t = calculateClimbTime(h, p.ay);
            std::cout << "  Время набора высоты   t   = " << t << " с\n";

            if (bestIndex == -1 || t < bestTime)
            {
                bestIndex = i;
                bestTime = t;
            }
        }
        else
        {
            std::cout << "  \nПодъёмная сила меньше веса — набрать высоту не может.\n";
        }
    }

    if (bestIndex == -1)
    {
        std::cout << "\nНи один самолёт не может набрать высоту при этих условиях.\n";
    }
    else
    {
        std::cout << "\nБыстрее всех высоту " << h << " м наберёт "
            << planes[bestIndex].name << ": за " << bestTime << " с.\n";
    }

    return 0;
}