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
    double t_max = 15.0;

    std::vector<double> times;
    std::vector<double> heights;

    for (double t = 0.0; t <= t_max; t += dt)
    {
        times.push_back(t);
        heights.push_back(v0 * t - 0.5 * g * t * t);
    }

    if (heights.size() < 2)
    {
        std::cout << "Слишком мало данных.\n";
        return 0;
    }

    auto it = std::find_if(heights.begin() + 1, heights.end(), [](double h) { return h <= 0.0; });

    std::cout << std::fixed << std::setprecision(1);

    if (it == heights.end())
    {
        std::cout << "Падения не было в диапазоне до " << t_max << " с.\n";
    }
    else
    {
        size_t idx = std::distance(heights.begin(), it);
        double t_fall = times[idx];

        std::cout << "Момент падения: t = " << t_fall << " с\n";
        std::cout << "Высота в этот момент: " << heights[idx] << " м\n";
    }

    return 0;
}
