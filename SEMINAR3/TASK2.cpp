#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Russian");

    double v0 = 50.0;
    double g = 9.8;
    double dt = 1.0;

    std::vector<double> times;
    std::vector<double> heights;

    for (double t = 0.0; t <= 1000; t += dt)
    {
        double h = v0 * t - 0.5 * g * t * t;

        if (h < 0)
        {
            break;
        }

        times.push_back(t);
        heights.push_back(h);
    }

    if (heights.empty())
    {
        std::cout << "Данных нет.\n";
        return 0;
    }

    size_t idx_max = 0;
    for (size_t i = 1; i < heights.size(); ++i)
    {
        if (heights[i] > heights[idx_max])
        {
            idx_max = i;
        }
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Через цикл:\n";
    std::cout << "  Максимальная высота: " << heights[idx_max] << " м\n";
    std::cout << "  Время: " << times[idx_max] << " с\n";

    auto it = std::max_element(heights.begin(), heights.end());
    size_t idx = std::distance(heights.begin(), it);

    std::cout << "Через max_element:\n";
    std::cout << "  Максимальная высота: " << heights[idx] << " м\n";
    std::cout << "  Время: " << times[idx] << " с\n";

    std::vector<double> plateau = { 1.0, 5.0, 5.0, 3.0 };

    size_t idx_plateau = 0;
    for (size_t i = 1; i < plateau.size(); ++i)
    {
        if (plateau[i] > plateau[idx_plateau])
        {
            idx_plateau = i;
        }
    }

    std::cout << "\nТест на плато {1, 5, 5, 3}: индекс максимума = " << idx_plateau << "\n";

    return 0;
}
