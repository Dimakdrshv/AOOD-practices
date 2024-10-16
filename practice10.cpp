#include <iostream>
#include <vector>

void InputAmountOfArrayElements(int& n) {
    std::cout << "Введите значение n - количество элементов одномерного массива." << std::endl;
    while (true) {
        std::cout << "n: ";
        std::cin >> n;
        if (n > 0) break;
        else std::cout << "Вы неверно ввели значение n. Попробуйте снова." << std::endl;
    }
}

void InputArrayElements(std::vector<int>& vector, const int n) {
    std::cout << "Введите элементы массива: ";
    int element;
    for (size_t i = 0; i < n; i++) {
        std::cin >> element;
        vector.push_back(element);
    }
}

int FindMaxElement(const int n, std::vector<int> vector, int stackOveflow = 100) {
    if (stackOveflow == 0) {
        std::cout << "Массив слишком огромный. Стэк переполнен. Ошибка - NULL." << std::endl;
        exit(NULL);
    }
    else {
        if (vector.size() == 1) return vector[0];
        else {
            stackOveflow -= 1;
            std::vector<int> newVector;
            std::copy(std::begin(vector) + 1, std::end(vector), std::back_inserter(newVector));
            return std::max(vector[0], FindMaxElement(n-1, newVector, stackOveflow));
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n;
    std::vector<int> vector;
    InputAmountOfArrayElements(n);
    InputArrayElements(vector, n);
    std::cout << "Максимальный элемент массива: " << FindMaxElement(n, vector) << std::endl;
}

