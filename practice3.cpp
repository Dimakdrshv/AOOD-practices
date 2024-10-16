#include <iostream>
#include <vector>

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

void ArrayInitialization(int**& array, const int n, const int m) {
    array = new int* [n];
    for (size_t i = 0; i < n; i++) {
        array[i] = new int[m];
    }
}

void ArrayElementsInitialization(int**& const array, const int n, const int m) {
    std::cout << "Введите элементы вектора: \n";
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cin >> array[i][j];
        }
    }
}

void AddColumn(int**& array, const int n, int& m, const int index) {
    int** newArray = new int* [n];
    m = m + 1;
    for (size_t i = 0; i < n; i++){
        newArray[i] = new int[m];
    }
    int* tempArray = new int[n];
    std::cout << "Введите новый массив размерности b(n): ";
    for (size_t i = 0; i < n; i++) std::cin >> tempArray[i];
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (j <= index) newArray[i][j] = array[i][j];
            else if (j > index + 1) newArray[i][j] = array[i][j-1];
            else newArray[i][j] = tempArray[i];
        }
    }
    delete[] tempArray;
    for (size_t i = 0; i < n; i++) {
        delete array[i];
    }
    delete[] array;
    array = newArray;
}

void OutputAnswer(int**& const array, const int n, const int m) {
    std::cout << "Окончательный ответ: " << std::endl;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            printf("%4d", array[i][j]);
        }
        std::cout << std::endl;
    }
}

void Clear(int**& array, const int n) {
    for (size_t i = 0; i < n; i++) {
        delete array[i];
    }
    delete[] array;
}


void Solution(int**& array, int& n, int& m) {
    std::vector<int> currentArray;
    for (size_t i = 0; i < m; i++) {
        bool flag = true;
        for (size_t j = 0; j < n; j++) {
            if (array[j][i] != 0) { flag = false; continue; }
        }
        if (flag) {
            currentArray.push_back(i);
        }
    }
    for (size_t i = 0; i < currentArray.size(); i++) {
        AddColumn(array, n, m, currentArray[i] + i);
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n, m;
    InputAmountOfArray(n, m);
    int** array;
    ArrayInitialization(array, n, m);
    ArrayElementsInitialization(array, n, m);
    Solution(array, n, m);
    OutputAnswer(array, n, m);
    Clear(array, n);
}

