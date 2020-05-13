#pragma once

#include <iostream>
#include "Gentreenode.h"
#include <fstream>
#include <sstream>

#include <string>

using namespace std;


template <class T>
class GenSearchTree {
private:
    GenTreeNode<T>* root;
    int size;

    void printInOrder(GenTreeNode<T>* node);
    GenTreeNode<T>* getNext(GenTreeNode<T>* node, GenTreeNode<T>* &parent);
    void serializeInOrder(GenTreeNode<T>* node, fstream &filestream);

public:
    GenSearchTree();
    ~GenSearchTree();


    bool ifContains(int k); // check if contains k key
    T* find(int k);
    void insert(T* d);
    T* deleteNode(int k); // remove key k entry, return NULL if non-existant

    void printTree(); // In-order print

    GenTreeNode<T>* getMin(GenTreeNode<T>* node); // return first entry starting at node
    T* getMax(); // return last entry

    int getSize(); // number of entries
    bool isEmpty(); // is the tree empty?

    void serialize(fstream &filestream);
};

template <class T>
GenSearchTree<T>::GenSearchTree() {
    root = NULL;
    size = 0;
}

template<class T>
GenSearchTree<T>::~GenSearchTree() {

}

// get next node in tree
template<class T>
GenTreeNode<T>* GenSearchTree<T>::getNext(GenTreeNode<T>* node, GenTreeNode<T>* &parent) {
    if (node == NULL || node->right == NULL) {
        return NULL;
    }
    // find the smallest key starting at node->right
    parent = node->right;
    GenTreeNode<T>* curr = node->right;

    while (curr->left != NULL) {
        parent = curr;
        curr = curr->left;
    }
    return (curr);
}

// finding if tree contains key k
template<class T>
bool GenSearchTree<T>::ifContains(int k) {
    GenTreeNode<T>* result = find(k);
    return (result != NULL);
}

// finding key k in tree
template<class T>
T* GenSearchTree<T>::find(int k) {
    if (root == NULL) {
        return NULL;
    }

    GenTreeNode<T>* curr = root;

    while (curr->key != k) {
        if (k < curr->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
        if (curr == NULL) {
            return NULL;
        }
    }
    return curr->data;
}

// insertion of data in tree
template <class T>
void GenSearchTree<T>::insert(T* d) {

    GenTreeNode<T>* node = new GenTreeNode<T>(d);
    if (root == NULL) {
        root = node;
    }
    else {

        GenTreeNode<T>* curr = root;
        GenTreeNode<T>* parent;

        while (true) {
            parent = curr;
            if (node->key < curr->key) {
                curr = curr->left;
                if (curr == NULL) {
                    parent->left = node;
                    break;
                }
            }
            else {
                if (node->key > curr->key) {
                    curr = curr->right;
                    if (curr == NULL) {
                        parent->right = node;
                        break;
                    }
                }
                else {
                    // node exists; this a duplicate, we do nothing
                    return;
                }
            }
        }
    }
    ++size;
}

// deleting a node from the tree
template <class T>
T* GenSearchTree<T>::deleteNode(int k) {

    // 1. removing a leaf node (no children)
    // 2. removing a node with a single child
    // 3. removing a node with 2 children


    // if there are no nodes
    if (root == NULL) {
        return NULL;
    }


    bool found = false;
    GenTreeNode<T>* curr = root;
    GenTreeNode<T>* parent = root;

    // first find the node
    while (curr->key != k) {
        parent = curr;

        if (k < curr->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }

        if (curr == NULL) {
            return NULL;
        }
    }
    // found the node at curr

    // check for no children
    if (curr->left == NULL && curr->right == NULL) {
        if (curr == root) {
            root = NULL;
        }
        else if (parent->left == curr) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
    }
    else if (curr->right == NULL) { // no right node
        if (curr == root) {
            root = curr->left;
        }
        else if (parent->left == curr) {
            parent->left = curr->left;
        }
        else {
            parent->right = curr->left;
        }
    }
    else if (curr->left == NULL) { // no left node
        if (curr == root) {
            root = curr->right;
        }
        else if (parent->left == curr) {
            parent->left = curr->right;
        }
        else {
            parent->right = curr->right;
        }
    }
    else {
        // removing node with 2 children
        if ((curr == NULL) || (curr->left == NULL) || (curr->right == NULL)) {
            cout << "error\n";
            exit(1);
        }

        GenTreeNode<T>* pnode;
         GenTreeNode<T>* next = getNext(curr, pnode);
        if (curr == root) {
            root = next;
        }
        else if (parent->left == curr) {
            parent->left = next;
        }
        else {
            parent->right = next;
        }
        if (pnode == next) {
            // next->right stays the same
        } else {
            pnode->left = next->right;
            next->right = curr->right;
        }
        next->left = curr->left;

    }
    --size;
    return curr->data;

}

// obtain minimum value in tree
template <class T>
GenTreeNode<T>* GenSearchTree<T>::getMin(GenTreeNode<T>* node) {
    GenTreeNode<T>* curr = node;

    if (curr == NULL) { // tree is empty
        return NULL;
    }

    // left node
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

// obtain largest value in tree
template <class T>
T* GenSearchTree<T>::getMax() {
    GenTreeNode<T>* curr = root;

    if (curr == NULL) { // tree is empty
        return NULL;
    }

    // right node
    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr->data;
}


// print tree in ordered nodes
template <class T>
void GenSearchTree<T>::printInOrder(GenTreeNode<T>* node) {
    GenTreeNode<T>* curr = node;
    if (curr == NULL) { // tree is empty
        return;
    }
    printInOrder(node->left);
    node->printOut();
    printInOrder(node->right);
}

// prints tree
template <class T>
void GenSearchTree<T>::printTree() {
    printInOrder(root);
}

// obtain size
template <class T>
int GenSearchTree<T>::getSize() {
    return size;
}

// if tree is empy
template <class T>
bool GenSearchTree<T>::isEmpty() {
    return (root == NULL);
}

// serialize function, takes in file stream
template <class T>
void GenSearchTree<T>::serialize(fstream &filestream) {

    if (root == NULL) {
        return;
    }
    serializeInOrder(root, filestream);
}

// serializes in order, takes in node and file stream
template <class T>
void GenSearchTree<T>::serializeInOrder(GenTreeNode<T>* node, fstream &filestream) {
    GenTreeNode<T>* curr = node;
    if (curr == NULL) { // tree is empty
        return;
    }
    serializeInOrder(node->left, filestream);
    node->data->serialize(filestream);
    serializeInOrder(node->right, filestream);
}
