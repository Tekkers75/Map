#include <string>
#include <iostream>
#include "Map.h"


using namespace std;
int main() {

    setlocale(LC_ALL, "ru");
    Map<int, int> map;
    map.Insert(42, 6);
    map.Insert(55, 12);
    map.Insert(17, 3);

    map.Remove(55);
    int b;
    bool a = map.Find(b = 43);

    if (a == true) {
        cout << "Ключ" << " " << b << " " << "найден," << " ";
        cout << "его значение: " << map.Get(b) << endl;
    }
    else {
        cout << "Ключ" << " " << b << " " << "не найден" << " " << endl;
    }

   //cout << "Поиск по ключу " << dict.Get(42) << endl;




    map.PrintTreeAVL();

    /* dict.Remove(55);
     dict.PrintTreeAVL();*/
    return 0;
}