// @author Саранчин К.А.
#pragma once
#include "AVLTree.h"

// Класс KeyValue представляет пару ключ-значение для элементов словаря
template<class K, class T>
class KeyValue {
protected:
    K key; // Ключ
public:
    T value; // Значение
    KeyValue() : key(), value() {}

    // Конструктор c параметрами ключ - значение
    KeyValue(const K& key, const T& value) : key(key), value(value) {}
    KeyValue<K, T>& operator=(const KeyValue<K, T>& other) {
        if (this != &other) {
            key = other.key;
            value = other.value;
        }
        return *this;
    }
    // Сравнение ключей
    bool operator==(const KeyValue<K, T>& other) const {
        return key == other.key;
    }

    // Сравнение ключей <
    bool operator<(const KeyValue<K, T>& other) const {
        return key < other.key;
    }

    // Сравнение ключей >
    bool operator>(const KeyValue<K, T>& other) const {
        return key > other.key;
    }

    // Получения значения ключа
    K getkey() const
    {
        return key;
    };

    // Оператор вывода в консоль
    friend std::ostream& operator<<(std::ostream& os, const KeyValue<K, T>& keyValue) {
        os << "Ключ: " << keyValue.key << ", Значение: " << keyValue.value;
        return os;
    }
};

// Класс словарь на основе АВЛ дерева
template<class K, class T>
class Map : public AVLTree<KeyValue<K, T>> {

public:
    // Вставка элемента в дерево, если ключ существует, то вставить новое значение не получится.
    void Insert(const K& key, const T& value) {
        KeyValue<K, T> keyValue(key, value);
        AVLTree<KeyValue<K, T>>::Insert(keyValue);
    }

    // Обновление значения элемента по ключу, если ключа нету, то обновить не получится.
    void Update(const K& key, const T& value) {
        KeyValue<K, T> keyValue(key, value);
        AVLTreeNode<KeyValue<K, T>>* node = this->AVLTree<KeyValue<K, T>>::Find(keyValue);
        if (node != nullptr) {
            node->data.value = value;  // Обновляем значение существующего элемента
            cout << "Значение ключа " << key << " успешно обновлено" << endl;
        }
        else {
            cout << "Ключ не найден" << endl;
        }
    }

    // Удаление элемента по ключу
    void Remove(const K& key) {
        KeyValue<K, T> keyValue(key, T());
        AVLTreeNode<KeyValue<K, T>>* node = AVLTree<KeyValue<K, T>>::Find(keyValue);
        if (node != nullptr) {
            AVLTree<KeyValue<K, T>>::Remove(node->data);
            cout << "Элемент успешно удален" << endl;
        }
        else {
            cout << "Ключ не найден" << endl;
        }
    }

    // Получение значения элемента по ключу,если ключа нету вернется дефолтное значение.
    T Get(const K& key) {
        AVLTreeNode<KeyValue<K, T>>* node = AVLTree<KeyValue<K, T>>::Find(KeyValue<K, T>(key, T()));
        if (node != nullptr) {
            return node->data.value;
        }
        /*cout << "Ключ не найден" << endl;*/
        return T();
    }

    // Поиск элемента по ключу
    bool Find(const K& key) {
        KeyValue<K, T> keyValue(key, T());
        return AVLTree<KeyValue<K, T>>::Find(keyValue) != nullptr;
    }

    // Вывод дерева на экран
    void PrintTreeAVL() {
        PrintTree(AVLTree<KeyValue<K, T>>::GetRoot(), 0);
    }

    /// Todo количество узлов
    // Подсчет узлов
    int CountNode() {
        //вызываем метод базового класса для подсчета пар значении в дереве
        return CountNodes(AVLTree<KeyValue<K, T>>::GetRoot());
    }

};