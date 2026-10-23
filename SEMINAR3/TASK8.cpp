#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <clocale>

void simulate(double v0, std::vector<double>& times, std::vector<double>& heights)
{
    double g = 9.8;
    double dt = 1.0;
    double t_max = 20.0;

    for (double t = 0.0; t <= t_max; t += dt)
    {
        times.push_back(t);
        heights.push_back(v0 * t - 0.5 * g * t * t);
    }
}

double findFall(const std::vector<double>& times, const std::vector<double>& heights)
{
    auto it = std::find_if(heights.begin() + 1, heights.end(), [](double h) { return h <= 0.0; });

    if (it == heights.end())
    {
        return -1.0;
    }

    size_t idx = std::distance(heights.begin(), it);
    return times[idx];
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<double> times1, heights1;
    std::vector<double> times2, heights2;

    simulate(50.0, times1, heights1);
    simulate(40.0, times2, heights2);

    auto it1 = std::max_element(heights1.begin(), heights1.end());
    double max1 = *it1;
    size_t idx_max1 = std::distance(heights1.begin(), it1);
    double t_max1 = times1[idx_max1];
    double t_fall1 = findFall(times1, heights1);

    auto it2 = std::max_element(heights2.begin(), heights2.end());
    double max2 = *it2;
    size_t idx_max2 = std::distance(heights2.begin(), it2);
    double t_max2 = times2[idx_max2];
    double t_fall2 = findFall(times2, heights2);

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(8) << "Ракета" << std::setw(14) << "max_height" << std::setw(14) << "time_of_max" << std::setw(14) << "time_of_fall" << "\n";

    std::cout << std::setw(8) << 1 << std::setw(14) << max1 << std::setw(14) << t_max1;
    if (t_fall1 < 0)
        std::cout << std::setw(14) << "в воздухе" << "\n";
    else
        std::cout << std::setw(14) << t_fall1 << "\n";

    std::cout << std::setw(8) << 2 << std::setw(14) << max2 << std::setw(14) << t_max2;
    if (t_fall2 < 0)
        std::cout << std::setw(14) << "в воздухе" << "\n";
    else
        std::cout << std::setw(14) << t_fall2 << "\n";

    std::cout << "\n";

    if (max1 > max2)
        std::cout << "Выше поднялась ракета 1.\n";
    else if (max2 > max1)
        std::cout << "Выше поднялась ракета 2.\n";
    else
        std::cout << "Ракеты поднялись на одинаковую высоту.\n";

    if (t_fall1 < 0 && t_fall2 < 0)
        std::cout << "Обе ракеты ещё в воздухе.\n";
    else if (t_fall1 < 0)
        std::cout << "Дольше в воздухе ракета 1 (она ещё не упала).\n";
    else if (t_fall2 < 0)
        std::cout << "Дольше в воздухе ракета 2 (она ещё не упала).\n";
    else if (t_fall1 > t_fall2)
        std::cout << "Дольше в воздухе ракета 1.\n";
    else if (t_fall2 > t_fall1)
        std::cout << "Дольше в воздухе ракета 2.\n";
    else
        std::cout << "Ракеты были в воздухе одинаковое время.\n";

    return 0;
}
