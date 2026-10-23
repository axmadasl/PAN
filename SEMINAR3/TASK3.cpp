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
    double t_max = 2 * v0 / g;

    std::vector<double> times;
    std::vector<double> velocities;

    for (double t = 0.0; t <= t_max; t += dt)
    {
        double v = v0 - g * t;

        times.push_back(t);
        velocities.push_back(v);
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(8) << "t, с" << std::setw(12) << "v, м/с" << "\n";

    for (size_t i = 0; i < times.size(); i++)
    {
        std::cout << std::setw(8) << times[i] << std::setw(12) << velocities[i] << "\n";
    }

    std::cout << std::setprecision(2);
    std::cout << "\nСкорость меняет знак в момент t = v0 / g = " << v0 / g << " с\n";

    return 0;
}
