#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
using namespace std;

struct Record {
    string date;
    string text;
    int income;
};

int main() {
    setlocale(LC_ALL, "Ru");

    ifstream infile("Test.txt");
    if (!infile) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    vector<Record> records;
    string line;

    regex date_regex(R"(\b\d{2}\.\d{2}\.\d{4}\b)");
    regex number_regex(R"(\b\d+\b)");
    regex text_regex(R"((["'])?([а-яА-Яa-zA-Z]+)(["'])?)");

    while (getline(infile, line)) {
        smatch date_match;
        if (regex_search(line, date_match, date_regex)) {
            string date = date_match[0];

            string line_without_date = regex_replace(line, date_regex, "");

            smatch number_match;
            if (regex_search(line_without_date, number_match, number_regex)) {
                string number = number_match[0];

                string without_nums = regex_replace(line_without_date, number_regex, "");

                smatch text_match;
                if (regex_search(without_nums, text_match, text_regex)) {
                    string text = text_match[2]; // Берем текст без кавычек

                    Record rec;
                    rec.date = date;
                    rec.text = text;
                    rec.income = stoi(number);
                    records.push_back(rec);
                }
            }
        }
    }

    infile.close();

    int choice, vibor;
    cout << "Выберите опцию\n\n1.Добавление новой строки\n2.Вывод имеющихся данных" << endl;
    cout << "Введите ваш выбор: ";
    cin >> vibor;
    cout << endl;

    if (vibor == 1) {
        // Здесь будет добавление новой строки
    }
    else if (vibor == 2) {
        cout << "Надо ли отсортировать по убыванию дохода?\n\n";
        cout << "1: Да" << endl << "2: Нет" << endl << "Введите ваш выбор: ";
        cin >> choice;
        cout << "\n";

        if (choice != 1 && choice != 2) {
            cout << "Ошибка!" << endl;
        }
        else if (choice == 2) {
            cout << "Неотсортированные данные" << "\n\n";
            for (const auto& r : records) {
                cout << "Дата: " << r.date << " | Сумма: " << r.income << " | Источник: " << r.text << endl;
            }
        }
        else if (choice == 1) {
            sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
                return a.income > b.income;
                });
            cout << "Отсортированные данные" << "\n\n";
            for (const auto& r : records) {
                cout << "Дата: " << r.date << " | Сумма: " << r.income << " | Источник: " << r.text << endl;
            }
        }
    }
    else {
        cout << "Так нельзя!" << endl;
    }

    return 0;
}