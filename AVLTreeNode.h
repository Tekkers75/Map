#pragma once

//@author Саранчин К.А.
#include"TreeNode.h"
//узел AVL-дерева   
template <class T>
class AVLTreeNode :public TreeNode<T> {
private:
    //Фактор баланса( разница высот левого и правого поддеревьев)
    int balanceFactor;

public:
    //конструктор класса

    AVLTreeNode(const T& value, TreeNode<T>* leftChild = nullptr, TreeNode<T>* rightChild = nullptr)
        : TreeNode<T>(value, leftChild, rightChild), balanceFactor(0)
    {
    }
    //левое поддерево
    AVLTreeNode<T>* Left() const { return dynamic_cast<AVLTreeNode<T>*>(this->left); }
    //правое поддерево
    AVLTreeNode<T>* Right() const { return dynamic_cast<AVLTreeNode<T>*>(this->right); }
    //получение фактора баланса
    int GetBalanceFactor() const { return balanceFactor; }
    //установка фактора баланса
    void SetBalanceFactor(int factor) { balanceFactor = factor; }
    //методы,позволяющие установить указатели на правое и левое поддеревья
    void SetRight(AVLTreeNode<T>* rightNode)
    {
        this->right = rightNode;
    }
    void SetLeft(AVLTreeNode<T>* leftNode)
    {
        this->left = leftNode;
    }

    //получение высоты дерева
    int GetHeight(AVLTreeNode<T>* node) {
        //если корень пуст, высота =-1
        if (node == nullptr) {
            return -1;
        }
        //рекурсивно вызываем функцию для поддеревьев
        int leftHeight = GetHeight(node->Left());
        int rightHeight = GetHeight(node->Right());

        //корень+ макс.поддерево
        return 1 + max(leftHeight, rightHeight);
    }
    //вычисление баланс фактора
    int GetBalanceFactor(AVLTreeNode<T>* node) {
        //если корень пуст,вернуть 0
        if (node == nullptr) {
            return 0;
        }
        //баланс фактор= высота правого поддерева - высота левого
        return GetHeight(node->Right()) - GetHeight(node->Left());
    }

       //левый поворот
    AVLTreeNode<T>* RotateLeft(AVLTreeNode<T>* node) {
        //Проверяем, что node и его правое поддерево не пусты, чтобы поворот был возможен.
        //Если это не так, мы просто возвращаемся из функции.
        if (node == nullptr || node->right == nullptr)
        {
            return nullptr;
        }
        //Создаем новый указатель newRoot и присваиваем ему правое поддерево узла node.
        AVLTreeNode<T>* newRoot = node->Right();
        // изменяем указатели, чтобы правое поддерево newRoot стало левым поддеревом узла node,
        //  а node стал левым дочерним узлом newRoot
        node->SetRight(newRoot->Left());
        newRoot->SetLeft(node);
        //обновляем указатель node на новый корень newRoot
        node = newRoot;
        return node;
    }

    //правый поворот
    AVLTreeNode<T>* RotateRight(AVLTreeNode<T>* node) {
        //Проверяем, что node и его левое поддерево не пусты, чтобы поворот был возможен.
       //Если это не так, мы просто возвращаемся из функции.
        if (node == nullptr || node->Left() == nullptr)
        {
            return nullptr;
        }
        // Создаем новый указатель newRoot и присваиваем ему левое поддерево узла node
        AVLTreeNode<T>* newRoot = node->Left();
        //изменяем указатели, чтобы левое поддерево newRoot стало правым поддеревом узла node,
         // а node стал правым дочерним узлом newRoot
        node->SetLeft(newRoot->Right());
        newRoot->SetRight(node);
        //обновляем указатель node на новый корень newRoot
        node = newRoot;
        return node;
    }
    // добавление узла в дерево
    AVLTreeNode<T>* AddNodeAVL(const T& item)
    { //если текущий узел пуст, значит дерево пустое
        if (this == nullptr)
        {//создаем новый узел
            return new AVLTreeNode<T>(item);
        }
        //Если значение item меньше значения текущего узла (this->data)
        if (item < this->data)
        {//рекурсивно вызываем AddNodeAVL для левого поддерева текущего узла,
         //используя метод Left(), и устанавливаем его результат в качестве левого потомка текущего узла, используя метод SetLeft()
            this->SetLeft(dynamic_cast<AVLTreeNode<T>*>(this->Left()->AddNodeAVL(item)));
        }
        //Если значение item больше значения текущего узла
        else if (item > this->data)
        {
            //Рекурсивно вызываем AddNodeAVL для правого поддерева текущего узла, используя метод Right(),
            //  и устанавливаем его результат в качестве правого потомка текущего узла, используя метод SetRight().
            this->SetRight(dynamic_cast<AVLTreeNode<T>*>(this->Right()->AddNodeAVL(item)));
        }
        //вызываем перебалансировку для текущего узла
        return BalanceTree(this);
    }
    //перебалансировка дерева
    AVLTreeNode<T>* BalanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        int balanceFactor = GetBalanceFactor(node);

        // Если дерево имеет левый наклон
        if (balanceFactor == -2) {
            // Если левое поддерево имеет правый наклон, сначала делаем левый поворот для левого поддерева
            if (GetBalanceFactor(node->Left()) > 0) {
                node->SetLeft(RotateLeft(node->Left()));
            }
            // Затем делаем правый поворот для текущего узла
            return RotateRight(node);
        }
        // Если дерево имеет правый наклон
        else if (balanceFactor == 2) {
            // Если правое поддерево имеет левый наклон, сначала делаем правый поворот для правого поддерева
            if (GetBalanceFactor(node->Right()) < 0) {
                node->SetRight(RotateRight(node->Right()));
            }
            // Затем делаем левый поворот для текущего узла
            return RotateLeft(node);
        }
        return node;
    }

    //удаление узла бинарного дерева
    template<class T>
    AVLTreeNode<T>* Remove(const T& data) {
        AVLTreeNode<T>* root = this;
        //указатель, parent, который будет хранить родителя удаляемого узла
        AVLTreeNode<T>* parent;

        if (root == nullptr) {
            // Дерево пустое или достигнут конец ветки (лист без значения)
            return nullptr;
        }

        if (data < root->data) {
            // рекурсивно вызываем Remove для левого поддерева текущего узла и устанавливаем его результат в качестве левого потомка текущего узла с помощью метода SetLeft()
            root->SetLeft(dynamic_cast<AVLTreeNode<T>*> (root->Left()->Remove(data)));
        }
        else if (data > root->data) {
            // рекурсивно вызываем Remove для правого поддерева текущего узла и устанавливаем его результат в качестве правого потомка текущего узла с помощью метода SetRight()
            root->SetRight(dynamic_cast<AVLTreeNode<T>*> (root->Right()->Remove(data)));
        }
        else {
            // Найден узел, который нужно удалить

            if (root->Left() == nullptr && root->Right() == nullptr) {
                // Узел является листом (не имеет потомков)
                delete root;
                root = nullptr;
            }
            else if (root->Left() == nullptr) {
                // Узел имеет только правого потомка
                // Сохраняем указатель на текущий узел
                parent = root;
                // Перемещаем правого потомка на место текущего узла
                root = root->Right();
                // Удаляем текущий узел
                delete parent;
            }
            else if (root->Right() == nullptr) {
                // Узел имеет только левого потомка
                // Сохраняем указатель на текущий узел
                parent = root;
                // Перемещаем левого потомка на место текущего узла
                root = root->Left();
                // Удаляем текущий узел
                delete parent;
            }
            else {


                // Узел имеет оба потомка
              // Находим узел с минимальным значением в правом поддереве текущего узла
             // и сохраняем его в переменную successor
                AVLTreeNode<T>* successor = dynamic_cast<AVLTreeNode<T>*>(SuccMin(root->Right()));
                // Заменяем значение текущего узла значением преемника
                root->data = successor->data;
                // Если преемник является непосредственным правым потомком текущего узла
                if (successor == root->Right()) {
                    // устанавливаем его правого потомка в качестве правого потомка текущего узла
                    root->SetRight(successor->Right());
                }
                else {
                    // Если преемник не является непосредственным правым потомком текущего узла,
                // находим его родителя, пропуская его в левом поддереве, и устанавливаем его левого потомка
                // в качестве правого потомка преемника
                    AVLTreeNode<T>* successorParent = root->Right();
                    while (successorParent->Left() != successor) {
                        successorParent = successorParent->Left();
                    }
                    successorParent->SetLeft(successor->Right());
                }

                delete successor;

            }
        }
        //вызываем перебалансировку 
        return BalanceTree(root);
    }

    AVLTreeNode<T>* CopyAVLTree(AVLTreeNode<T>* node) {
        return dynamic_cast<AVLTreeNode<T>*>(CopyTree(node));
    }
};
