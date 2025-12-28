#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

// Структура записи
struct Record {
    std::string date;
    std::string text;
    int income;
};

// Функция проверки високосного года
int checkLeapYear(int year);

// Функция проверки корректности даты
bool checkDate(std::string date);

// Функция чтения записей из файла
std::vector<Record> readRecordsFromFile(const std::string& filename);

// Функция проверки всех дат в записях
bool checkAllDates(const std::vector<Record>& records);

// Функция добавления новой записи
void addNewRecord();

// Функция вывода записей
void printRecords(bool sortByIncome = false);

#endif // FUNCTIONS_H