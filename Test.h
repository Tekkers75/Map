#pragma once

#include <cassert>
#include "Map.h"
#include <string>
using namespace std;

void TestMapInsert() {
    Map<int, string> map;

    // ������� ����� ���������
    map.Insert(1, "One");
    map.Insert(2, "Two");
    map.Insert(3, "Three");

    // �������� ��������
    assert(map.Get(1) == "One");
    assert(map.Get(2) == "Two");
    assert(map.Get(3) == "Three");

    // ���������� ������������� ��������
    map.Update(3, "New Two");

    // �������� ������������ ��������
    assert(map.Get(3) == "New Two");
}

void TestMapRemove() {
    Map<int, string> map;

    // ������� ���������
    map.Insert(1, "One");
    map.Insert(2, "Two");
    map.Insert(3, "Three");

    // �������� ��������
    map.Remove(2);

    // �������� ��������
    assert(!map.Find(2));
    assert(map.Get(2) == "");

    // �������� ���������� ���������
    assert(map.Get(1) == "One");
    assert(map.Get(3) == "Three");
}

void TestMapGet() {
    Map<int, string> map;

    // ������� ��������
    map.Insert(1, "One");

    // ��������� �������� �� �����
    string value = map.Get(1);

    // �������� ��������
    assert(value == "One");
}

void TestMapFind() {
    Map<int, string> map;

    // ������� ��������
    map.Insert(1, "One");

    // ����� ��������
    bool found = map.Find(1);

    // �������� ���������� ������
    assert(found);

    // ����� �������������� ��������
    found = map.Find(2);

    // �������� ���������� ������
    assert(!found);
}

void TestMapPrintTreeAVL() {
    Map<int, string> map;

    // ������� ���������
    map.Insert(1, "One");
    map.Insert(2, "Two");
    map.Insert(3, "Three");

    // ����� ������ AVL
    map.PrintTreeAVL();
}

