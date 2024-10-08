﻿#include <iostream>
#include <string>
#include <vector>

namespace BoyerMoore {

    // создание таблицы смещений
    void CreateTable(const std::string& pattern, std::vector<int>& table) {
        int pattern_size = pattern.length();
        for (int i = 0; i < 256; ++i) {
            table[i] = pattern_size; // инициализируем таблицу значением длины образа
        }
        for (int i = 0; i < pattern_size - 1; i++) {
            table[static_cast<unsigned char>(pattern[i])] = pattern_size - 1 - i; // заполняем таблицу
        }
    }

    // поиск подстроки с возможностью указать вхождения
    std::vector<int> Search(const std::string& text, const std::string& pattern, int start, int end, bool searchFirst) {
        std::vector<int> indices;
        int text_size = text.length();
        int pattern_size = pattern.length();

        if (pattern_size == 0 || pattern_size > text_size || start < 0 || end >= text_size || start > end) {
            return indices;
        }

        std::vector<int> table(256);
        CreateTable(pattern, table);

        int bias = start; // начальное смещение
        while (bias <= end - pattern_size) {
            int j = pattern_size - 1;

            while (j >= 0 && pattern[j] == text[bias + j]) {
                --j;
            }

            if (j < 0) {
                indices.push_back(bias); // сохраняем индекс вхождения
                if (searchFirst) {
                    return indices; // возвращаем сразу, если нужно только первое вхождение
                }
                bias++;
            }
            else {
                bias += std::max(1, j - table[static_cast<unsigned char>(text[bias + j])]);
            }
        }
        return indices;
    }

    // поиск первого вхождения подстроки в строке
    int SearchFirst(const std::string& text, const std::string& pattern) {
        auto indices = Search(text, pattern, 0, text.length() - 1, true);
        if (indices.empty()) {
            return -1;
        }
        else {
            return indices[0];
        }
    }

    // поиск всех вхождений подстроки в заданном диапазоне
    std::vector<int> SearchAll(const std::string& text, const std::string& pattern, int start, int end) {
        return Search(text, pattern, start, end, false);
    }

}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string text;
    std::cout << "Введите строку: ";
    std::getline(std::cin, text); // getline = ввод строки с пробелами
    std::string pattern;
    std::cout << "Введите подстроку: ";
    std::getline(std::cin, pattern);

    // поиск первого вхождения
    int firstIndex = BoyerMoore::SearchFirst(text, pattern);
    if (firstIndex == -1) {
        std::cout << "Вхождений нет" << '\n';
        return 0;
    }
    else {
        std::cout << "Индекс первого вхождения подстроки: " << firstIndex << '\n';
    }

    // поиск всех вхождений в заданном диапазоне
    std::cout << "Введите диапазон вхождений: ";
    int start, end;
    std::cin >> start >> end;

    std::vector<int> allIndex = BoyerMoore::SearchAll(text, pattern, start, end);
    std::cout << "Индексы всех вхождений подстроки: ";

    if (allIndex.empty()) {
        std::cout << "Вхождений нет" << '\n';
    }
    else {
        for (int index : allIndex) {
            std::cout << index << " ";
        }
        std::cout << '\n';
    }

    return 0;
}