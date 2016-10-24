#ifndef _AVL_H_
#define _AVL_H_

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class Node{
    public:
        T data;
        int balance;

        Node *parent, *right, *left;

        Node(T tData, Node *p) : data(tData), balance(0), parent(p), right(NULL), left(NULL){}

        ~Node(){
            delete right;
            delete left;
        }
};

template<typename T>
class Avl{
    private:
        Node<T> *root;

        Node<T>* rotateLeft(Node<T> *a);
        Node<T>* rotateRight(Node<T> *a);

        Node<T>* rotateLeftThenRight(Node<T> *n);
        Node<T>* rotateRightThenLeft(Node<T> *n);

        void rebalance(Node<T> *n);
        int height(Node<T> *n);
        void setBalance(Node<T> *n);
        void printBalance(Node<T> *n);
        void clearNode(Node<T> *n);

        vector<T> getSubArray(Node<T> *n);

    public:
        Avl();
        ~Avl();

        bool insert(T);
        bool remove(T);
        // will remove the minimum and put it in T
        bool removeMin(T *t);
        bool removeMax(T *t);
        vector<T> getSortedArray();
        bool find(T);
        void printBalance();
};

template <typename T>
void Avl<T>::rebalance(Node<T> *n) {

    setBalance(n);

    if (n->balance == -2) {

        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {

        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {

        rebalance(n->parent);
    }
    else {

        root = n;
    }
}

template <class T>
Node<T>* Avl<T>::rotateLeft(Node<T> *a) {

    Node<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a)
            b->parent->right = b;
        else
            b->parent->left = b;
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template<typename T>
Node<T>* Avl<T>::rotateRight(Node<T> *a){
    Node<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL){
        if (b->parent->right == a)
            b->parent->right = b;
        else
            b->parent->left = b;
    }

    setBalance(a);
    setBalance(b);

    return b;
}

template<typename T>
Node<T>* Avl<T>::rotateLeftThenRight(Node<T> *n){
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template<typename T>
Node<T>* Avl<T>::rotateRightThenLeft(Node<T> *n){
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template<typename T>
int Avl<T>::height(Node<T> *n){
    if (n == NULL)
        return -1;
    return 1 + max(height(n->left), height(n->right));
}

template<typename T>
void Avl<T>::setBalance(Node<T> *n){
    n->balance = height(n->right) - height(n->left);
}

template<typename T>
void Avl<T>::printBalance(Node<T> *n){
    if (n != NULL){
        printBalance(n->left);
        cout<<n->balance<<' ';
        printBalance(n->right);
    }
}

template<typename T>
Avl<T>::Avl(): root(NULL){}

template<typename T>
Avl<T>::~Avl(){
    delete root;
}

template<typename T>
bool Avl<T>::insert(T data){
    if (root == NULL)
        root = new Node<T>(data, NULL);
    else{
        // n is the node from where we start seeking for insertion place
        Node<T> *n = root, *parent;

        bool inserted = false;

        while (!inserted){
            // if we already have the data inserted
            if (n->data == data)
                return false;
            
            parent = n;
            // we look for which way to go
            bool goLeft = n->data > data;
            n = goLeft ? n->left : n->right;

            // if it's a leaf
            if (n == NULL){
                if (goLeft)
                    parent->left = new Node<T>(data, parent);
                else
                    parent->right = new Node<T>(data, parent);

                rebalance(parent);
                inserted = true;
            }
        }
    }
    return true;
}

template<typename T>
bool Avl<T>::remove(const T delData){
    if (root == NULL)
        return false;

    Node<T>
        *n       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delData >= n->data ? n->right : n->left;
        if (delData == n->data){
            delNode = n;
        }
    }

    if (delNode != NULL) {

        delNode->data = n->data;

        child = n->left != NULL ? n->left : n->right;

        if (root->data == delData) {
            root = child;
        }
        else {

            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
        return true;
    }
    return false;
}

template<typename T>
bool Avl<T>::removeMin(T *t){
    // if the tree is empty
    if (root == NULL)
        // will return a great number if there is nothing
        return false;

    // the leaf at the left extremum is the minimum
    Node<T> *actual = root, *child = actual->left;
    while (child != NULL){
        actual = child;
        child = actual->left;
    }
    *t = actual->data;
    remove(*t);
    return true;
}

template<typename T>
bool Avl<T>::removeMax(T *t){
    // if the tree is empty
    if (root == NULL)
        // will return a great number if there is nothing
        return false;

    // the leaf at the left extremum is the minimum
    Node<T> *actual = root, *child = actual->right;
    while (child != NULL){
        actual = child;
        child = actual->right;
    }
    *t = actual->data;
    remove(*t);
    return true;
}

template<typename T>
vector<T> Avl<T>::getSortedArray(){
    vector<T> result, left, right;
    
    if (root != NULL){
        left = getSubArray(root->left);
        right = getSubArray(root->right);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(root->data);
        result.insert(result.end(), right.begin(), right.end());
    }

    return result;
}

template<typename T>
vector<T> Avl<T>::getSubArray(Node<T> *n){
    vector<T> result, left, right;

    if (n != NULL){
        left = getSubArray(n->left);
        right = getSubArray(n->right);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(n->data);
        result.insert(result.end(), right.begin(), right.end());
    }

    return result;
}

template<typename T>
void Avl<T>::printBalance(){
    printBalance(root);
    cout<<endl;
}

#endif
