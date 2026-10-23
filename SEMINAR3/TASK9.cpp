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

    std::vector<double> clean;

    for (double t = 0.0; t <= 1000; t += dt)
    {
        double h = v0 * t - 0.5 * g * t * t;

        if (h < 0)
        {
            break;
        }

        clean.push_back(h);
    }

    std::vector<double> noise = { 5.0, -7.0, 6.0, -4.0, 8.0, -6.0, 3.0, -8.0, 7.0, -5.0, 4.0 };

    std::vector<double> h = clean;
    for (size_t i = 0; i < h.size() && i < noise.size(); i++)
    {
        h[i] += noise[i];
    }

    size_t n = h.size();

    if (n == 0)
    {
        std::cout << "Данных нет.\n";
        return 0;
    }

    std::vector<double> smoothed(n);

    smoothed[0] = h[0];
    smoothed[n - 1] = h[n - 1];

    for (size_t i = 1; i + 1 < n; ++i)
    {
        smoothed[i] = (h[i - 1] + h[i] + h[i + 1]) / 3.0;
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(6) << "t, с" << std::setw(14) << "с шумом, м" << std::setw(16) << "сглаженная, м" << "\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(6) << i * dt << std::setw(14) << h[i] << std::setw(16) << smoothed[i] << "\n";
    }

    double mseNoisy = 0.0;
    double mseSmoothed = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        mseNoisy += (h[i] - clean[i]) * (h[i] - clean[i]);
        mseSmoothed += (smoothed[i] - clean[i]) * (smoothed[i] - clean[i]);
    }

    mseNoisy /= n;
    mseSmoothed /= n;

    std::cout << std::setprecision(2);
    std::cout << "\nСреднеквадратичная ошибка (MSE) относительно точной траектории:\n";
    std::cout << "  с шумом:    " << mseNoisy << "\n";
    std::cout << "  сглаженная: " << mseSmoothed << "\n";

    return 0;
}
