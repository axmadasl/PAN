//==========================================
// Задача 9. Интерактивный расчёт аэродинамических характеристик
//   L   = 1/2 * rho * V^2 * S * C_L   
//   D   = 1/2 * rho * V^2 * S * C_D   
//   a   = (T - D) / m                 
//   a_y = (L - m*g) / m               
//==========================================

#include <iostream>
#include <iomanip>
#include <clocale>

const double G = 9.81;      
const int MAX_N = 10;       


struct Aircraft
{   
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


double calculateLift(double rho, double V, double S, double CL)
{
    return 0.5 * rho * V * V * S * CL;
}

double calculateDrag(double rho, double V, double S, double CD)
{
    return 0.5 * rho * V * V * S * CD;
}

double calculateAcceleration(double T, double D, double m)
{
    return (T - D) / m;
}

double calculateVerticalAcceleration(double L, double m)
{
    return (L - m * G) / m;
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

double readNonNegative(const char* prompt)
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
        else if (value < 0)
        {
            std::cout << "  Ошибка: значение не может быть отрицательным.\n";
        }
        else
        {
            return value;
        }
    }
}

int readIntInRange(const char* prompt, int minValue, int maxValue)
{
    int value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || std::cin.peek() != '\n')
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "  Ошибка: нужно ввести целое число. Попробуй ещё раз.\n";
        }
        else if (value < minValue || value > maxValue)
        {
            std::cout << "  Ошибка: число должно быть от " << minValue
                << " до " << maxValue << ".\n";
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

    std::cout << "=== Задача 9. Интерактивный расчёт аэродинамических характеристик ===\n\n";

    std::cout << "Условия полёта (общие для всех самолётов):\n";
    double V = readPositive("  Скорость V, м/с:                 ");
    double rho = readPositive("  Плотность воздуха rho, кг/м^3:   ");

    Aircraft planes[MAX_N];
    int N = readIntInRange("\nКоличество самолётов N (от 1 до 10): ", 1, MAX_N);

    for (int i = 0; i < N; i++)
    {
        std::cout << "\n--- Самолёт " << i + 1 << " ---\n";

        Aircraft& p = planes[i];   

        p.m = readPositive("  Масса m, кг:                     ");
        p.S = readPositive("  Площадь крыла S, м^2:            ");
        p.T = readNonNegative("  Тяга T, Н:                       ");
        p.CL = readPositive("  Коэффициент подъёмной силы C_L:  ");
        p.CD = readPositive("  Коэффициент сопротивления C_D:   ");

        p.L = calculateLift(rho, V, p.S, p.CL);
        p.D = calculateDrag(rho, V, p.S, p.CD);
        p.a = calculateAcceleration(p.T, p.D, p.m);
        p.ay = calculateVerticalAcceleration(p.L, p.m);
    }

    int leader = 0;
    for (int i = 1; i < N; i++)
    {
        if (planes[i].a > planes[leader].a)
        {
            leader = i;
        }
    }

    std::cout << std::fixed;
    std::cout << "\nРезультаты:\n";
    std::cout << "+-----+--------------+------------+------------+------------+\n";
    std::cout << "|  №  |         L, Н |       D, Н |   a, м/с^2 | a_y, м/с^2 |\n";
    std::cout << "+-----+--------------+------------+------------+------------+\n";

    for (int i = 0; i < N; i++)
    {
        std::cout << "| " << std::setw(3) << i + 1
            << " | " << std::setw(12) << std::setprecision(1) << planes[i].L
            << " | " << std::setw(10) << std::setprecision(1) << planes[i].D
            << " | " << std::setw(10) << std::setprecision(2) << planes[i].a
            << " | " << std::setw(10) << std::setprecision(2) << planes[i].ay
            << " |";

        if (i == leader)
            std::cout << "  <- лидер";

        std::cout << "\n";
    }
    std::cout << "+-----+--------------+------------+------------+------------+\n";

    std::cout << "\nНаибольшее ускорение у самолёта " << leader + 1
        << ": a = " << std::setprecision(2) << planes[leader].a << " м/с^2\n";

    return 0;
}