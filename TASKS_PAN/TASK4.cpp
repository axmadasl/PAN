//==========================================
// Задача 4 "Расчет времени набора высоты" 
// формула - h=0.5*a_y*t^2
//==========================================

#include <iostream>    
#include <cmath>
#include <clocale>
#include <iomanip>


double calculateTime(double h, double a_y)
{
    return std::sqrt(2.0 * h / a_y);
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

    std::cout << "=== Задача 4. Расчет времени набора высоты === \n";
    std::cout << "Формула - h = 0.5 * a_y * t^2\n\n";
    double h = readPositive("Высота h, м:             ");
    double a_y = readPositive("Ускорение a_y, м/с^2:    ");

    double t = calculateTime(h, a_y);
    std::cout << "\nВремя необходимое для набора высоты " << h << " м, равняется " << t << " c.\n";

}