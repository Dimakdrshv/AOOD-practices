#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct VideoСassette {
    int cassetteCode;
    std::string filmName;
    std::string filmDirector;
    int year;

    VideoСassette(int cassetteCode, std::string filmName, std::string filmDirector, int year) : cassetteCode{ cassetteCode }, filmName{ filmName },
        filmDirector{ filmDirector }, year{ year } {};

    void outputVideoCassette() {
        std::cout << this->cassetteCode << std::endl;
        std::cout << this->filmName << std::endl;
        std::cout << this->filmDirector << std::endl;
        std::cout << this->year << std::endl;
    }
};

void inputN(int& n) {
    std::cout << "Введите количество считываемых объектов из файла" << std::endl;
    while (true) {
        std::cout << "n: ";
        std::cin >> n;
        if (n > 0 && n <= 50) break;
        else std::cout << "Вы ввели неверное значение n. Попробуйте снова." << std::endl;
    }
}

void inputPath(std::string& path) {
    std::cout << "Введите путь до файла, с которым хотите работать." << std::endl;
    while (true) {
        std::cout << "path: ";
        std::cin >> path;
        if (path.find(".txt") != std::string::npos) break;
        else std::cout << "Вы ввели неверный путь до файла. Попробуйте снова." << std::endl;
    }
}

void inputVideoCassetteArray(const std::string path, int& n, std::vector<VideoСassette*>& videoCassetteArray) {
    int startN = n;
    std::ifstream fin;
    fin.open(path);
    if (fin.is_open()) {
        std::string info;
        short int operationCount = 0;
        int cassetteCode;
        std::string filmName;
        std::string filmDirector;
        int year;
        while (!fin.eof() && startN) {
            std::getline(fin, info);
            if (operationCount == 0) cassetteCode = std::stoi(info);
            else if (operationCount == 1) filmName = info;
            else if (operationCount == 2) filmDirector = info;
            else if (operationCount == 3) year = std::stoi(info);
            else {
                videoCassetteArray.push_back(new VideoСassette(cassetteCode, filmName, filmDirector, year));
                operationCount = -1;
                startN--;
            }
            operationCount++;
        }
        if (startN > 0) {
            videoCassetteArray.push_back(new VideoСassette(cassetteCode, filmName, filmDirector, year));
            startN--;
        }
        if (startN != 0) {
            n -= startN;
            std::cout << "Корректировка размера коллекции на n = " << n << std::endl;
        }
    }
    else std::cout << "Неверное имя файла.";
}

void sortVideoCassetteArray(std::vector<VideoСassette*>& videoCassetteArray) {
    std::sort(std::begin(videoCassetteArray), std::end(videoCassetteArray), [](VideoСassette* a, VideoСassette* b) -> bool {
        return a->cassetteCode < b->cassetteCode;
    });
}

void outputVideoCassetteArray(const int n, std::vector<VideoСassette*>& videoCassetteArray) {
    sortVideoCassetteArray(videoCassetteArray);
    for (size_t i = 0; i < n; i++)
        videoCassetteArray[i]->outputVideoCassette();
}

void findVideoCassette(const int n, const int cassetteCode, const std::vector<VideoСassette*> videoCassetteArray) {
    int start = 0, end = n - 1, mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (videoCassetteArray[mid]->cassetteCode < cassetteCode) start = mid + 1;
        else if (videoCassetteArray[mid]->cassetteCode > cassetteCode) end = mid - 1;
        else { videoCassetteArray[mid]->outputVideoCassette(); return; }
    }
    std::cout << "Видеокассета с данным номером не найдена." << std::endl;
}

void writeByteVideoCassetteArray(const int n, const std::string path, std::vector<VideoСassette*>& videoCassetteArray) {
    sortVideoCassetteArray(videoCassetteArray);
    std::ofstream fout;
    fout.open(path);
    if (fout.is_open()) {
        for (size_t i = 0; i < n; i++)
            fout.write((char*)&(*videoCassetteArray[i]), sizeof(VideoСassette));
    }
    else std::cout << "Неверное имя файла." << std::endl;
}

void readByteVideoCassetteArray(const std::string path, int& n, std::vector<VideoСassette*>& videoCassetteArray) {
    int startN = n;
    std::vector<VideoСassette*> newVideoCassetteArray;
    newVideoCassetteArray.push_back(new VideoСassette(0, "", "", 0));
    size_t count = 0;
    std::ifstream fin;
    fin.open(path);
    if (fin.is_open()) {
        while (fin.read((char*)&(*newVideoCassetteArray[count]), sizeof(VideoСassette)) && startN) {
            count++;
            newVideoCassetteArray.push_back(new VideoСassette(0, "", "", 0));
            startN--;
        }
        newVideoCassetteArray.erase(std::begin(newVideoCassetteArray) + newVideoCassetteArray.size() - 1);
        videoCassetteArray = newVideoCassetteArray;
        if (startN != 0) {
            n -= startN;
            std::cout << "Корректировка размера коллекции на n = " << n << std::endl;
        }
    }
    else std::cout << "Неверное имя файла." << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    int operation;
    int n;
    std::string path;
    std::vector<VideoСassette*> videoCassetteArray;
    while (true) {
        std::cout << "Введите операцию:\n"
            << "1. Ввод данных об n объектах из текстового файла в массив структур (0<n<=50)\n"
            << "2. Сортировка массива структур по возрастанию поля \"Код видеокассеты\"\n"
            << "3. Вывод данных об объектах на экран в упорядоченном по возрастанию виде\n"
            << "4. Поиск объекта по значению поля \"Код видеокассеты\"\n"
            << "5. Запись упорядоченных данных об объектах в двоичный файл\n"
            << "6. Чтение двоичного файла\n" 
            << "0. Выход\n>>> ";
        std::cin >> operation;
        switch (operation) {
        case 1: {
            inputN(n);
            inputPath(path);
            inputVideoCassetteArray(path, n, videoCassetteArray);
            break;
        }
        case 2:
            sortVideoCassetteArray(videoCassetteArray);
            break;
        case 3:
            outputVideoCassetteArray(n, videoCassetteArray);
            break;
        case 4: {
            int cassetteCode;
            std::cout << "Введите номер кассеты, которую хотите найти: ";
            std::cin >> cassetteCode;
            sortVideoCassetteArray(videoCassetteArray);
            findVideoCassette(n, cassetteCode, videoCassetteArray);
            break;
        }
        case 5: {
            inputPath(path);
            writeByteVideoCassetteArray(n, path, videoCassetteArray);
            break;
        }
        case 6: {
            inputN(n);
            inputPath(path);
            readByteVideoCassetteArray(path, n, videoCassetteArray);
            break;
        }
        case 0:
            std::cout << "Завершение программы." << std::endl;
            exit(0);
        default: { std::cout << "Неверно введена операция. Попробуйте снова." << std::endl; break; }
        }
    }
}