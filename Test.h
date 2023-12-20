#pragma once

#include <cassert>
#include "Map.h"
#include <string>
using namespace std;

void TestMapInsert() {
    Map<int, string> map;

    // Вставка новых элементов
    map.Insert(1, "One");
    map.Insert(2, "Two");
    map.Insert(3, "Three");

    // Проверка значений
    assert(map.Get(1) == "One");
    assert(map.Get(2) == "Two");
    assert(map.Get(3) == "Three");

    // Обновление существующего элемента
    map.Update(3, "New Two");

    // Проверка обновленного значения
    assert(map.Get(3) == "New Two");
}

void TestMapRemove() {
    Map<int, string> map;

    // Вставка элементов
    map.Insert(1, "One");
    map.Insert(2, "Two");
    map.Insert(3, "Three");

    // Удаление элемента
    map.Remove(2);

    // Проверка удаления
    assert(!map.Find(2));
    assert(map.Get(2) == "");

    // Проверка оставшихся элементов
    assert(map.Get(1) == "One");
    assert(map.Get(3) == "Three");
}

void TestMapGet() {
    Map<int, string> map;

    // Вставка элемента
    map.Insert(1, "One");

    // Получение значения по ключу
    string value = map.Get(1);

    // Проверка значения
    assert(value == "One");
}

void TestMapFind() {
    Map<int, string> map;

    // Вставка элемента
    map.Insert(1, "One");

    // Поиск элемента
    bool found = map.Find(1);

    // Проверка результата поиска
    assert(found);

    // Поиск отсутствующего элемента
    found = map.Find(2);

    // Проверка результата поиска
    assert(!found);
}

void TestMapPrintTreeAVL() {
    Map<int, string> map;

    // Вставка элементов
    map.Insert(1, "One");
    map.Insert(2, "Two");
    map.Insert(3, "Three");

    // Вывод дерева AVL
    map.PrintTreeAVL();
}

