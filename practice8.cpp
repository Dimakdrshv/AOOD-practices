#include <iostream>
#include <vector>
#include <algorithm>

void InputAmountOfArray(int& n, int& m) {
	std::cout << "Введите количество строк массива 1 < n <= 100\n";
	while (true) {
		std::cout << "n: ";
		std::cin >> n;
		if (n > 1 && n <= 100) break;
		else std::cout << "Введенное вами число некорректно, попробуйте еще раз." << std::endl;
	}
	std::cout << "Введите количество столбцов массива 1 < m <= 50\n";
	while (true) {
		std::cout << "m: ";
		std::cin >> m;
		if (m > 1 && m <= 50) break;
		else std::cout << "Введенное вами число некорректно, попробуйте еще раз." << std::endl;
	}
}

void InputArrayElements(int**& matrix, const int n, const int m) {
	std::cout << "Введите элементы целочисленной матрицы:" << std::endl;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			std::cin >> matrix[i][j];
		}
	}
}

void InputArrayElements(char**& matrix, const int n, const int m) {
	std::cout << "Введите элементы строковой матрицы:" << std::endl;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			std::cin >> matrix[i][j];
			if (std::isupper(matrix[i][j]) && !std::isdigit(matrix[i][j])) matrix[i][j] = (int)matrix[i][j] + 32;
		}
	}
}

template<typename T>
void Tmatrix(std::vector<std::vector<T>>& newMatrix, T**& matrix, const int n, const int m) {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			std::swap(newMatrix[j][i], matrix[i][j]);
		}
	}
}

template<typename T>
void ClearMatrix(T**& matrix, const int n) {
	for (size_t i = 0; i < n; i++)
		delete matrix[i];
	delete[] matrix;
}

void SortMatrix(int**& matrix, const int n, const int m) {
	std::vector<std::vector<int>> newMatrix(m, std::vector<int>(n));
	Tmatrix(newMatrix, matrix, n, m);
	std::sort(newMatrix.begin(), newMatrix.end(), [&n](std::vector<int> a, std::vector<int> b) mutable -> bool {
		return a[n - 1] < b[n - 1];
	});
	Tmatrix(newMatrix, matrix, n, m);
}

void SortMatrix(char**& matrix, const int n, const int m) {
	std::vector<std::vector<char>> newMatrix(m, std::vector<char>(n));
	Tmatrix(newMatrix, matrix, n, m);
	std::sort(newMatrix.begin(), newMatrix.end(), [&n](std::vector<char> a, std::vector<char> b) mutable -> bool {
		return (int)a[n - 1] < (int)b[n - 1];
		});
	Tmatrix(newMatrix, matrix, n, m);
}

void OutputMatrix(const int** const matrix, const int n, const int m) {
	std::cout << "Вывод элементов отсортированной матрицы с целочисленными элементами:" << std::endl;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			printf("%4d", matrix[i][j]);
		}
		std::cout << std::endl;
	}
}

void OutputMatrix(const char** const matrix, const int n, const int m) {
	std::cout << "Вывод элементов отсортированной матрицы со строковыми элементами:" << std::endl;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			printf("%4c", matrix[i][j]);
		}
		std::cout << std::endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	short int operation;
	bool flag = true;
	int n, m;
	InputAmountOfArray(n, m);
	std::cout << "Введите тип данных, которые будет хранить в себе матрица размерности n на m\n1. Целочисленный\n2. Строковый" << std::endl;
	while (flag) {
		std::cin >> operation;
		switch (operation)
		{
			case 1: {
				int** matrix = new int* [n];
				for (size_t i = 0; i < n; i++) {
					matrix[i] = new int[m];
				}
				InputArrayElements(matrix, n, m);
				SortMatrix(matrix, n, m);
				OutputMatrix((const int**)matrix, n, m);
				flag = false;
				ClearMatrix(matrix, n);
				break;
			}
			case 2: {
				char** matrix = new char* [n];
				for (size_t i = 0; i < n; i++) {
					matrix[i] = new char[m];
				}
				InputArrayElements(matrix, n, m);
				SortMatrix(matrix, n, m);
				OutputMatrix((const char**)matrix, n, m);
				flag = false;
				ClearMatrix(matrix, n);
				break;
			}
			default:
				std::cout << "Вы ввели неверный тип данных двумерной матрицы. Попробуйте снова" << std::endl;
				break;
		}
	}
}