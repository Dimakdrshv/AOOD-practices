#include <iostream>
#include <functional>
#include <string>
#include <algorithm>

void InputArray(int& n, int*& array);

void OutputArray(const int* const array, const int n);

void CountArrayNumbersDifferentFromLast(const int* const array, const int n);

void DeleteElement(int*& array, int& n);

int main()
{
    setlocale(LC_ALL, "ru");
    int n;
    int* array;
    int operation;
    std::function<void()> Menu = [&operation, &array, &n]() -> void {
        std::cout << "1. Ввести массив\n2. Вывести массив\n3. Посчитать количество элементов массива, которые не совпадают с последним\n4. Удалить элемент массива, стоящий перед первым максимальным элементом массива\n5. Закончить работу программы" << std::endl;
        while (true) {
            std::cout << "Введите операцию над массивом: ";
            std::cin >> operation;
            switch (operation) {
                case 1:
                    InputArray(n, array);
                    break;
                case 2:
                    OutputArray(array, n);
                    break;
                case 3:
                    CountArrayNumbersDifferentFromLast(array, n);
                    break;
                case 4:
                    DeleteElement(array, n);
                    break;
                case 5:
                    exit(0);
                default:
                    std::cout << "Неверная операция, попробуйте еще раз." << std::endl;
                    break;
            }
        }
    };
    Menu();
}

void InputArray(int& n, int*& array) {
    std::cout << "Введите количество элементов массива\n";
    while (true) {
        std::cout << "n: ";
        std::cin >> n;
        if (n > 0 && n <= 100) break;
        else std::cout << "Некорректное количество элементов массива, попробуйте еще раз." << std::endl;
    }
    array = new int[n];
    std::cout << "Введите элементы массива: ";
    for (size_t i = 0; i < n; i++) {
        std::cin >> array[i];
    }
}

void OutputArray(const int* const array, const int n) {
    std::cout << "Элементы массива: ";
    for (size_t i = 0; i < n; i++) printf("%3d", array[i]);
    std::cout << std::endl;
}

void CountArrayNumbersDifferentFromLast(const int* const array, const int n) {
    short int count = 0;
    for (size_t i = 0; i < n - 1; i++) {
        if (array[i] != array[n - 1]) count++;
    }
    std::cout << "Количество чисел массива отличных от последнего элемента массива: " << count << std::endl;
}

void DeleteElement(int*& array, int& n) {
    auto maxElemIndex = std::__std_max_element(array, array + n);
    if (*maxElemIndex == *array) {
        std::cout << "Удаление невозможно, так как первый максимальный элемент массива находится на нулевом индексе." << std::endl;
        return;
    }
    int* newArray = new int[n - 1];
    short int index = 0;
    for (auto i = array; i < array + n; ++i) {
        if (i + 1 != maxElemIndex) {
            *(newArray + index) = *i;
            ++index;
        }
        else continue;
    }
    n -= 1;
    delete[] array;
    array = newArray;
}