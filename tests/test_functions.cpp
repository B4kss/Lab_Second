#include <gtest/gtest.h>
#include "functions.h"
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

// Тест 1: Стандартный високосный год
TEST(LeapYearTest, StandardLeapYear) {
    EXPECT_EQ(checkLeapYear(2020), 1);
    EXPECT_EQ(checkLeapYear(2024), 1);
}

// Тест 2: Год, кратный 100, но не 400
TEST(LeapYearTest, CenturyNonLeapYear) {
    EXPECT_EQ(checkLeapYear(1900), 0);
    EXPECT_EQ(checkLeapYear(2100), 0);
}

// Тест 3: Год, кратный 400
TEST(LeapYearTest, FourHundredYearLeap) {
    EXPECT_EQ(checkLeapYear(2000), 1);
    EXPECT_EQ(checkLeapYear(2400), 1);
}

// Тест 4: Обычный невисокосный год
TEST(LeapYearTest, RegularNonLeapYear) {
    EXPECT_EQ(checkLeapYear(2023), 0);
    EXPECT_EQ(checkLeapYear(2021), 0);
}

// Тест 5: Корректные даты
TEST(DateValidationTest, ValidDates) {
    EXPECT_TRUE(checkDate("15.06.2023"));
    EXPECT_TRUE(checkDate("01.01.2000"));
    EXPECT_TRUE(checkDate("31.12.1999"));
}

// Тест 6: Дата с 29 февраля в високосный год
TEST(DateValidationTest, ValidLeapYearDate) {
    EXPECT_TRUE(checkDate("29.02.2020"));
    EXPECT_TRUE(checkDate("29.02.2024"));
    EXPECT_TRUE(checkDate("29.02.2000"));
}

// Тест 7: 29 февраля НЕ в високосный год
TEST(DateValidationTest, InvalidFeb29NonLeap) {
    EXPECT_FALSE(checkDate("29.02.2023"));
    EXPECT_FALSE(checkDate("29.02.1900"));
    EXPECT_FALSE(checkDate("29.02.2100"));
}

// Тест 8: Некорректный день (>31)
TEST(DateValidationTest, InvalidDay) {
    EXPECT_FALSE(checkDate("32.01.2023"));
    EXPECT_FALSE(checkDate("00.01.2023"));
    EXPECT_FALSE(checkDate("35.05.2023"));
}

// Тест 9: Некорректный месяц (>12)
TEST(DateValidationTest, InvalidMonth) {
    EXPECT_FALSE(checkDate("15.13.2023"));
    EXPECT_FALSE(checkDate("01.00.2023"));
    EXPECT_FALSE(checkDate("15.20.2023"));
}

// Тест 10: Месяцы с 30 днями
TEST(DateValidationTest, MonthsWith30Days) {
    EXPECT_FALSE(checkDate("31.04.2023")); // Апрель
    EXPECT_FALSE(checkDate("31.06.2023")); // Июнь
    EXPECT_FALSE(checkDate("31.09.2023")); // Сентябрь
    EXPECT_FALSE(checkDate("31.11.2023")); // Ноябрь
    
    EXPECT_TRUE(checkDate("30.04.2023"));
    EXPECT_TRUE(checkDate("30.06.2023"));
}

// Тест 11: Неправильный формат даты
TEST(DateValidationTest, WrongFormat) {
    EXPECT_FALSE(checkDate("15-06-2023"));
    EXPECT_FALSE(checkDate("15/06/2023"));
    EXPECT_FALSE(checkDate("15062023"));
    EXPECT_FALSE(checkDate("1.6.2023"));   // Одна цифра
    EXPECT_FALSE(checkDate("15.06.23"));   // Две цифры в годе
    EXPECT_FALSE(checkDate(""));           // Пустая строка
    EXPECT_FALSE(checkDate("abc.def.ghij")); // Буквы вместо цифр
}

// Тест 12: Чтение корректного файла
TEST(FileReadingTest, ReadValidFile) {
    // Создаем тестовый файл
    const string filename = "test_valid.txt";
    
    ofstream file(filename);
    file << "15.06.2023 5000 \"Salary\"\n";
    file << "20.06.2023 1500 \"Freelance\"\n";
    file << "01.07.2023 3000 \"Investment\"\n";
    file.close();
    
    auto records = readRecordsFromFile(filename);
    
    ASSERT_EQ(records.size(), 3);
    
    EXPECT_EQ(records[0].date, "15.06.2023");
    EXPECT_EQ(records[0].income, 5000);
    EXPECT_EQ(records[0].text, "Salary");
    
    EXPECT_EQ(records[1].date, "20.06.2023");
    EXPECT_EQ(records[1].income, 1500);
    EXPECT_EQ(records[1].text, "Freelance");
    
    EXPECT_EQ(records[2].date, "01.07.2023");
    EXPECT_EQ(records[2].income, 3000);
    EXPECT_EQ(records[2].text, "Investment");
    
    remove(filename.c_str());
}

// Тест 13: Пустой файл
TEST(FileReadingTest, EmptyFile) {
    const string filename = "test_empty.txt";
    
    ofstream file(filename);
    file.close();
    
    auto records = readRecordsFromFile(filename);
    EXPECT_TRUE(records.empty());
    
    remove(filename.c_str());
}

// Тест 14: Файл с некорректными строками
TEST(FileReadingTest, FileWithInvalidLines) {
    const string filename = "test_invalid.txt";
    
    ofstream file(filename);
    file << "15.06.2023 5000 \"Salary\"\n";     // Корректная
    file << "Incorrect string without any data\n";   // Некорректная
    file << "20.06.2023 1500 \"Freelance\"\n";      // Корректная
    file << "\n";                                  // Пустая строка
    file << "incorrect string again\n";            // Некорректная
    file.close();
    
    auto records = readRecordsFromFile(filename);
    
    // Должны прочитаться только 2 корректные строки
    EXPECT_EQ(records.size(), 2);
    EXPECT_EQ(records[0].date, "15.06.2023");
    EXPECT_EQ(records[1].date, "20.06.2023");
    
    remove(filename.c_str());
}

// Тест 15: Файл с разными форматами чисел
TEST(FileReadingTest, DifferentNumberFormats) {
    const string filename = "test_numbers.txt";
    
    ofstream file(filename);
    file << "01.01.2023 0 \"Zero Income\"\n";       // Ноль
    file << "02.01.2023 100 \"Little Income\"\n";   // Маленькое число
    file << "03.01.2023 1000000 \"Big Income\"\n";  // Большое число
    file << "04.01.2023 999999 \"HUGE Income\"\n";  // Большое число
    file.close();
    
    auto records = readRecordsFromFile(filename);
    
    ASSERT_EQ(records.size(), 4);
    EXPECT_EQ(records[0].income, 0);
    EXPECT_EQ(records[1].income, 100);
    EXPECT_EQ(records[2].income, 1000000);
    EXPECT_EQ(records[3].income, 999999);
    
    remove(filename.c_str());
}

// Тест 16: Все даты корректны
TEST(CheckAllDatesTest, AllDatesValid) {
    vector<Record> records = {
        {"15.06.2023", "Зарплата", 5000},
        {"29.02.2024", "Бонус", 1000},  // Високосный год
        {"31.01.2023", "Аванс", 2000}
    };
    
    EXPECT_TRUE(checkAllDates(records));
}

// Тест 17: Одна некорректная дата
TEST(CheckAllDatesTest, OneInvalidDate) {
    vector<Record> records = {
        {"15.06.2023", "Зарплата", 5000},
        {"32.01.2023", "Ошибка", 1000},  // Некорректная!
        {"20.06.2023", "Фриланс", 1500}
    };
    
    EXPECT_FALSE(checkAllDates(records));
}

// Тест 18: Все даты некорректны
TEST(CheckAllDatesTest, AllDatesInvalid) {
    vector<Record> records = {
        {"32.13.2023", "Mistake1", 1000},
        {"00.00.0000", "Mistake2", 2000},
        {"99.99.9999", "Mistake3", 3000}
    };
    
    EXPECT_FALSE(checkAllDates(records));
}

// Тест 19: Пустой вектор записей
TEST(CheckAllDatesTest, EmptyVector) {
    vector<Record> records;
    EXPECT_TRUE(checkAllDates(records)); // Пустой список считается валидным
}

// Тест 20: Создание и сравнение записей
TEST(RecordTest, RecordCreationAndComparison) {
    Record rec1;
    rec1.date = "15.06.2023";
    rec1.text = "Зарплата";
    rec1.income = 5000;
    
    Record rec2 = {"15.06.2023", "Зарплата", 5000};
    
    EXPECT_EQ(rec1.date, rec2.date);
    EXPECT_EQ(rec1.text, rec2.text);
    EXPECT_EQ(rec1.income, rec2.income);
    
    // Проверка разных записей
    Record rec3 = {"20.06.2023", "Фриланс", 1500};
    EXPECT_NE(rec1.date, rec3.date);
    EXPECT_NE(rec1.text, rec3.text);
    EXPECT_NE(rec1.income, rec3.income);
}

// Тест 21: Граничные значения для дней в феврале
TEST(BoundaryTests, FebruaryBoundaries) {
    // Високосный год
    EXPECT_TRUE(checkDate("28.02.2024"));
    EXPECT_TRUE(checkDate("29.02.2024"));
    EXPECT_FALSE(checkDate("30.02.2024"));
    
    // Невисокосный год
    EXPECT_TRUE(checkDate("28.02.2023"));
    EXPECT_FALSE(checkDate("29.02.2023"));
    EXPECT_FALSE(checkDate("30.02.2023"));
}


// Главная функция
int main(int argc, char **argv) {
    // Инициализация Google Test
    ::testing::InitGoogleTest(&argc, argv);
    
    // Запуск всех тестов
    return RUN_ALL_TESTS();
}