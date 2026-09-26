// =============================================================
// Лабораторная: аэродинамические силы
//   Задача 1 — подъёмная сила      L = 1/2 * rho * V^2 * S * C_L
//   Задача 2 — сила сопротивления  D = 1/2 * rho * V^2 * S * C_D
//   Задача 3 - ускорение по направлению движения a = (T-D)/m и a_y = (L - mg)/m
// 
// Обе задачи в одной программе. При запуске появляется меню,
// где выбираешь, какую задачу решать.
// =============================================================

#include <iostream>   // ввод/вывод: std::cin, std::cout
#include <iomanip>    // форматирование чисел: std::fixed, std::setprecision
#include <clocale>    // setlocale — кириллица в консоли Windows

const double G = 9.81;

// =============================================================
// ФУНКЦИИ РАСЧЁТА
// =============================================================

// Задача 1: подъёмная сила
double calculateLift(double rho, double V, double S, double CL)
{
    return 0.5 * rho * V * V * S * CL;
}

// Задача 2: сила аэродинамического сопротивления
double calculateDrag(double rho, double V, double S, double CD)
{
    return 0.5 * rho * V * V * S * CD;
}
// Задача 3: ускорение по направлению движения 
double calculateAcceleration(double T, double D, double m)
{
    return (T - D) / m;
}

// Задача 3: вертикальное ускорение.
double calculateVerticalAcceleration(double L, double m)
{
    return (L - m * G) / m;
}

// =============================================================
// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ВВОДА
// =============================================================
double readPositive(const char* prompt)
{
    double value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())                  
        {
            std::cin.clear();                 
            std::cin.ignore(10000, '\n');     
            std::cout << "  Ошибка: нужно ввести число. Попробуй ещё раз.\n";
        }
        else if (value <= 0)                  
        {
            std::cout << "  Ошибка: значение должно быть больше нуля.\n";
        }
        else
        {
            return value;
        }
    }
}
// Для третей задачи, чтобы не было отрицательное число
double readNonNegative(const char* prompt)
{
    double value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "  Ошибка: нужно ввести число. Попробуй ещё раз.\n";
        }
        else if (value < 0)
        {
            std::cout << "  Ошибка: значение должно быть больше нуля.\n";
        }
        else
        {
            return value;
        }
    }
}

// =============================================================
// ЗАДАЧА 1 — ввод, расчёт и вывод подъёмной силы
// =============================================================

void task1()
{
    std::cout << "\n--- Задача 1. Подъёмная сила ---\n";
    std::cout << "Формула: L = 1/2 * rho * V^2 * S * C_L\n\n";

    double S = readPositive("Площадь крыла S, м^2:              ");
    double V = readPositive("Скорость полёта V, м/с:            ");
    double rho = readPositive("Плотность воздуха rho, кг/м^3:     ");
    double CL = readPositive("Коэффициент подъёмной силы C_L:    ");

    double L = calculateLift(rho, V, S, CL);

    std::cout << "\nПодъёмная сила L = " << L << " Н"
        << " (" << L / 1000.0 << " кН)\n";
}

// =============================================================
// ЗАДАЧА 2 — ввод, расчёт и вывод силы сопротивления
// =============================================================
void task2()
{
    std::cout << "\n--- Задача 2. Аэродинамическое сопротивление ---\n";
    std::cout << "Формула: D = 1/2 * rho * V^2 * S * C_D\n\n";

    double S = readPositive("Площадь крыла S, м^2:              ");
    double V = readPositive("Скорость полёта V, м/с:            ");
    double rho = readPositive("Плотность воздуха rho, кг/м^3:     ");
    double CD = readPositive("Коэффициент сопротивления C_D:     ");

    // Параметры передаются в функцию через аргументы —
    // именно это требуется по заданию
    double D = calculateDrag(rho, V, S, CD);

    std::cout << "\nСила сопротивления D = " << D << " Н"
        << " (" << D / 1000.0 << " кН)\n";

}
// =============================================================
// Задача 3 - ускорения ЛА с пояснением результата
// =============================================================
void task3()
{
    std::cout << "\n--- Задача 3. Ускорение ЛА ---\n";
    std::cout << "Формула: a = (T - D) / m,   a_y = (L - m*g) / m\n\n";

    double m = readPositive("Масса ЛА, кг:             ");
    double L = readNonNegative("Подъёмная сила L, Н:               ");
    double D = readNonNegative("Сопротивление D, Н:                ");
    double T = readNonNegative("Тяга двигателя T, Н:               ");

    double a = calculateAcceleration(T, D, m);
    double ay = calculateVerticalAcceleration(L, m);
    const double EPS = 0.01;

    std::cout << "\nУскорение по направлению движения a = " << a << " м/с^2\n";
    if (std::fabs(a) < EPS)
        std::cout << "  -> Тяга уравновешивает сопротивление: самолёт летит с постоянной скоростью.\n";
    else if (a > 0)
        std::cout << "  -> Тяга больше сопротивления: самолёт разгоняется.\n";
    else
        std::cout << "  -> Сопротивление больше тяги: самолёт тормозит.\n";

    // Вертикальное ускорение
    std::cout << "\nВертикальное ускорение a_y = " << ay << " м/с^2\n";
    if (std::fabs(ay) < EPS)
        std::cout << "  -> Подъёмная сила равна весу: горизонтальный полёт без снижения и набора.\n";
    else if (ay > 0)
        std::cout << "  -> Подъёмная сила больше веса: вертикальная скорость растёт (набор высоты).\n";
    else
        std::cout << "  -> Подъёмная сила меньше веса: самолёт проседает вниз (снижение).\n";

}


// =============================================================
// ГЛАВНАЯ ФУНКЦИЯ — меню выбора задачи
// =============================================================
int main()
{
    setlocale(LC_ALL, "Russian");                 
    std::cout << std::fixed << std::setprecision(2); 

    int choice;

    
    do
    {
        std::cout << "\n==============================\n";
        std::cout << "1 - Задача 1: подъёмная сила\n";
        std::cout << "2 - Задача 2: сопротивление\n";
        std::cout << "3 - Задача 3: ускорения ЛА\n";
        std::cout << "0 - Выход\n";
        std::cout << "Выбери задачу: ";
        std::cin >> choice;

        if (std::cin.fail())              // если ввели не число — чистим и спрашиваем снова
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;                  
        }
       
        switch (choice)
        {
        case 1:
            task1();
            break;                        
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 0:
            std::cout << "Выход.\n";
            break;
        default:                          
            std::cout << "Нет такого пункта, введи 1, 2 или 0.\n";
        }
    } while (choice != 0);

    return 0;
}