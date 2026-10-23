#include <iostream>
#include <iomanip>
#include <vector>
#include <clocale>

struct Point
{
    double x;
    double y;
    double z;
};

class Rocket
{
private:
    double mass;
    double x, y, z;
    double vx, vy, vz;

public:
    Rocket(double m, double vx0, double vy0, double vz0)
    {
        mass = m;
        x = 0.0;
        y = 0.0;
        z = 0.0;
        vx = vx0;
        vy = vy0;
        vz = vz0;
    }

    void updatePosition(double dt)
    {
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;

        if (z < 0)
        {
            z = 0.0;
            vx = 0.0;
            vy = 0.0;
            vz = 0.0;
        }
    }

    void changeVelocity(double dvx, double dvy, double dvz)
    {
        vx += dvx;
        vy += dvy;
        vz += dvz;
    }

    Point getPosition()
    {
        return { x, y, z };
    }

    double getMass()
    {
        return mass;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    double g = 9.8;
    double dt = 0.1;
    double T = 10.0;

    std::vector<Rocket> squad;
    squad.reserve(5);

    squad.emplace_back(1000, 10, 0, 50);
    squad.emplace_back(900, 15, -5, 40);
    squad.emplace_back(1100, 5, 10, 60);
    squad.emplace_back(800, 20, 5, 30);
    squad.emplace_back(950, 0, -10, 70);

    std::vector<std::vector<Point>> trajectories(squad.size());

    for (double t = 0; t <= T; t += dt)
    {
        for (size_t i = 0; i < squad.size(); i++)
        {
            trajectories[i].push_back(squad[i].getPosition());

            squad[i].updatePosition(dt);
            squad[i].changeVelocity(0, 0, -g * dt);
        }
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Конечные положения ракет через " << T << " с:\n\n";
    std::cout << std::setw(8) << "Ракета" << std::setw(10) << "m, кг"
              << std::setw(10) << "x, м" << std::setw(10) << "y, м" << std::setw(10) << "z, м" << "\n";

    for (size_t i = 0; i < squad.size(); i++)
    {
        Point last = trajectories[i].back();

        std::cout << std::setw(8) << i + 1
                  << std::setw(10) << squad[i].getMass()
                  << std::setw(10) << last.x
                  << std::setw(10) << last.y
                  << std::setw(10) << last.z;

        if (last.z <= 0.0)
            std::cout << "   (на земле)";

        std::cout << "\n";
    }

    std::cout << "\nТочек в каждой траектории: " << trajectories[0].size() << "\n";

    return 0;
}
