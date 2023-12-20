#pragma once

//@author Maltseva K.V.

#include <cassert>
#include <queue>
#include<functional>
#include<stack>
using namespace std;

// объявление объекта для узла бинарного дерева
template <class T>
struct TreeNode
{

    // указатели левого и правого дочерних узлов
    TreeNode<T>* left;
    TreeNode<T>* right;


    // открытый элемент, допускающий обновление
    T data;

    // конструктор инициализирует поля данных и указателей
    // значение NULL соответствует пустому поддереву
    TreeNode(const T& item, TreeNode<T>* lptr, TreeNode<T>* rptr)
        //: data(item), left(lptr), right(rptr)
    {
        data = item;
        left = lptr;
        right = rptr;
    }
    TreeNode() {
        data = NULL;
        left = nullptr;
        right = nullptr;
    }

    // методы доступа к полям указателей
    TreeNode<T>* Left() const { return left; }
    TreeNode<T>* Right() const { return right; }


    virtual ~TreeNode() {};
};

//удаление дерева
template <class T>
void DeleteTree(TreeNode<T>* root) {
    if (root == nullptr)
        return;

    DeleteTree(root->Left());
    DeleteTree(root->Right());

    delete root;


}
//освобождение динамической памяти занимаемой одним узлом
template<class T>
void DeleteTreeNode(TreeNode<T>* node) {
    delete node;
}

//печать одного узла
template <class T>
void PrintNode(TreeNode<T>* node) {
    if (node == nullptr)
    {
        cout << "Узел пуст" << endl;
    }
    else
    {
        cout << node->data << "  ";
    }
}

//подсчет листьев дерева,т.е узлов, которые не имеют потомков
template <class T>
void CountLeaf(TreeNode<T>* t, int& count) {
    // использование обратного метода прохождения
    if (t != nullptr)
    {
        CountLeaf(t->Left(), count); //пройти левое поддерево
        CountLeaf(t->Right(), count);// пройти правое поддерево

        // проверить,является ли данный узел листом
        //если да, то произвести приращение переменной count
        if (t->Left() == nullptr && t->Right() == nullptr)
            count++;
    }

}
//подсчет узлов дерева
template<class T>
int CountNodes(TreeNode<T>* t) {
    int left_value, right_value;
    //если в правой и левой стороне пусто
    if (t->Left() == nullptr && t->Right() == nullptr)
        return 1;
    //если левое поддерево не ноль, считаем
    if (t->Left() != nullptr)
        left_value = CountNodes(t->Left());
    //иначе ноль
    else left_value = 0;
    //если правое поддерево не ноль, считаем
    if (t->Right() != nullptr)
        right_value = CountNodes(t->Right());
    //иначе ноль
    else right_value = 0;
    //считаем общее число узлов + вершина
    return left_value + right_value + 1;
}


//подсчет глубины (уровней) дерева
template<class T>
int Depth(TreeNode<T>* t) {
    int depthLeft, depthRight, depthValue;
    //если дерево пустое,его глубина=-1
    if (t == nullptr)
    {
        depthValue = -1;
    }
    else
        //обратный метод прохождения
        //вычисление глубины правого и левого поддеревьев
        //возвращение их результирующего
    {
        depthLeft = Depth(t->Left());
        depthRight = Depth(t->Right());
        //тернарный оператор(условие? true:false)
        //выбирает максимальное между depthLeft и depthRight
        depthValue = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthValue;
}
//увеличение данных узла на 10
template <class T>
void Inc(TreeNode<T>* node) {
    node->data += 10;
}

//возведение данных узла в квадрат
template <class T>
void Square(TreeNode<T>* node) {
    node->data = node->data * node->data;
}
//обратное рекурсивное прохождение узлов дерева(снизу вверх) LRN
template <class T>
void Postorder_print(TreeNode<T>* root, void(*func)(TreeNode<T>*)) {

    //рекурсивное прохождение завершается на пустом поддереве
    if (root == nullptr)
        return;
    Postorder_print(root->Left(), func);//спуститься по левому поддереву
    Postorder_print(root->Right(), func);//спуститься по правому поддереву
    func(root);

}

//симметричное прохождение узлов дерева(слева направо)
template <class T>
void Inorder_print(TreeNode<T>* node, void(*func)(TreeNode<T>*)) {
    //рекурсивное прохождение завершается на пустом поддереве
    if (node != nullptr) {
        Inorder_print(node->Left(), func);//спуститься по левому поддереву
        func(node);//посетить узел
        Inorder_print(node->Right(), func);//спуститься по правому поддереву
    }
}
//прохождение дерева в прямом порядке(сверху вниз)
template <class T>
void Preorder_print(TreeNode<T>* node, void(*func)(TreeNode<T>*)) {

    if (node != nullptr) {
        func(node);//посетить узел
        Preorder_print(node->Left(), func);//спуститься по левому поддереву
        Preorder_print(node->Right(), func);//спуститься по правому поддереву
    }
}



//промежуток между уровнями
const int indentBlock = 6;
//вставить numпробелов в текущей строке
void IndentBlanks(int num) {
    for (int i = 0; i < num; i++)
        cout << "  ";
}
//печать дерева боком,используя RNL- прохождение
template<class T>
void PrintTree(TreeNode<T>* node, int level) {
    //печатать правое дерево узла node, пока он не равет nullptr
    if (node != nullptr)
    {
        //печатать правое поддерево узла node
        PrintTree(node->Right(), level + 1);
        //выровнять текущий уровень и вывести поле данных
        IndentBlanks(indentBlock * level);
        cout << node->data << endl;
        //печатать левое поддерево узла node
        PrintTree(node->Left(), level + 1);
    }
}




//добавление новых узлов в дерево поиска
template <class T>
TreeNode<T>* AddNode(TreeNode<T>* node, const T& item)

{
    //Если ветки не существует

    if (node == nullptr)

    { //создадим ее и зададим в нее данные

        return new TreeNode<int>(item, nullptr, nullptr);

    }


    if (item < node->data) {
        // Рекурсивно вставляем значение в левое поддерево
        node->left = AddNode(node->left, item);
    }
    else if (item > node->data) {
        // Рекурсивно вставляем значение в правое поддерево
        node->right = AddNode(node->right, item);
    }

    // Если значение уже присутствует в дереве, ничего не делаем

    return node;
}
//
//template<class T>
//int PrintArr(TreeNode<T>* t, T arr[], int i) {
//    if (t == nullptr) {
//        return i;
//    }
//    if (t->left != nullptr) {
//        i = PrintArr(t->left, arr, i);
//    }
//
//    arr[i] = t->data;
//    i++;
//
//    if (t->right != nullptr) {
//        i = PrintArr(t->right, arr, i);
//    }
//    return i;
//}

//печать дерева в массив
template<class T>
T* PrintArr(TreeNode<T>* t, T*& arr) {
    if (t == nullptr) {
        return arr;
    }
    if (t->left != nullptr) {
        arr = PrintArr(t->left, arr);
    }

    *arr = t->data;
    arr++;

    if (t->right != nullptr) {
        arr = PrintArr(t->right, arr);
    }
    return arr;
}
//построение бинарного дерева из массива, элементы в котором хранятся след.образом( корень,левый и правый потомки,потомки левого,потомки правого и т.д)
template<class T>
TreeNode<T>* BinaryTreeFromVector(vector<T> vec) {
    // Создание корневого узла с первым элементом вектора
    TreeNode<int>* root = new TreeNode<int>(vec.at(0), nullptr, nullptr);
    for (int i = 0; i < vec.size(); i++) {
        int left = 2 * i + 1;// Вычисление индекса левого потомка
        int right = left + 1; // Вычисление индекса правого потомка
        if (left < vec.size())
            AddNode(root, vec.at(i));
        if (right < vec.size())
            AddNode(root, vec.at(i));

    }
    //возвращаем корень
    return root;
    PrintTree(root, 0);
}


////поиск узла по значению
//template<class T>
//bool Search(TreeNode<T>* node, const T& data) {
//    if (node == nullptr) {
//        // Дерево пустое или достигнут конец ветки (лист без значения)
//        return false;
//    }
//
//    if (data == node->data) {
//        // Значение найдено в текущем узле
//        return true;
//    }
//    else if (data < node->data) {
//        // Рекурсивно ищем значение в левом поддереве
//        return Search(node->left, data);
//    }
//    else {
//        // Рекурсивно ищем значение в правом поддереве
//        return Search(node->right, data);
//    }
//}

//поиск узла по значению(вывод его уровня)
template<class T>
TreeNode<T>* Search(TreeNode<T>* node, const T& data, int level = 0) {
    if (node == nullptr) {
        // Дерево пустое или достигнут конец ветки (лист без значения)
        return nullptr; // Возвращаем -1, чтобы указать, что элемент не найден
    }

    if (data == node->data) {
        // Значение найдено в текущем узле
        return node;
    }
    else if (data < node->data) {
        // Рекурсивно ищем значение в левом поддереве
        return Search(node->left, data, level + 1);
    }
    else {
        // Рекурсивно ищем значение в правом поддереве
        return Search(node->right, data, level + 1);
    }
}

//удаление узла бинарного дерева
template<class T>
TreeNode<T>* Remove(TreeNode<T>* root, const T& data) {
    //указател, parent, который будет храненить родителя удаляемого узла
    TreeNode<T>* parent;

    if (root == nullptr) {
        // Дерево пустое или достигнут конец ветки (лист без значения)
        return nullptr;
    }

    if (data < root->data) {
        // Рекурсивно удаляем значение из левого поддерева
        root->left = Remove(root->left, data);
    }
    else if (data > root->data) {
        // Рекурсивно удаляем значение из правого поддерева
        root->right = Remove(root->right, data);
    }
    else {
        // Найден узел, который нужно удалить

        if (root->left == nullptr && root->right == nullptr) {
            // Узел является листом (не имеет потомков)
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            // Узел имеет только правого потомка

            parent = root;
            root = root->right;
            delete parent;
        }
        else if (root->right == nullptr) {
            // Узел имеет только левого потомка

            parent = root;
            root = root->left;
            delete parent;
        }
        else {
            // Узел имеет оба потомка

            TreeNode<T>* parent = SuccMin(root->right);
            root->data = parent->data;
            root->right = Remove(root->right, parent->data);
        }
    }

    return root;
}
//поиск следующего наименьшего
template<class T>
TreeNode<T>* SuccMin(TreeNode<T>* root) {
    if (root == nullptr) {
        return nullptr;
    }
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}
//копирование дерева
template <class T>
TreeNode<T>* CopyTree(TreeNode<T>* node) {
    //создаем указатели на новые узлы
    TreeNode<T>* newlptr, * newrptr, * newnode;
    //Если node равен nullptr, то это базовый случай рекурсии
    if (node == nullptr)
        return nullptr;
    //Если у узла node есть левый потомок (node->left), 
    // вызывается рекурсивный вызов функции CopyTree для копирования левого поддерева. Результат сохраняется в newlptr.
    if (node->left != nullptr)
        newlptr = CopyTree(node->left);
    else
        newlptr = nullptr;
    //Если у узла node есть правый потомок(node->right), 
    // вызывается рекурсивный вызов функции CopyTree для копирования правого поддерева.Результат сохраняется в newrptr.
    if (node->right != nullptr)
        newrptr = CopyTree(node->right);
    else newrptr = nullptr;
    // Создается новый узел newnode с данными node->data и указателями 
    // на скопированные левое и правое поддеревья(newlptr и newrptr соответственно).
    //Новый узел newnode становится корневым узлом скопированного поддерева.
    newnode = new TreeNode<int>(node->data, newlptr, newrptr);
    return newnode;
}
//проход дерева в ширину с использованием очереди
template <class T>
void BFS(TreeNode<T>* root, void(*func)(TreeNode<T>*)) {
    if (root == nullptr)
        return;
    //создаем пустую очередь
    queue <TreeNode<T>*> q;
    //помещаем в очередь корневой узел
    q.push(root);
    // цикл до тех пор, пока queue не станет пустой
    while (!q.empty()) {
        //создаем указатель на начало очереди
        TreeNode<T>* current = q.front();
        //извлекаем первый элемент
        q.pop();
        // Обработка текущего узла
        func(current);
        //Добавление левого и правого потомка текущего узла в очередь
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

//проход дерева в ширину с использованием очереди
template <class T>
void BFS(TreeNode<T>* root, std::function<void(TreeNode<T>&)> f) {
    if (root == nullptr)
        return;
    //создаем пустую очередь
    queue <TreeNode<T>*> q;
    //помещаем в очередь корневой узел
    q.push(root);
    // цикл до тех пор, пока queue не станет пустой
    while (!q.empty()) {
        //создаем указатель на начало очереди
        TreeNode<T>* current = q.front();
        //извлекаем первый элемент
        q.pop();
        // Обработка текущего узла
        f(*current);
        //Добавление левого и правого потомка текущего узла в очередь
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}
