#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <stdexcept>
#include <cwctype>

/**
 * @brief Класс исключения для ошибок шифрования
 * @details Наследуется от std::invalid_argument, используется для всех ошибок,
 *          связанных с шифрованием и дешифрованием.
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с строкой в качестве параметра
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    
    /**
     * @brief Конструктор с C-строкой в качестве параметра
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

/**
 * @brief Шифрование методом Гронсфельда
 * @details Класс реализует шифр Гронсфельда для русского алфавита.
 *          Ключ устанавливается в конструкторе. Для зашифровывания и
 *          расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для русского языка
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Алфавит по порядку
    std::map<wchar_t, int> alphaNum; ///< Ассоциативный массив "символ-номер"
    std::vector<int> key; ///< Ключ в числовом виде
    std::vector<size_t> space_positions; ///< Позиции пробелов в исходном тексте

    /**
     * @brief Валидация и преобразование ключа
     * @param skey Ключ в виде строки
     * @return Валидный ключ в верхнем регистре
     * @throw cipher_error если ключ пустой или содержит некириллические символы
     */
    std::wstring getValidKey(const std::wstring& skey);
    
    /**
     * @brief Валидация открытого текста
     * @param text Открытый текст
     * @return Текст без не-букв, в верхнем регистре
     * @throw cipher_error если после обработки текст пуст
     */
    std::wstring getValidOpenText(const std::wstring& text);
    
    /**
     * @brief Валидация зашифрованного текста
     * @param text Зашифрованный текст
     * @return Исходный текст
     * @throw cipher_error если текст пустой или содержит недопустимые символы
     */
    std::wstring getValidCipherText(const std::wstring& text);

    /**
     * @brief Преобразование строки в числовой вектор
     * @param s Строка для преобразования
     * @return Вектор номеров символов в алфавите
     * @throw cipher_error если символ не найден в алфавите
     */
    std::vector<int> convert(const std::wstring& s);
    
    /**
     * @brief Преобразование числового вектора в строку
     * @param v Вектор номеров символов
     * @return Строка из символов алфавита
     * @throw cipher_error если индекс вне диапазона алфавита
     */
    std::wstring convert(const std::vector<int>& v);
    
    /**
     * @brief Поиск позиций пробелов в тексте
     * @param text Исходный текст
     */
    void find_space_positions(const std::wstring& text);

public:
    modAlphaCipher() = delete; ///< Запрет конструктора без параметров
    
    /**
     * @brief Конструктор для установки ключа
     * @param skey Ключ шифрования в виде строки
     * @throw cipher_error если ключ невалиден
     */
    modAlphaCipher(const std::wstring& skey);

    /**
     * @brief Зашифровывание текста
     * @param open_text Открытый текст. Не должен быть пустой строкой.
     *                  Строчные символы автоматически преобразуются к прописным.
     *                  Все не-буквы удаляются.
     * @return Зашифрованная строка
     * @throw cipher_error если текст пустой
     */
    std::wstring encrypt(const std::wstring& open_text);
    
    /**
     * @brief Расшифровывание текста
     * @param cipher_text Зашифрованный текст. Должен содержать только
     *                    прописные буквы русского алфавита.
     * @return Расшифрованная строка с восстановленными пробелами
     * @throw cipher_error если текст пустой или содержит недопустимые символы
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};
