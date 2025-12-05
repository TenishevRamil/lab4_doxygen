/**
 * @file modAlphaCipher.cpp
 * @author Тенишев Рамиль
 * @version 1.0
 * @date 05.12.2025
 * @brief Реализация шифра Гронсфельда для русского алфавита
 * @copyright Учебный проект
 * @warning Это учебный пример
 */

#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <vector>
#include <cwctype>

// Вспомогательная функция для проверки кириллической буквы
bool isCyrillicLetter(wchar_t c) {
    return (c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'Ё' || c == L'ё';
}

// Вспомогательная функция для перевода в верхний регистр
wchar_t toUpperCyrillic(wchar_t c) {
    if (c >= L'а' && c <= L'я') {
        return c - (L'а' - L'А');
    } else if (c == L'ё') {
        return L'Ё';
    }
    return c;
}

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    std::wstring valid_key = getValidKey(skey);
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(valid_key);
}

std::wstring modAlphaCipher::getValidKey(const std::wstring& skey) {
    if (skey.empty()) {
        throw cipher_error("Empty key");
    }
    std::wstring tmp;
    for (wchar_t c : skey) {
        if (!isCyrillicLetter(c)) {
            throw cipher_error("Invalid key character: non-cyrillic character found");
        }
        tmp += toUpperCyrillic(c);
    }
    if (tmp.empty()) {
        throw cipher_error("Empty key after processing");
    }
    return tmp;
}

std::wstring modAlphaCipher::getValidOpenText(const std::wstring& text) {
    std::wstring tmp;
    for (wchar_t c : text) {
        if (isCyrillicLetter(c)) {
            tmp += toUpperCyrillic(c);
        }
    }
    if (tmp.empty()) {
        throw cipher_error("Empty open text after processing");
    }
    return tmp;
}

std::wstring modAlphaCipher::getValidCipherText(const std::wstring& text) {
    if (text.empty()) {
        throw cipher_error("Empty cipher text");
    }
    for (wchar_t c : text) {
        if (alphaNum.find(c) == alphaNum.end()) {
            throw cipher_error("Invalid cipher text: character not in alphabet found");
        }
    }
    return text;
}

void modAlphaCipher::find_space_positions(const std::wstring& text)
{
    space_positions.clear();
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == L' ') {
            space_positions.push_back(i);
        }
    }
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring valid_text = getValidOpenText(open_text);
    find_space_positions(open_text);
    
    std::vector<int> work = convert(valid_text);
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring valid_cipher_text = getValidCipherText(cipher_text);
    std::vector<int> work = convert(valid_cipher_text);
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    std::wstring decrypted_without_spaces = convert(work);
    std::wstring result;
    size_t text_index = 0;
    size_t space_index = 0;
    
    for (size_t i = 0; i < decrypted_without_spaces.length() + space_positions.size(); i++) {
        if (space_index < space_positions.size() && i == space_positions[space_index]) {
            result += L' ';
            space_index++;
        } else {
            if (text_index < decrypted_without_spaces.length()) {
                result += decrypted_without_spaces[text_index];
                text_index++;
            }
        }
    }
    
    return result;
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (wchar_t c : s) {
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        } else {
            throw cipher_error("Invalid character in text during conversion");
        }
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (int i : v) {
        if (i >= 0 && i < (int)numAlpha.size()) {
            result += numAlpha[i];
        } else {
            throw cipher_error("Invalid index in vector during conversion");
        }
    }
    return result;
}
