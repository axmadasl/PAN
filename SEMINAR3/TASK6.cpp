#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <clocale>

void printVector(const std::vector<double>& v)
{
    if (v.empty())
    {
        std::cout << "  (вектор пуст)\n";
        return;
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << "  " << v[i] << "\n";
    }
}

void removeBelow10(std::vector<double>& heights)
{
    auto new_end = std::remove_if(heights.begin(), heights.end(), [](double h) { return h < 10.0; });
    heights.erase(new_end, heights.end());
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed << std::setprecision(1);

    double v0 = 50.0;
    double g = 9.8;
    double dt = 1.0;

    std::vector<double> heights;

    for (double t = 0.0; t <= 1000; t += dt)
    {
        double h = v0 * t - 0.5 * g * t * t;

        if (h < 0)
        {
            break;
        }

        heights.push_back(h);
    }

    std::cout << "Высоты до удаления:\n";
    printVector(heights);

    removeBelow10(heights);

    std::cout << "\nВысоты после удаления значений ниже 10 м:\n";
    printVector(heights);

    std::vector<double> allLow = { 1.0, 5.0, 9.9 };
    removeBelow10(allLow);
    std::cout << "\nТест 1, все значения < 10 {1, 5, 9.9}:\n";
    printVector(allLow);

    std::vector<double> allHigh = { 15.0, 20.0, 30.0 };
    removeBelow10(allHigh);
    std::cout << "\nТест 2, ничего не удаляется {15, 20, 30}:\n";
    printVector(allHigh);

    return 0;
}
