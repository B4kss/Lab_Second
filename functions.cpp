#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

// Проверка високосного года
int checkLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Проверка корректности даты
bool checkDate(std::string date) {  // ИСПРАВЛЕНО: const std::string&
    std::regex date_regex(R"(\b\d{2}\.\d{2}\.\d{4}\b)");

    if (!std::regex_match(date, date_regex)) {
        return false;
    }

    std::vector<std::string> parts;
    std::stringstream ss(date);
    std::string part;

    while (std::getline(ss, part, '.')) {
        parts.push_back(part);
    }

    int day = std::stoi(parts[0]);
    int month = std::stoi(parts[1]);
    int year_num = std::stoi(parts[2]);

    // Проверка месяца
    if (month < 1 || month > 12) {
        return false;
    }

    // Проверка дня
    if (day < 1 || day > 31) {
        return false;
    }

    // Проверка месяцев с 30 днями
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    // Проверка февраля
    if (month == 2) {
        if (checkLeapYear(year_num)) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    }

    return true;
}

// Чтение записей из файла
std::vector<Record> readRecordsFromFile(const std::string& filename) {
    std::vector<Record> records;
    std::ifstream infile(filename);
    
    if (!infile) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        return records;
    }

    std::regex date_regex(R"(\b\d+\.\d+\.\d+\b)");
    std::regex number_regex(R"(\b\d+\b)");
    std::regex text_regex(R"((["'])?([а-яА-Яa-zA-Z]+)(["'])?)");

    std::string line;
    while (std::getline(infile, line)) {
        std::smatch date_match;
        if (std::regex_search(line, date_match, date_regex)) {
            std::string date = date_match[0];
            std::string line_without_date = std::regex_replace(line, date_regex, "");

            std::smatch number_match;
            if (std::regex_search(line_without_date, number_match, number_regex)) {
                std::string number = number_match[0];
                std::string without_nums = std::regex_replace(line_without_date, number_regex, "");

                std::smatch text_match;
                if (std::regex_search(without_nums, text_match, text_regex)) {
                    std::string text = text_match[2];

                    Record rec;
                    rec.date = date;
                    rec.text = text;
                    rec.income = std::stoi(number);
                    records.push_back(rec);
                }
            }
        }
    }

    infile.close();
    return records;
}

// Проверка всех дат
bool checkAllDates(const std::vector<Record>& records) {
    for (const auto& rec : records) {
        if (!checkDate(rec.date)) {
            return false;
        }
    }
    return true;
}

// Добавление новой записи
void addNewRecord() {
    std::string new_date, new_text, new_income_str;
    int new_income;

    std::regex date_regex(R"(\b\d{2}\.\d{2}\.\d{4}\b)");
    std::regex number_regex(R"(\b\d+\b)");
    std::regex text_regex(R"([а-яА-Яa-zA-Z]+)");

    // Ввод и проверка даты
    while (true) {
        std::cout << "Введите дату в формате ДД.ММ.ГГГГ: ";
        std::cin >> new_date;

        if (!std::regex_match(new_date, date_regex)) {
            std::cout << "Ошибка: неверный формат даты! Попробуйте снова." << std::endl;
            continue;
        }

        if (!checkDate(new_date)) {
            std::cout << "Ошибка: некорректная дата! Попробуйте снова." << std::endl;
            continue;
        }

        break;
    }

    // Ввод и проверка суммы
    while (true) {
        std::cout << "Введите сумму (целое число): ";
        std::cin >> new_income_str;

        if (!std::regex_match(new_income_str, number_regex)) {
            std::cout << "Ошибка: сумма должна быть целым числом! Попробуйте снова." << std::endl;
            continue;
        }

        try {
            new_income = std::stoi(new_income_str);
            break;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: неверный формат числа! Попробуйте снова." << std::endl;
        }
    }

    // Ввод источника
    while (true) {
        std::cout << "Введите источник дохода: ";
        std::cin >> new_text;

        if (!std::regex_match(new_text, text_regex)) {
            std::cout << "Источник должен содержать только буквы! Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    // Добавление в файл
    std::ofstream outfile("Test.txt", std::ios::app);
    if (!outfile) {
        std::cout << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }

    outfile << std::endl << new_date << " " << new_income << " \"" << new_text << "\"";
    outfile.close();

    std::cout << "Данные успешно добавлены в файл!" << std::endl;
}

// Вывод записей
void printRecords(bool sortByIncome) {
    std::vector<Record> records = readRecordsFromFile("Test.txt");
    
    if (records.empty()) {
        std::cout << "Нет данных для отображения." << std::endl;
        return;
    }

    if (!checkAllDates(records)) {
        std::cout << "Ошибка! Некорректная дата в файле!" << std::endl;
        return;
    }

    if (sortByIncome) {
        std::sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
            return a.income > b.income;
        });
        std::cout << "Отсортированные данные (по убыванию дохода):\n\n";
    } else {
        std::cout << "Неотсортированные данные:\n\n";
    }

    for (const auto& r : records) {
        std::cout << "Дата: " << r.date << " | Сумма: " << r.income << " | Источник: " << r.text << std::endl;
    }
}