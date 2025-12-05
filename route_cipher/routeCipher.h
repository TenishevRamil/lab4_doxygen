#pragma once
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @brief Класс исключения для ошибок шифрования
 * @details Используется для обработки ошибок в шифре маршрутной перестановки
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
 * @brief Шифрование методом маршрутной перестановки
 * @details Класс реализует шифр табличной маршрутной перестановки.
 *          Маршрут записи: по горизонтали слева направо, сверху вниз.
 *          Маршрут считывания: сверху вниз, справа налево.
 * @warning Ключ (количество столбцов) должен быть положительным числом
 */
class RouteCipher {
private:
    int key; ///< Количество столбцов таблицы

public:
    RouteCipher() = delete; ///< Запрет конструктора без параметров
    
    /**
     * @brief Конструктор для установки ключа
     * @param k Количество столбцов таблицы
     * @throw cipher_error если k <= 0
     */
    RouteCipher(int k);
    
    /**
     * @brief Шифрование текста методом маршрутной перестановки
     * @param text Текст для шифрования. Записывается в таблицу построчно,
     *             считывается по столбцам справа налево.
     * @return Зашифрованный текст
     * @throw cipher_error если текст пустой
     */
    std::string encrypt(const std::string& text);
    
    /**
     * @brief Дешифрование текста методом маршрутной перестановки
     * @param text Зашифрованный текст. Записывается в таблицу по столбцам
     *             справа налево, считывается построчно.
     * @return Расшифрованный текст
     * @throw cipher_error если текст пустой
     */
    std::string decrypt(const std::string& text);
};
