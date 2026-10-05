//==========================================
// Задача 10. Минимизация времени набора высоты
//==========================================

#include <iostream>
#include <iomanip>
#include <cmath>      
#include <clocale>

const double G = 9.81;               
const double PI = 3.14159265358979;   

const double M = 5500.0;   
const double S = 30.0;     
const double CL = 0.6;      
const double CD = 0.04;     
const double V = 70.0;     
const double RHO = 1.225;    
const double THETA_DEG = 10.0;     

double calculateLift(double rho, double v, double S, double CL)
{
    return 0.5 * rho * v * v * S * CL;
}

double calculateDrag(double rho, double v, double S, double CD)
{
    return 0.5 * rho * v * v * S * CD;
}

// Вертикальное ускорение при наборе высоты под углом theta (в радианах)
double calculateVerticalAcceleration(double L, double T, double D, double m, double theta)
{
    return (L * std::cos(theta) + (T - D) * std::sin(theta) - m * G) / m;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed;

    double L = calculateLift(RHO, V, S, CL);
    double D = calculateDrag(RHO, V, S, CD);
    double theta = THETA_DEG * PI / 180.0;   

    std::cout << "=== Задача 10. Минимизация времени набора высоты ===\n";
    std::cout << "Самолёт: m = " << std::setprecision(0) << M << " кг, S = " << S
        << " м^2, C_L = " << std::setprecision(2) << CL << ", C_D = " << CD << "\n";
    std::cout << "Полёт:   V = " << std::setprecision(0) << V << " м/с, rho = "
        << std::setprecision(3) << RHO << " кг/м^3, угол набора = "
        << std::setprecision(0) << THETA_DEG << " град\n";
    std::cout << "L = " << std::setprecision(1) << L << " Н, D = " << D << " Н\n\n";

    double Tmin = readNonNegative("Минимальная тяга T_min, Н:  ");

    double Tmax = readNonNegative("Максимальная тяга T_max, Н: ");
    while (Tmax < Tmin)
    {
        std::cout << "  Ошибка: T_max не может быть меньше T_min.\n";
        Tmax = readNonNegative("Максимальная тяга T_max, Н: ");
    }

    double dT = readPositive("Шаг тяги dT, Н:             ");
    while ((Tmax - Tmin) / dT > 1000)   
    {
        std::cout << "  Ошибка: слишком мелкий шаг (больше 1000 значений). Возьми шаг крупнее.\n";
        dT = readPositive("Шаг тяги dT, Н:             ");
    }

    double h = readPositive("Высота h, м:                ");

    int steps = (int)((Tmax - Tmin) / dT + 1e-9);

    
    bool found = false;     
    double bestT = 0;       
    double bestTime = 0;    

    std::cout << "\n+------------+------------+------------+\n";
    std::cout << "|       T, Н | a_y, м/с^2 |       t, с |\n";
    std::cout << "+------------+------------+------------+\n";

    for (int i = 0; i <= steps; i++)
    {
        double T = Tmin + i * dT;
        double ay = calculateVerticalAcceleration(L, T, D, M, theta);

        std::cout << "| " << std::setw(10) << std::setprecision(0) << T
            << " | " << std::setw(10) << std::setprecision(3) << ay << " | ";

        if (ay > 0)
        {
            double t = calculateClimbTime(h, ay);
            std::cout << std::setw(10) << std::setprecision(2) << t << " |\n";

            if (!found || t < bestTime)
            {
                found = true;
                bestT = T;
                bestTime = t;
            }
        }
        else
        {
            std::cout << "не наберёт |\n";
        }
    }
    std::cout << "+------------+------------+------------+\n";

    if (found)
    {
        std::cout << "\nОптимальная тяга: T = " << std::setprecision(0) << bestT << " Н\n";
        std::cout << "Минимальное время набора " << h << " м: t = "
            << std::setprecision(2) << bestTime << " с\n";
    }
    else
    {
        std::cout << "\nНи при одном значении тяги из диапазона самолёт не набирает высоту.\n";
    }

    return 0;
}