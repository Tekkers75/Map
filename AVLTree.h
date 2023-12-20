#pragma once

//@author �������� �.�.

#include"TreeNode.h"
#include"AVLTreeNode.h"
template <class T>
class AVLTree
{
private:
    //��������� �� ������
    AVLTreeNode<T>* root;


public:
    //�����������
    AVLTree(const T& item) : root(new AVLTreeNode<T>(item, nullptr, nullptr)) {}
    AVLTree() : root(nullptr)
    {
    }

    AVLTreeNode<T>* GetRoot() const{
        return root;
    }

    // ������� ������ ����
    void Insert(const T& item)
    {
        root = root->AddNodeAVL(item);

    }
    //�������� ����
    void Remove(const T& item) {
        root = root->Remove(item);
    }

    //������ ������
    void PrintTreeAVL() {
        PrintTree(root, 0);
    }
    //����� �� ��������
    AVLTreeNode<T>* Find(const T& item) {
        return dynamic_cast<AVLTreeNode<T>*>(Search(root, item, 0));
    }
    //������� ������� (�������) ������
    int Height() {
        return Depth(root);
    }
    //������� ����� ������
    int CountNode() {
        return CountNodes(root);
    }
    //�������� ������
    void DeleteAVLTree() {
        DeleteTree(root);
    }

    //������ ������ � ������ � ������� LNR
    void AddNodesToArray(T arr[]) {
        PrintArr(root, arr);
    }
    //����������

};
