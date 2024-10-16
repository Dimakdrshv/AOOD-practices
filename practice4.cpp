#include <iostream>
#include <string>
#include <functional>

int main()
{
    setlocale(LC_ALL, "ru");
    std::string email;
    std::function<void(std::string&)> Solution = [](std::string& email) -> void {
        std::cout << "Введите электронную почту: ";
        while (true) {
            std::cin >> email;
            if (std::count(email.begin(), email.end(), '@') != 1) std::cout << "Неверная почта, попробуйте еще раз: ";
            else {
                std::string emailName = email.substr(0, email.find("@"));
                if (emailName.find("__") != std::string::npos) std::cout << "Неверная почта, попробуйте еще раз: ";
                else { std::cout << "Почта введена корректно." << std::endl; break; }
            }
        }
    };
    Solution(email);
}