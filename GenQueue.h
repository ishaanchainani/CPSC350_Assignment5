#pragma once

// generic queue implementation

#include "DoublyLinkedList.h"

template <class T>
class GenQueue {
private:
    DoublyLinkedList<T>* myQueue;
public:
    GenQueue();                 // constructor
    ~GenQueue();                // destructor

    void enqueue(T* e);         // add element to beginning of queue
    T* dequeue();               // remove element from end of queue
    T* peek();                  // return pointer to first element

    unsigned int getSize();
    bool isEmpty();
};

template <class T>
GenQueue<T>::GenQueue() {
    myQueue = new DoublyLinkedList<T>(); // using DoublyLinkedList as underlying data strucutre 
}

template<class T>
GenQueue<T>::~GenQueue() {
    delete myQueue;
}

template<class T>
void GenQueue<T>::enqueue(T* element) {
    myQueue->insertBack(element);       // add element to back of myQueue
}

template<class T>
T* GenQueue<T>::dequeue() {
    return myQueue->removeFront();      // remove the front element of myQueue
}

template<class T>
T* GenQueue<T>::peek() {
    return myQueue->getFront();         // obtain front element of myQueue
}

template<class T>
bool GenQueue<T>::isEmpty() {
    return(myQueue->isEmpty());         // check is myQueue is empty
}

template<class T>
unsigned int GenQueue<T>::getSize() {
    return(myQueue->getSize());         // obtain size of myQueue
}