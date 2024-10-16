#include <iostream>
#include <iomanip>

void InputEps(float& eps) {
	std::cout << "Введите значение точности вычисления интеграла.\n";
	while (true) {
		std::cout << "eps: ";
		std::cin >> eps;
		if (eps > pow(10, -4)) break;
		else std::cout << "Вы ввели некорректное значение. Попробуйте еще раз." << std::endl;
	}
}

float f(float x) {
	return (float)pow(x, 2) * exp(-0.5 * x);
}

float SimpsoneIntegration(int a, int b, int n) {
	float h = (float)(b - a) / n;
	float integral = f(a) + f(b);
	short int k;
	for (size_t i = 1; i < n - 1; i++) {
		k = 2 + 2 * (i % 2);
		integral += k * f(a + h * i);
	}
	integral *= h / 3;
	return integral;
}

void Solution(int a, int b, int& n, float eps, float& integrationValue) {
	float integral_old = SimpsoneIntegration(a, b, n);
	while (true) {
		n *= 2;
		float integral_new = SimpsoneIntegration(a, b, n);
		if (fabs(integral_new - integral_old) <= eps) {
			integrationValue = integral_new;
			break;
		}
		integral_old = integral_new;
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	int n = 2;
	int startN = n;
	int a = 0;
	float eps;
	float integrationValue;
	InputEps(eps);
	std::cout << std::setw(5) << "Параметр b" << std::setw(15) << "Интеграл" << std::setw(20) << "Кол-во отрезков" << std::endl;
	for (int b = 1; b <= 10; b++) {
		Solution(a, b, n, eps, integrationValue);
		std::cout << std::setw(5) << b << std::setw(20) << std::fixed << std::setprecision(10) << integrationValue << std::setw(20) << n << std::endl;
		n = startN;
	}
}

