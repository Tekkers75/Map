#pragma once
#include "AVLTree.h"

template<class K, class T>
class KeyValue {
protected:
    K key;
public:
    T value;
    KeyValue() : key(), value() {} 

    KeyValue(const K& key, const T& value) : key(key), value(value) {}
    KeyValue<K, T>& operator=(const KeyValue<K, T>& other) {
        if (this != &other) {
            key = other.key;
            value = other.value;
        }
        return *this;
    }

    bool operator==(const KeyValue<K, T>& other) const {
        return key == other.key;
    }

    bool operator<(const KeyValue<K, T>& other) const {
        return key < other.key;
    }

    bool operator>(const KeyValue<K, T>& other) const {
        return key > other.key;
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
class Map :public AVLTree<KeyValue<K, T>> {

public:

    void Insert(const K& key, const T& value) {
        KeyValue<K, T> keyValue(key, value);
        AVLTree<KeyValue<K, T>>::Insert(keyValue);
    }

    void Update(const K& key, const T& value) {
        KeyValue<K, T> keyValue(key, value);
        AVLTreeNode<KeyValue<K, T>>* node = AVLTree<KeyValue<K, T>>::Find(keyValue);
        if (node != nullptr) {
            node->data.value = value;  // Обновляем значение существующего элемента
            cout << "Значение ключа" << " " << key << " " << "успешно обновлено" << endl;
        }
        else {
            cout << "Ключ не найден" << endl;
        }
    }

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

    T Get(const K& key) {
        AVLTreeNode<KeyValue<K, T>>* node = AVLTree<KeyValue<K, T>>::Find(KeyValue<K, T>(key, T()));
        if (node != nullptr) {
            return node->data.value;
        }
        /*cout << "Ключ не найден" << endl;*/
        return T();
    }

    bool Find(const K& key) {
        KeyValue<K, T> keyValue(key, T());
        return AVLTree<KeyValue<K, T>>::Find(keyValue) != nullptr;
    }

    void PrintTreeAVL() {
        PrintTree(AVLTree<KeyValue<K, T>>::GetRoot(), 0);
    }

};