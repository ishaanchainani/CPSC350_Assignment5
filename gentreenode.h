#pragma once
template <class T>
class GenTreeNode {
public:
  // public variables
    int key;
    T* data;
    GenTreeNode<T>* left;
    GenTreeNode<T>* right;

    GenTreeNode();
    GenTreeNode(T* d);
    ~GenTreeNode();

    void printOut();
};

// constructor, initialize variables
template <class T>
GenTreeNode<T>::GenTreeNode() {
    key = 0;
    data = NULL;
    left = NULL;
    right = NULL;
}
// overloaded constructor
template <class T>
GenTreeNode<T>::GenTreeNode(T* d) {
    key = d->getKey();
    data = d;
    left = NULL;
    right = NULL;
}

// destructor
template <class T>
GenTreeNode<T>::~GenTreeNode() {
}

// print function
template <class T>
void GenTreeNode<T>::printOut() {
    data->printOut();
}
