#pragma once
#include "AVLTree.h"

template<class K, class T>
class KeyValue {
protected:
    K key;
public:
    T value;
    KeyValue() : key(), value() {} // Конструктор по умолчанию с инициализацией

    //KeyValue(K KeyValue, T datavalue);
    KeyValue(const K& key, const T& value) : key(key), value(value) {}
    KeyValue<K, T>& operator=(const KeyValue<K, T>& other) {
        if (this != &other) {
            key = other.key;
            value = other.value;
        }
        return *this;
    }

    bool operator==(const KeyValue<K, T>& other) const {
        return (key == other.key) && (value == other.value);
    }

    bool operator<(const KeyValue<K, T>& other) const {
        if (key == other.key) {
            return value < other.value;
        }
        return key < other.key;
    }


    bool operator>(const KeyValue<K, T>& other) const {
        return !(*this < other);
    }

    K getkey() const
    {
        return key;
    };

    friend std::ostream& operator<<(std::ostream& os, const KeyValue<K, T>& keyValue) {
        os << "Ключ: " << keyValue.key << ",Значение: " << keyValue.value;
        return os;
    }
};

template<class K, class T>
class Dictionary :public AVLTree<KeyValue<K, T>> {

public:

    /* T& operator[](const K& key) {
         KeyValue<K, T> keyValue(key, T());
         KeyValue<K, T>* result = AVLTree<KeyValue<K, T>>::Find(keyValue);
         if (result) {
             return result->value;
         }
         else {
             KeyValue<K, T> newKeyValue(key, T());
             AVLTree<KeyValue<K, T>>::Insert(newKeyValue);
             return AVLTree<KeyValue<K, T>>::Find(newKeyValue)->data;
         }
     }*/

    void Insert(const K& key, const T& value) {
        KeyValue<K, T> keyValue(key, value);
        AVLTree<KeyValue<K, T>>::Insert(keyValue);
    }

    void Remove(const K& key) {
        KeyValue<K, T> keyValue(key, T());
        AVLTree<KeyValue<K, T>>::Remove(keyValue);
    }

    T Get(const K& key) {
        AVLTreeNode<KeyValue<K, T>>* node = AVLTree<KeyValue<K, T>>::Find(KeyValue<K, T>(key, T()));
        if (node != nullptr) {
            return node->data.value;
        }
        cout << "Ключ не найден" << endl;
        return T(); // Возвращаем значение по умолчанию типа T
    }

    bool Contains(const K& key) {
        KeyValue<K, T> keyValue(key, T());
        return AVLTree<KeyValue<K, T>>::Search(keyValue) != nullptr;
    }

    void PrintTreeAVL() {
        PrintTree(AVLTree<KeyValue<K, T>>::GetRoot(), 0);
    }

};