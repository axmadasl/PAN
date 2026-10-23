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

int main()
{
    setlocale(LC_ALL, "Russian");

    double vx = 30.0;
    double vy = 20.0;
    double vz = 40.0;
    double dt = 1.0;
    double t_max = 10.0;

    std::vector<Point> traj;
    traj.reserve((int)(t_max / dt) + 1);

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    for (double t = 0.0; t <= t_max; t += dt)
    {
        traj.push_back({ x, y, z });

        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(6) << "t" << std::setw(10) << "x" << std::setw(10) << "y" << std::setw(10) << "z" << "\n";

    for (size_t i = 0; i < traj.size(); i++)
    {
        std::cout << std::setw(6) << i * dt
                  << std::setw(10) << traj[i].x
                  << std::setw(10) << traj[i].y
                  << std::setw(10) << traj[i].z << "\n";
    }

    Point last = traj.back();
    double t_last = (traj.size() - 1) * dt;

    std::cout << "\nПроверка при t = " << t_last << " с:\n";
    std::cout << "  x = " << last.x << ", vx * t = " << vx * t_last << "\n";
    std::cout << "  y = " << last.y << ", vy * t = " << vy * t_last << "\n";
    std::cout << "  z = " << last.z << ", vz * t = " << vz * t_last << "\n";

    return 0;
}
