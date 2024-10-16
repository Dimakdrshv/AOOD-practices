#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void InputText(std::string& text) {
    std::cout << "Введите текст: ";
    while (true) {
        std::getline(std::cin, text);
        if (text.empty()) std::cout << "Вы ввели пустой текст, повторите ввод." << std::endl;
        else break;
    }
}

void FindTextWords(std::vector<std::string>& words, std::string text) {
    while (!text.empty()) {
        if (text.find(' ') != std::string::npos) {
            words.push_back(text.substr(0, text.find(' ')));
            text = text.erase(0, text.find(' ') + 1);
        }
        else {
            words.push_back(text);
            text.erase(text.begin(), text.end());
        }
    }
}

void WordWithoutPunctuationMarks(const std::vector<std::string>& words, std::vector<std::string>& newWords) {
    for (size_t i = 0; i < words.size(); i++) {
        std::string newWord = "";
        std::string word = words[i];
        for (size_t j = 0; j < word.size(); j++) {
            if (std::isalpha(word[j]) || word[j] == '\'') newWord += word[j];
            else if (!newWord.empty()) {
                    newWords.push_back(newWord);
                    newWord = "";
            }
        }
        if (!newWord.empty()) {
            newWords.push_back(newWord);
        }
    }
}

void Solution(std::vector<std::string> words) {
    std::vector<std::string> newWords;
    std::vector<std::string> uniqueWords;
    WordWithoutPunctuationMarks(words, newWords);
    std::cout << "Слова, буквы которых лексикографически упорядочены: ";
    for (size_t i = 0; i < newWords.size(); i++) {
        bool flag = true;
        std::string word = newWords[i];
        for (size_t j = 0; j < word.size() - 1; j++) {
            if (std::isupper(word[j])) word[j] = (int)word[j] + 32;
            if (std::isalpha(word[j]) && std::isalpha(word[j + 1]) && (int)word[j] < (int)word[j + 1] || word[j] == '\'' && (int)word[j-1] < (int)word[j+1] || word[j + 1] == '\'' && (int)word[j] < (int)word[j+2]) continue;
            else {
                flag = false;
                break;
            }
        }
        if (flag) {
            std::string currentWord = newWords[i];
            for (size_t i = 0; i < uniqueWords.size(); i++) {
                if (currentWord == uniqueWords[i]) flag = false;
            }
            if (flag) uniqueWords.push_back(currentWord);
        }
    }
    if (uniqueWords.empty()) std::cout << std::endl << "Слов, буквы которых упорядочены лексикографически не найдено.";
    else {
        for (size_t i = 0; i < uniqueWords.size(); i++) {
            std::cout << uniqueWords[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::string text;
    InputText(text);
    std::vector<std::string> words;
    FindTextWords(words, text);
    Solution(words);
}
