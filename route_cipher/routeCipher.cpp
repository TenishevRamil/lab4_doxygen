/**
 * @file routeCipher.cpp
 * @author Тенишев Рамиль
 * @version 1.0
 * @date 05.12.2025
 * @brief Реализация шифра маршрутной перестановки
 * @copyright Учебный проект
 * @warning Это учебный пример
 */

#include "routeCipher.h"
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

RouteCipher::RouteCipher(int k) {
    if (k <= 0) {
        throw cipher_error("Ключ (количество столбцов) должен быть положительным числом");
    }
    key = k;
}

std::string RouteCipher::encrypt(const std::string& text) {
    if (text.empty()) {
        throw cipher_error("Текст не может быть пустым");
    }

    int rows = (text.length() + key - 1) / key;
    vector<vector<char>> table(rows, vector<char>(key, ' '));

    for (size_t i = 0; i < text.length(); i++) {
        int row = i / key;
        int col = i % key;
        table[row][col] = text[i];
    }

    string result;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (row * key + col < static_cast<int>(text.length())) {
                result += table[row][col];
            }
        }
    }
    return result;
}

std::string RouteCipher::decrypt(const std::string& text) {
    if (text.empty()) {
        throw cipher_error("Текст не может быть пустым");
    }

    int rows = (text.length() + key - 1) / key;
    vector<vector<char>> table(rows, vector<char>(key, ' '));

    size_t index = 0;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (row * key + col < static_cast<int>(text.length())) {
                if (index < text.length()) {
                    table[row][col] = text[index++];
                }
            }
        }
    }

    string result;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            if (row * key + col < static_cast<int>(text.length())) {
                result += table[row][col];
            }
        }
    }

    return result;
}
