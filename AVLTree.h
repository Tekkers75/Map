#pragma once

//@author Саранчин К.А.

#include"TreeNode.h"
#include"AVLTreeNode.h"
template <class T>
class AVLTree
{
private:
    //указатель на корень
    AVLTreeNode<T>* root;


public:
    //конструктор
    AVLTree(const T& item) : root(new AVLTreeNode<T>(item, nullptr, nullptr)) {}
    AVLTree() : root(nullptr)
    {
    }

    AVLTreeNode<T>* GetRoot() const{
        return root;
    }

    // вставка нового узла
    void Insert(const T& item)
    {
        root = root->AddNodeAVL(item);

    }
    //удаление узла
    void Remove(const T& item) {
        root = root->Remove(item);
    }

    //печать дерева
    void PrintTreeAVL() {
        PrintTree(root, 0);
    }
    //поиск по значению
    AVLTreeNode<T>* Find(const T& item) {
        return dynamic_cast<AVLTreeNode<T>*>(Search(root, item, 0));
    }
    //подсчет глубины (уровней) дерева
    int Height() {
        return Depth(root);
    }
    //подсчет узлов дерева
    int CountNode() {
        return CountNodes(root);
    }
    //удаление дерева
    void DeleteAVLTree() {
        DeleteTree(root);
    }

    //печать дерева в массив в проходе LNR
    void AddNodesToArray(T arr[]) {
        PrintArr(root, arr);
    }
    //деструктор

};
