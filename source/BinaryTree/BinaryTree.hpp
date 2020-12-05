#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <queue>

#include "TreeNode.hpp"
#include "../Exception.hpp"
#include "../source/LinkedList/LinkedList.hpp"
#include "../Sequence/Sequence.hpp"
#include "../ArraySequence/ArraySequence.hpp"

using namespace std;


template<typename T>
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void Insert(T value);

    string ToString(string bypass = "KLR");

    TreeNode<T>* Search(T value);

    void DeleteTreeNode(T value);

    template<typename V>
    BinaryTree<V> * Map(V (*function)(T));

    template<typename V>
    V Reduce(V (*function)(T, V));

    BinaryTree<T> *Where(bool (*function)(T));

    LinkedList<TreeNode<T>*>* Thread(string bypass);

    BinaryTree<T> *GetSubTree(T value);

    bool ContainsSubTree(BinaryTree<T>* subTree);

    int Count();

    Sequence<T>* Get();

private:
    TreeNode<T>* root;

    void _DeleteTree(TreeNode<T>* node);

    void _Insert(T value, TreeNode<T>* node);

    string _ToString(string bypass, TreeNode<T>* node);

    TreeNode<T>* _Search(T value, TreeNode<T>* node);

    TreeNode<T>* _Minimum(TreeNode<T>* node);

    TreeNode<T> * _DeleteTreeNode(T value, TreeNode<T>* node);

    template<typename V>
    BinaryTree<V> * _Map(V (*funciton)(T), TreeNode<T> *node, BinaryTree<V> *binaryTree);

    template<typename V>
    V _Reduce(V (*function)(T, V), TreeNode<T> *node, V value);

    BinaryTree<T> *_Where(bool (*function)(T), TreeNode<T> *node, BinaryTree<T> *binaryTree);

    LinkedList<TreeNode<T>*>* _Thread(string bypass, TreeNode<T>* node, LinkedList<TreeNode<T>*>* threadList);

    BinaryTree<T> *_GetSubTree(TreeNode<T>* node, BinaryTree<T> *binaryTree);

    bool _ContainsSubTree(TreeNode<T>* node1, TreeNode<T>* node2);

    int _Count(TreeNode<T>* root);

    Sequence<T>* _Get(TreeNode<T>* node, Sequence<T>* sequence, int* index);
};

template<typename T>
BinaryTree<T>::BinaryTree() {
   this->root = NULL;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    this->_DeleteTree(this->root);
}

template<typename T>
void BinaryTree<T>::_DeleteTree(TreeNode<T> *node) {
    if (node != NULL) {
        this->_DeleteTree(node->left);
        this->_DeleteTree(node->right);
        delete node;
    }
}

template<typename T>
void BinaryTree<T>::Insert(T value) {
    if (this->root != NULL) {
        this->_Insert(value, this->root);
    } else {
        this->root = new TreeNode<T>(value);
        this->root->left = NULL;
        this->root->right = NULL;
    }
}

template<typename T>
void BinaryTree<T>::_Insert(T value, TreeNode<T> *node) {
    if (value <= *node->value) {
        if (node->left != NULL) {
            this->_Insert(value, node->left);
        } else {
            node->left = new TreeNode<T>(value);
            node->left->left = NULL;
            node->left->right = NULL;
        }
    } else if (value > *node->value) {
        if (node->right != NULL) {
            this->_Insert(value, node->right);
        } else {
            node->right = new TreeNode<T>(value);
            node->right->right = NULL;
            node->right->left = NULL;
        }
    }
}

template<typename T>
string BinaryTree<T>::ToString(string bypass) {
    return this->_ToString(bypass, this->root);
}

template<typename T>
string BinaryTree<T>::_ToString(string bypass, TreeNode<T> *node) {
    stringstream strs;

    if (node != NULL) {
        for (int i = 0; i < bypass.length(); i++) {
            switch (bypass[i]) {
                case 'K':
                    strs << "{" << *node->value << "}";
                    break;
                case 'L':
                    if (node->left != NULL) {
                        strs << "(" << this->_ToString(bypass, node->left) << ")";
                    }
                    break;
                case 'R':
                    if (node->right != NULL) {
                        strs << "[" << this->_ToString(bypass, node->right) << "]";
                    }
                    break;
            }
        }
    }

    return strs.str();
}

template<typename T>
TreeNode<T> *BinaryTree<T>::Search(T value) {
    return this->_Search(value, this->root);
}

template<typename T>
TreeNode<T> *BinaryTree<T>::_Search(T value, TreeNode<T> *node) {
    if (node != NULL) {
        if (value == *node->value) {
            return node;
        }

        if (value <= *node->value) {
            return this->_Search(value, node->left);
        } else {
            return this->_Search(value, node->right);
        }
    } else {
        return NULL;
    }
}

template<typename T>
void BinaryTree<T>::DeleteTreeNode(T value) {
    if (this->root == NULL) {
        throw new Exception;
    }

    if (*root->value != value) {
        this->_DeleteTreeNode(value, root);
        return;
    }

    root = this->_DeleteTreeNode(value, root);
}

template<typename T>
TreeNode<T> * BinaryTree<T>::_DeleteTreeNode(T value, TreeNode<T>* node) {

    if (node == NULL) {
        return node;
    }
    if (value < *node->value) {
        node->left = _DeleteTreeNode(value, node->left);
    } else if (value > *node->value) {
        node->right = _DeleteTreeNode(value, node->right);
    } else if (node->left != NULL && node->right != NULL) {
        node->value = this->_Minimum(node->right)->value;
        node->right = this->_DeleteTreeNode(*node->value, node->right);
    } else {
        if (node->left != NULL) {
           node = node->left;
        } else if (node->right != NULL) {
            node = node->right;
        } else {
            node = NULL;
        }
    }

    return node;
}

template<typename T>
TreeNode<T> *BinaryTree<T>::_Minimum(TreeNode<T> *node) {
    if (node->left == NULL) {
        return node;
    }

    return _Minimum(node->left);
}

template<typename T>
template<typename V>
BinaryTree<V> * BinaryTree<T>::Map(V (*function)(T)) {
    return this->_Map(function, this->root, new BinaryTree<V>());
}

template<typename T>
template<typename V>
BinaryTree<V> * BinaryTree<T>::_Map(V (*funciton)(T), TreeNode<T> *node, BinaryTree<V> *binaryTree) {
    if (node != NULL) {
        binaryTree->Insert(funciton(*node->value));
        this->_Map(funciton, node->left, binaryTree);
        this->_Map(funciton, node->right, binaryTree);
    }

    return binaryTree;
}


template<typename T>
template<typename V>
V BinaryTree<T>::Reduce(V (*function)(T, V)) {
    return this->_Reduce(function, this->root, *(new V()));
}

template<typename T>
template<typename V>
V BinaryTree<T>::_Reduce(V (*function)(T, V), TreeNode<T> *node, V value) {
    if (node != NULL) {
        value = function(*node->value, value);
        value = this->_Reduce(function, node->left, value);
        value = this->_Reduce(function, node->right, value);
    }

    return value;
}

template<typename T>
BinaryTree<T> *BinaryTree<T>::Where(bool (*function)(T)) {
    return _Where(function, this->root, new BinaryTree<T>());
}

template<typename T>
BinaryTree<T> *BinaryTree<T>::_Where(bool (*function)(T), TreeNode<T> *node, BinaryTree<T> *binaryTree) {
    if (node != NULL) {
        if (function(*node->value)) {
            binaryTree->Insert(*node->value);
        }
        this->_Where(function, node->left, binaryTree);
        this->_Where(function, node->right, binaryTree);
    }

    return binaryTree;
}

template<typename T>
LinkedList<TreeNode<T> *> *BinaryTree<T>::Thread(string bypass) {
    return this->_Thread(bypass, this->root, new LinkedList<TreeNode<T> *>);
}

template<typename T>
LinkedList<TreeNode<T> *> *BinaryTree<T>::_Thread(string bypass, TreeNode<T> *node, LinkedList<TreeNode<T>*>* threatList) {
    if (node != NULL) {
        for (int i = 0; i < bypass.length(); i++) {
            switch (bypass[i]) {
                case 'K':
                    threatList->Append(node);
                    break;
                case 'L':
                    if (node->left != NULL) {
                        this->_Thread(bypass, node->left, threatList);
                    }
                    break;
                case 'R':
                    if (node->right != NULL) {
                        this->_Thread(bypass, node->right, threatList);
                    }
                    break;
            }
        }
    }

    return threatList;
}

template<typename T>
BinaryTree<T> *BinaryTree<T>::GetSubTree(T value) {
    return this->_GetSubTree(this->Search(value), new BinaryTree<T>());
}

template<typename T>
BinaryTree<T> *BinaryTree<T>::_GetSubTree(TreeNode<T> *node, BinaryTree<T> *binaryTree) {
    if (node != NULL) {
        binaryTree->Insert(*node->value);
        this->_GetSubTree(node->left, binaryTree);
        this->_GetSubTree(node->right, binaryTree);
    }

    return binaryTree;
}

template<typename T>
bool BinaryTree<T>::ContainsSubTree(BinaryTree<T> *subtree) {
    return this->_ContainsSubTree(subtree->root, this->Search(*subtree->root->value));
}

template<typename T>
bool BinaryTree<T>::_ContainsSubTree(TreeNode<T> *node1, TreeNode<T> *node2) {
    if (node1 == NULL) {
        return true;
    }

    if (node2 == NULL) {
        return false;
    }

    if (*node1->value != *node2->value) {
        return false;
    }

    if (this->_ContainsSubTree(node1->left, node2->left) && this->_ContainsSubTree(node1->right, node2->right)) {
        return true;
    }

    return false;
}

template<typename T>
int BinaryTree<T>::Count() {
    return this->_Count(this->root);
}

template<typename T>
int BinaryTree<T>::_Count(TreeNode<T>* root) {
    int count = 0;
    queue<TreeNode<T>*> q;

    q.push(root);

    while(!q.empty()) {
        if (q.front()->left)
            q.push(q.front()->left);
        if (q.front()->right)
            q.push(q.front()->right);

        q.pop();
        count++;
    }

    return count;
}

template<typename T>
Sequence<T>* BinaryTree<T>::Get() {
    int index = 0;
    return this->_Get(this->root, new ArraySequence<T>(this->Count()), &index);
}

template<typename T>
Sequence<T>* BinaryTree<T>::_Get(TreeNode<T> *node, Sequence<T>* sequence, int* index) {
    /*if (index < 0 || index >= this->Count()) {
        throw new Exception;
    }

    int cur_index = 0;
    queue<TreeNode<T>*> q;

    q.push(root);

    while(!q.empty()) {
        if (cur_index == index) {
            return *(q.front()->value);
        }

        if (q.front()->left)
            q.push(q.front()->left);
        if (q.front()->right)
            q.push(q.front()->right);

        q.pop();
        cur_index++;
    }*/

    if (this->Count() == 0) {
        throw new Exception;
    }

    if (node != NULL) {
        sequence->Set(*node->value, *index);

        (*index)++;
        this->_Get(node->left, sequence, index);
        this->_Get(node->right, sequence, index);
    }

    return sequence;
}
