#include <iostream>
#include <vector>

void InputAmountOfArrayElements(int& n) {
    std::cout << "Введите количество элементов массива 1 <= n <= 100\n";
    while (true) {
        std::cout << "n: ";
        std::cin >> n;
        if (n >= 1 && n <= 100) break;
        else std::cout << "Введенное вами число некорректно, попробуйте еще раз." << std::endl;
    }
}

void InputArrayElements(int* const array, const int SIZE) {
    std::cout << "Введите элементы массива: " << std::endl;
    for (int i = 0; i < SIZE; i++)
        std::cin >> array[i];
}

void FillingVector(std::vector<std::vector<int>>& Elements, const int* const array, short int index, short int start, short int end) {
    Elements.resize(index + 1);
    for (size_t i = start; i < end; i++)
        Elements[index].push_back(array[i]);
}

void OutputAnswer(std::vector<std::vector<int>>& Elements) {
    short int count = 1;
    for (int i = 0; i < Elements.size(); i++) {
        if (Elements[i].empty()) continue;
        else {
            std::cout << "Подпоследовательность " << count << ": ";
            for (int j = 0; j < Elements[i].size(); j++) {
                std::cout << Elements[i][j] << " ";
            }
            std::cout << std::endl;
            count++;
        }
    }
}

void Solution(int* const array, const int SIZE) {
    std::vector<std::vector<int>> Elements;
    short int index = 0, start, end, count = 1, maxcount = 1;
    for (size_t i = 0; i < SIZE - 1; i++) {
        if (array[i] < array[i + 1]) {
            count++;
            if (count >= maxcount) {
                start = i - count + 2;
                end = start + count;
                if (count > maxcount) {
                    Elements.clear();
                    index = 0;
                }
                FillingVector(Elements, array, index, start, end);
                maxcount = count; index++;
            }
        }
        else count = 1;
    }
    if (Elements.empty()) {
        Elements.resize(SIZE);
        for (size_t i = 0; i < SIZE; i++) 
            Elements[i].push_back(array[i]);
    }
    OutputAnswer(Elements);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n;
    InputAmountOfArrayElements(n);
    int* array = new int[n];
    InputArrayElements(array, n);
    Solution(array, n);
    delete[] array;
}