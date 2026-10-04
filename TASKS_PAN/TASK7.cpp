//==========================================
// Задача 7. Автоматический выбор режима полёта
//==========================================

#include <iostream>
#include <iomanip>
#include <clocale>
#include <cmath>      

const double G = 9.81;              
const double lim = 0.5;     


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

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "=== Задача 7. Автоматический выбор режима полёта ===\n\n";

    double m = readPositive("Масса самолёта m, кг:     ");
    double T = readNonNegative("Тяга двигателя T, Н:      ");
    double L = readNonNegative("Подъёмная сила L, Н:      ");
    double D = readNonNegative("Сопротивление D, Н:       ");

    double a = calculateAcceleration(T, D, m);
    double ay = calculateVerticalAcceleration(L, m);

    std::cout << "\nУскорение вдоль траектории a   = " << a << " м/с^2\n";
    std::cout << "Вертикальное ускорение     a_y = " << ay << " м/с^2\n\n";

    if (ay > lim)
    {
        std::cout << "Режим полёта: НАБОР ВЫСОТЫ\n";
        std::cout << "  (вертикальное ускорение больше " << lim << " м/с^2)\n";
    }
    else if (ay >= 0)
    {
        std::cout << "Режим полёта: ГОРИЗОНТАЛЬНЫЙ ПОЛЁТ\n";
        std::cout << "  (вертикальное ускорение от 0 до " << lim << " м/с^2)\n";
    }
    else
    {
        std::cout << "Режим полёта: СНИЖЕНИЕ\n";
        std::cout << "  (вертикальное ускорение отрицательное — подъёмная сила меньше веса)\n";
    }


    return 0;
}