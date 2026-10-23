#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Russian");

    double v0 = 50.0;
    double g = 9.8;
    double dt = 1.0;
    double t_max = 2 * v0 / g;

    std::vector<double> velocities;

    for (double t = 0.0; t <= t_max; t += dt)
    {
        velocities.push_back(v0 - g * t);
    }

    if (velocities.empty())
    {
        std::cout << "Вектор скоростей пуст.\n";
        return 0;
    }

    double sum = std::accumulate(velocities.begin(), velocities.end(), 0.0);
    double avg = sum / velocities.size();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Количество значений: " << velocities.size() << "\n";
    std::cout << "Сумма скоростей: " << sum << " м/с\n";
    std::cout << "Средняя скорость: " << avg << " м/с\n";

    return 0;
}
