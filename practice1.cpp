#include <iostream>

void Input_Coordinates(int& x, int& y) {
    std::cout << "Введите координаты х и у\nx: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
}

void Input_Rectangle(int& a, int& b) {
    std::cout << "Введите значения сторон прямоугольника" << std::endl;
    while (true) {
        std::cout << "Длина: ";
        std::cin >> a;
        if (a > 0) break;
        else std::cout << "Сторона должна быть положительной." << std::endl;
    }
    while (true) {
        std::cout << "Ширина: ";
        std::cin >> b;
        if (b > 0) break;
        else std::cout << "Сторона должна быть положительной." << std::endl;
    }
}

void Input_Circle(int& r) {
    std::cout << "Введите радиус окружности" << std::endl;
    while (true) {
        std::cout << "Радиус: ";
        std::cin >> r;
        if (r > 0) break;
        else std::cout << "Радиус должен быть положительным." << std::endl;
    }
}

void Solution(int x, int y, int a, int b, int r) {
    if (x >= 0 && x <= b && y <= a/2 && y >= -a/2)
        std::cout << "Точка с координатами: (" << x << "," << y << ")" << " попала в заданную область." << std::endl;
    else if (x < 0 && pow(x, 2) + pow(y, 2) <= pow(r, 2))
        std::cout << "Точка с координатами: (" << x << "," << y << ")" << " попала в заданную область." << std::endl;
    else
        std::cout << "Точка с координатами: (" << x << "," << y << ")" << " не попала в заданную область." << std::endl;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int x, y, a, b, r;
    Input_Rectangle(a, b);
    Input_Circle(r);
    Input_Coordinates(x, y);
    Solution(x, y, a, b, r);
}

