#pragma once

//@author �������� �.�.

#include"TreeNode.h"


//���� AVL-������   
template <class T>
class AVLTreeNode :public TreeNode<T> {
private:
    //������ �������( ������� ����� ������ � ������� �����������)
    int balanceFactor;

public:
    //����������� ������

    AVLTreeNode(const T& value, TreeNode<T>* leftChild = nullptr, TreeNode<T>* rightChild = nullptr)
        : TreeNode<T>(value, leftChild, rightChild), balanceFactor(0)
    {
    }
    //����� ���������
    AVLTreeNode<T>* Left() const { return dynamic_cast<AVLTreeNode<T>*>(this->left); }
    //������ ���������
    AVLTreeNode<T>* Right() const { return dynamic_cast<AVLTreeNode<T>*>(this->right); }
    //��������� ������� �������
    int GetBalanceFactor() const { return balanceFactor; }
    //��������� ������� �������
    void SetBalanceFactor(int factor) { balanceFactor = factor; }
    //������,����������� ���������� ��������� �� ������ � ����� ����������
    void SetRight(AVLTreeNode<T>* rightNode)
    {
        this->right = rightNode;
    }
    void SetLeft(AVLTreeNode<T>* leftNode)
    {
        this->left = leftNode;
    }

    //��������� ������ ������
    int GetHeight(AVLTreeNode<T>* node) {
        //���� ������ ����, ������ =-1
        if (node == nullptr) {
            return -1;
        }
        //���������� �������� ������� ��� �����������
        int leftHeight = GetHeight(node->Left());
        int rightHeight = GetHeight(node->Right());

        //������+ ����.���������
        return 1 + max(leftHeight, rightHeight);
    }
    //���������� ������ �������
    int GetBalanceFactor(AVLTreeNode<T>* node) {
        //���� ������ ����,������� 0
        if (node == nullptr) {
            return 0;
        }
        //������ ������= ������ ������� ��������� - ������ ������
        return GetHeight(node->Right()) - GetHeight(node->Left());
    }

       //����� �������
    AVLTreeNode<T>* RotateLeft(AVLTreeNode<T>* node) {
        //���������, ��� node � ��� ������ ��������� �� �����, ����� ������� ��� ��������.
        //���� ��� �� ���, �� ������ ������������ �� �������.
        if (node == nullptr || node->right == nullptr)
        {
            return nullptr;
        }
        //������� ����� ��������� newRoot � ����������� ��� ������ ��������� ���� node.
        AVLTreeNode<T>* newRoot = node->Right();
        // �������� ���������, ����� ������ ��������� newRoot ����� ����� ���������� ���� node,
        //  � node ���� ����� �������� ����� newRoot
        node->SetRight(newRoot->Left());
        newRoot->SetLeft(node);
        //��������� ��������� node �� ����� ������ newRoot
        node = newRoot;
        return node;
    }

    //������ �������
    AVLTreeNode<T>* RotateRight(AVLTreeNode<T>* node) {
        //���������, ��� node � ��� ����� ��������� �� �����, ����� ������� ��� ��������.
       //���� ��� �� ���, �� ������ ������������ �� �������.
        if (node == nullptr || node->Left() == nullptr)
        {
            return nullptr;
        }
        // ������� ����� ��������� newRoot � ����������� ��� ����� ��������� ���� node
        AVLTreeNode<T>* newRoot = node->Left();
        //�������� ���������, ����� ����� ��������� newRoot ����� ������ ���������� ���� node,
         // � node ���� ������ �������� ����� newRoot
        node->SetLeft(newRoot->Right());
        newRoot->SetRight(node);
        //��������� ��������� node �� ����� ������ newRoot
        node = newRoot;
        return node;
    }
    // ���������� ���� � ������
    AVLTreeNode<T>* AddNodeAVL(const T& item)
    { //���� ������� ���� ����, ������ ������ ������
        if (this == nullptr)
        {//������� ����� ����
            return new AVLTreeNode<T>(item);
        }
        //���� �������� item ������ �������� �������� ���� (this->data)
        if (item < this->data)
        {//���������� �������� AddNodeAVL ��� ������ ��������� �������� ����,
         //��������� ����� Left(), � ������������� ��� ��������� � �������� ������ ������� �������� ����, ��������� ����� SetLeft()
            this->SetLeft(dynamic_cast<AVLTreeNode<T>*>(this->Left()->AddNodeAVL(item)));
        }
        //���� �������� item ������ �������� �������� ����
        else if (item > this->data)
        {
            //���������� �������� AddNodeAVL ��� ������� ��������� �������� ����, ��������� ����� Right(),
            //  � ������������� ��� ��������� � �������� ������� ������� �������� ����, ��������� ����� SetRight().
            this->SetRight(dynamic_cast<AVLTreeNode<T>*>(this->Right()->AddNodeAVL(item)));
        }
        //�������� ���������������� ��� �������� ����
        return BalanceTree(this);
    }
    //���������������� ������
    AVLTreeNode<T>* BalanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        int balanceFactor = GetBalanceFactor(node);

        // ���� ������ ����� ����� ������
        if (balanceFactor == -2) {
            // ���� ����� ��������� ����� ������ ������, ������� ������ ����� ������� ��� ������ ���������
            if (GetBalanceFactor(node->Left()) > 0) {
                node->SetLeft(RotateLeft(node->Left()));
            }
            // ����� ������ ������ ������� ��� �������� ����
            return RotateRight(node);
        }
        // ���� ������ ����� ������ ������
        else if (balanceFactor == 2) {
            // ���� ������ ��������� ����� ����� ������, ������� ������ ������ ������� ��� ������� ���������
            if (GetBalanceFactor(node->Right()) < 0) {
                node->SetRight(RotateRight(node->Right()));
            }
            // ����� ������ ����� ������� ��� �������� ����
            return RotateLeft(node);
        }
        return node;
    }

    //�������� ���� ��������� ������
    template<class T>
    AVLTreeNode<T>* Remove(const T& data) {
        AVLTreeNode<T>* root = this;
        //���������, parent, ������� ����� ������� �������� ���������� ����
        AVLTreeNode<T>* parent;

        if (root == nullptr) {
            // ������ ������ ��� ��������� ����� ����� (���� ��� ��������)
            return nullptr;
        }

        if (data < root->data) {
            // ���������� �������� Remove ��� ������ ��������� �������� ���� � ������������� ��� ��������� � �������� ������ ������� �������� ���� � ������� ������ SetLeft()
            root->SetLeft(dynamic_cast<AVLTreeNode<T>*> (root->Left()->Remove(data)));
        }
        else if (data > root->data) {
            // ���������� �������� Remove ��� ������� ��������� �������� ���� � ������������� ��� ��������� � �������� ������� ������� �������� ���� � ������� ������ SetRight()
            root->SetRight(dynamic_cast<AVLTreeNode<T>*> (root->Right()->Remove(data)));
        }
        else {
            // ������ ����, ������� ����� �������

            if (root->Left() == nullptr && root->Right() == nullptr) {
                // ���� �������� ������ (�� ����� ��������)
                delete root;
                root = nullptr;
            }
            else if (root->Left() == nullptr) {
                // ���� ����� ������ ������� �������
                // ��������� ��������� �� ������� ����
                parent = root;
                // ���������� ������� ������� �� ����� �������� ����
                root = root->Right();
                // ������� ������� ����
                delete parent;
            }
            else if (root->Right() == nullptr) {
                // ���� ����� ������ ������ �������
                // ��������� ��������� �� ������� ����
                parent = root;
                // ���������� ������ ������� �� ����� �������� ����
                root = root->Left();
                // ������� ������� ����
                delete parent;
            }
            else {


                // ���� ����� ��� �������
              // ������� ���� � ����������� ��������� � ������ ��������� �������� ����
             // � ��������� ��� � ���������� successor
                AVLTreeNode<T>* successor = dynamic_cast<AVLTreeNode<T>*>(SuccMin(root->Right()));
                // �������� �������� �������� ���� ��������� ���������
                root->data = successor->data;
                // ���� �������� �������� ���������������� ������ �������� �������� ����
                if (successor == root->Right()) {
                    // ������������� ��� ������� ������� � �������� ������� ������� �������� ����
                    root->SetRight(successor->Right());
                }
                else {
                    // ���� �������� �� �������� ���������������� ������ �������� �������� ����,
                // ������� ��� ��������, ��������� ��� � ����� ���������, � ������������� ��� ������ �������
                // � �������� ������� ������� ���������
                    AVLTreeNode<T>* successorParent = root->Right();
                    while (successorParent->Left() != successor) {
                        successorParent = successorParent->Left();
                    }
                    successorParent->SetLeft(successor->Right());
                }

                delete successor;

            }
        }
        //�������� ���������������� 
        return BalanceTree(root);
    }

    AVLTreeNode<T>* CopyAVLTree(AVLTreeNode<T>* node) {
        return dynamic_cast<AVLTreeNode<T>*>(CopyTree(node));
    }
};
