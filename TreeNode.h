#pragma once

//@author Maltseva K.V.

#include <cassert>
#include <queue>
#include<functional>
#include<stack>
using namespace std;

// ���������� ������� ��� ���� ��������� ������
template <class T>
struct TreeNode
{

    // ��������� ������ � ������� �������� �����
    TreeNode<T>* left;
    TreeNode<T>* right;


    // �������� �������, ����������� ����������
    T data;

    // ����������� �������������� ���� ������ � ����������
    // �������� NULL ������������� ������� ���������
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

    // ������ ������� � ����� ����������
    TreeNode<T>* Left() const { return left; }
    TreeNode<T>* Right() const { return right; }


    virtual ~TreeNode() {};
};

//�������� ������
template <class T>
void DeleteTree(TreeNode<T>* root) {
    if (root == nullptr)
        return;

    DeleteTree(root->Left());
    DeleteTree(root->Right());

    delete root;


}
//������������ ������������ ������ ���������� ����� �����
template<class T>
void DeleteTreeNode(TreeNode<T>* node) {
    delete node;
}

//������ ������ ����
template <class T>
void PrintNode(TreeNode<T>* node) {
    if (node == nullptr)
    {
        cout << "���� ����" << endl;
    }
    else
    {
        cout << node->data << "  ";
    }
}

//������� ������� ������,�.� �����, ������� �� ����� ��������
template <class T>
void CountLeaf(TreeNode<T>* t, int& count) {
    // ������������� ��������� ������ �����������
    if (t != nullptr)
    {
        CountLeaf(t->Left(), count); //������ ����� ���������
        CountLeaf(t->Right(), count);// ������ ������ ���������

        // ���������,�������� �� ������ ���� ������
        //���� ��, �� ���������� ���������� ���������� count
        if (t->Left() == nullptr && t->Right() == nullptr)
            count++;
    }

}
//������� ����� ������
template<class T>
int CountNodes(TreeNode<T>* t) {
    int left_value, right_value;
    //���� � ������ � ����� ������� �����
    if (t->Left() == nullptr && t->Right() == nullptr)
        return 1;
    //���� ����� ��������� �� ����, �������
    if (t->Left() != nullptr)
        left_value = CountNodes(t->Left());
    //����� ����
    else left_value = 0;
    //���� ������ ��������� �� ����, �������
    if (t->Right() != nullptr)
        right_value = CountNodes(t->Right());
    //����� ����
    else right_value = 0;
    //������� ����� ����� ����� + �������
    return left_value + right_value + 1;
}


//������� ������� (�������) ������
template<class T>
int Depth(TreeNode<T>* t) {
    int depthLeft, depthRight, depthValue;
    //���� ������ ������,��� �������=-1
    if (t == nullptr)
    {
        depthValue = -1;
    }
    else
        //�������� ����� �����������
        //���������� ������� ������� � ������ �����������
        //����������� �� ���������������
    {
        depthLeft = Depth(t->Left());
        depthRight = Depth(t->Right());
        //��������� ��������(�������? true:false)
        //�������� ������������ ����� depthLeft � depthRight
        depthValue = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthValue;
}
//���������� ������ ���� �� 10
template <class T>
void Inc(TreeNode<T>* node) {
    node->data += 10;
}

//���������� ������ ���� � �������
template <class T>
void Square(TreeNode<T>* node) {
    node->data = node->data * node->data;
}
//�������� ����������� ����������� ����� ������(����� �����) LRN
template <class T>
void Postorder_print(TreeNode<T>* root, void(*func)(TreeNode<T>*)) {

    //����������� ����������� ����������� �� ������ ���������
    if (root == nullptr)
        return;
    Postorder_print(root->Left(), func);//���������� �� ������ ���������
    Postorder_print(root->Right(), func);//���������� �� ������� ���������
    func(root);

}

//������������ ����������� ����� ������(����� �������)
template <class T>
void Inorder_print(TreeNode<T>* node, void(*func)(TreeNode<T>*)) {
    //����������� ����������� ����������� �� ������ ���������
    if (node != nullptr) {
        Inorder_print(node->Left(), func);//���������� �� ������ ���������
        func(node);//�������� ����
        Inorder_print(node->Right(), func);//���������� �� ������� ���������
    }
}
//����������� ������ � ������ �������(������ ����)
template <class T>
void Preorder_print(TreeNode<T>* node, void(*func)(TreeNode<T>*)) {

    if (node != nullptr) {
        func(node);//�������� ����
        Preorder_print(node->Left(), func);//���������� �� ������ ���������
        Preorder_print(node->Right(), func);//���������� �� ������� ���������
    }
}



//���������� ����� ��������
const int indentBlock = 6;
//�������� num�������� � ������� ������
void IndentBlanks(int num) {
    for (int i = 0; i < num; i++)
        cout << "  ";
}
//������ ������ �����,��������� RNL- �����������
template<class T>
void PrintTree(TreeNode<T>* node, int level) {
    //�������� ������ ������ ���� node, ���� �� �� ����� nullptr
    if (node != nullptr)
    {
        //�������� ������ ��������� ���� node
        PrintTree(node->Left(), level);
        //��������� ������� ������� � ������� ���� ������
        //IndentBlanks(indentBlock * level);
        cout << node->data << endl;
        //�������� ����� ��������� ���� node
        PrintTree(node->Right(), level);
    }
}




//���������� ����� ����� � ������ ������
template <class T>
TreeNode<T>* AddNode(TreeNode<T>* node, const T& item)

{
    //���� ����� �� ����������

    if (node == nullptr)

    { //�������� �� � ������� � ��� ������

        return new TreeNode<int>(item, nullptr, nullptr);

    }


    if (item < node->data) {
        // ���������� ��������� �������� � ����� ���������
        node->left = AddNode(node->left, item);
    }
    else if (item > node->data) {
        // ���������� ��������� �������� � ������ ���������
        node->right = AddNode(node->right, item);
    }

    // ���� �������� ��� ������������ � ������, ������ �� ������

    return node;
}

//������ ������ � ������
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
//���������� ��������� ������ �� �������, �������� � ������� �������� ����.�������( ������,����� � ������ �������,������� ������,������� ������� � �.�)
template<class T>
TreeNode<T>* BinaryTreeFromVector(vector<T> vec) {
    // �������� ��������� ���� � ������ ��������� �������
    TreeNode<int>* root = new TreeNode<int>(vec.at(0), nullptr, nullptr);
    for (int i = 0; i < vec.size(); i++) {
        int left = 2 * i + 1;// ���������� ������� ������ �������
        int right = left + 1; // ���������� ������� ������� �������
        if (left < vec.size())
            AddNode(root, vec.at(i));
        if (right < vec.size())
            AddNode(root, vec.at(i));

    }
    //���������� ������
    return root;
    PrintTree(root, 0);
}


//����� ���� �� ��������(����� ��� ������)
template<class T>
TreeNode<T>* Search(TreeNode<T>* node, const T& data, int level = 0) {
    if (node == nullptr) {
        // ������ ������ ��� ��������� ����� ����� (���� ��� ��������)
        return nullptr; // ���������� -1, ����� �������, ��� ������� �� ������
    }

    if (data == node->data) {
        // �������� ������� � ������� ����
        return node;
    }
    else if (data < node->data) {
        // ���������� ���� �������� � ����� ���������
        return Search(node->left, data, level + 1);
    }
    else {
        // ���������� ���� �������� � ������ ���������
        return Search(node->right, data, level + 1);
    }
}

//�������� ���� ��������� ������
template<class T>
TreeNode<T>* Remove(TreeNode<T>* root, const T& data) {
    //��������, parent, ������� ����� ��������� �������� ���������� ����
    TreeNode<T>* parent;

    if (root == nullptr) {
        // ������ ������ ��� ��������� ����� ����� (���� ��� ��������)
        return nullptr;
    }

    if (data < root->data) {
        // ���������� ������� �������� �� ������ ���������
        root->left = Remove(root->left, data);
    }
    else if (data > root->data) {
        // ���������� ������� �������� �� ������� ���������
        root->right = Remove(root->right, data);
    }
    else {
        // ������ ����, ������� ����� �������

        if (root->left == nullptr && root->right == nullptr) {
            // ���� �������� ������ (�� ����� ��������)
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            // ���� ����� ������ ������� �������

            parent = root;
            root = root->right;
            delete parent;
        }
        else if (root->right == nullptr) {
            // ���� ����� ������ ������ �������

            parent = root;
            root = root->left;
            delete parent;
        }
        else {
            // ���� ����� ��� �������

            TreeNode<T>* parent = SuccMin(root->right);
            root->data = parent->data;
            root->right = Remove(root->right, parent->data);
        }
    }

    return root;
}
//����� ���������� �����������
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
//����������� ������
template <class T>
TreeNode<T>* CopyTree(TreeNode<T>* node) {
    //������� ��������� �� ����� ����
    TreeNode<T>* newlptr, * newrptr, * newnode;
    //���� node ����� nullptr, �� ��� ������� ������ ��������
    if (node == nullptr)
        return nullptr;
    //���� � ���� node ���� ����� ������� (node->left), 
    // ���������� ����������� ����� ������� CopyTree ��� ����������� ������ ���������. ��������� ����������� � newlptr.
    if (node->left != nullptr)
        newlptr = CopyTree(node->left);
    else
        newlptr = nullptr;
    //���� � ���� node ���� ������ �������(node->right), 
    // ���������� ����������� ����� ������� CopyTree ��� ����������� ������� ���������.��������� ����������� � newrptr.
    if (node->right != nullptr)
        newrptr = CopyTree(node->right);
    else newrptr = nullptr;
    // ��������� ����� ���� newnode � ������� node->data � ����������� 
    // �� ������������� ����� � ������ ����������(newlptr � newrptr ��������������).
    //����� ���� newnode ���������� �������� ����� �������������� ���������.
    newnode = new TreeNode<int>(node->data, newlptr, newrptr);
    return newnode;
}
//������ ������ � ������ � �������������� �������
template <class T>
void BFS(TreeNode<T>* root, void(*func)(TreeNode<T>*)) {
    if (root == nullptr)
        return;
    //������� ������ �������
    queue <TreeNode<T>*> q;
    //�������� � ������� �������� ����
    q.push(root);
    // ���� �� ��� ���, ���� queue �� ������ ������
    while (!q.empty()) {
        //������� ��������� �� ������ �������
        TreeNode<T>* current = q.front();
        //��������� ������ �������
        q.pop();
        // ��������� �������� ����
        func(current);
        //���������� ������ � ������� ������� �������� ���� � �������
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

//������ ������ � ������ � �������������� �������
template <class T>
void BFS(TreeNode<T>* root, std::function<void(TreeNode<T>&)> f) {
    if (root == nullptr)
        return;
    //������� ������ �������
    queue <TreeNode<T>*> q;
    //�������� � ������� �������� ����
    q.push(root);
    // ���� �� ��� ���, ���� queue �� ������ ������
    while (!q.empty()) {
        //������� ��������� �� ������ �������
        TreeNode<T>* current = q.front();
        //��������� ������ �������
        q.pop();
        // ��������� �������� ����
        f(*current);
        //���������� ������ � ������� ������� �������� ���� � �������
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}
