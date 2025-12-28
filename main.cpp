#include "functions.h"
#include <windows.h>
#include <iostream>
#include <locale.h>
#include <map>
#include <functional>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Чтение данных из файла
    std::vector<Record> records = readRecordsFromFile("Test.txt");
    if (records.empty()) {
        std::cout << "Файл пуст или не найден." << std::endl;
        return 1;
    }

    // Проверка дат
    if (!checkAllDates(records)) {
        std::cout << "Ошибка! Некорректная дата в файле!" << std::endl;
        return 1;
    }

    // Создаём словарь меню
    std::map<int, std::pair<std::string, std::function<void()>>> menuMap;

    menuMap[1] = {"Добавление новой записи", addNewRecord};

    menuMap[2] = {"Вывод имеющихся данных", []() {
        int sortChoice;
        std::cout << "Сортировать по убыванию дохода?\n1. Да\n2. Нет\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> sortChoice;

        if (sortChoice == 1) {
            printRecords(true);
        } else if (sortChoice == 2) {
            printRecords(false);
        } else {
            std::cout << "Ошибка: неверный выбор!" << std::endl;
        }
    }};

    menuMap[3] = {"Выход из программы", []() {
        std::cout << "Выход из программы." << std::endl;
        return; // завершаем программу
    }};

    // Вывод меню
    std::cout << "Опции:\n\n";
    for (auto &[key, item] : menuMap) {
        std::cout << key << ". " << item.first << "\n";
    }

    int choice;
    std::cout << "\nВведите ваш выбор: ";
    std::cin >> choice;
    std::cout << std::endl;

    if (menuMap.find(choice) != menuMap.end()) {
        menuMap[choice].second(); // вызываем функцию
    } else {
        std::cout << "Ошибка: неверный выбор!" << std::endl;
        return 1;
    }

    std::cout << "\nПрограмма завершена." << std::endl;
    return 0;
}