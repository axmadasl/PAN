#include <iostream>
#include <iomanip>
#include <vector>
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Russian");

    double v0 = 50.0;
    double g = 9.8;
    double dt = 1.0;

    if (v0 <= 0)
    {
        std::cout << "Предупреждение: начальная скорость должна быть больше нуля, ракета не взлетит.\n";
        return 0;
    }

    std::vector<double> times;
    std::vector<double> heights;

    times.reserve((int)(v0 * 2 / g / dt));
    heights.reserve((int)(v0 * 2 / g / dt));

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

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(8) << "t, с" << std::setw(12) << "h, м" << "\n";

    for (size_t i = 0; i < times.size(); i++)
    {
        std::cout << std::setw(8) << times[i] << std::setw(12) << heights[i] << "\n";
    }

    return 0;
}