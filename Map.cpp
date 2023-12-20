#include <string>
#include <iostream>
#include "Map.h"


using namespace std;
int main() {

    setlocale(LC_ALL, "ru");
    //Dictionary<int, string> dict;
    Dictionary<int, int> dict;
    ///*   dict.Insert(42, "Иван");
    //   dict.Insert(55, "Филипп");
    //   dict.Insert(17, "Савелий");*/
    dict.Insert(42, 6);
    dict.Insert(55, 12);
    dict.Insert(17, 3);
    dict.Insert(42, 6);
    dict.Insert(55, 12);
    dict.Insert(17, 3);
    dict.Insert(42, 6);
    dict.Insert(55, 12);
    dict.Insert(17, 3);

    //std::cout << "Поиск по ключу " << dict.Get(42) << std::endl;




    dict.PrintTreeAVL();

    /* dict.Remove(55);
     dict.PrintTreeAVL();*/
    return 0;
}