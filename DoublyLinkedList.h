#pragma once

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DoublyLinkedList {
private:
    unsigned int size; // number of elements in the list
    ListNode<T>* header; // pointer to sentinal head
    ListNode<T>* trailer; // pointer to sentinal trail

public:
    DoublyLinkedList(); // constructor
    ~DoublyLinkedList(); // destructor

    unsigned int getSize();
    bool isEmpty(); // checks if list is empty

    void insertFront(T* data); // insert at front
    void insertBack(T* data); //insert at back

    T* removeFront(); // remove first
    T* removeBack(); // remove back

    T* getFront(); // return pointer to the front, do not remove
    T* getBack(); // return pointer to the back, do not remove

    //T* removePos(int pos); not implemented
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    size = 0;
    header = new ListNode<T>(NULL); // Header sentinel
    trailer = new ListNode<T>(NULL); // Trailer sentinel

    header->next = trailer; // set header sentinel next pointer to trailer
    header->prev = trailer; // set header sentinel prev pointer to trailer

    trailer->next = header; // set trailer sentinel next pointer to header
    trailer->prev = header; // set trailer sentinel prev pointer to header
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    // clean up any remaining elements in the LinkedList
    while (!isEmpty()) {
        T* node = removeFront();
        delete node;
    }
    // delete sentinels
    delete header;
    delete trailer;
}

template<class T>
unsigned int DoublyLinkedList<T>::getSize() {
    return size;
}

template<class T>
bool DoublyLinkedList<T>::isEmpty() {
    return(size == 0);
}

template<class T>
void DoublyLinkedList<T>::insertFront(T* d) {
    ListNode<T>* node = new ListNode<T>(d); // creates new element

    // link new element in front
    ListNode<T>* prevFront = header->next; // capturing the previous front
    node->prev = header;                   // setting the nodes previous pointer to header sentinel
    node->next = prevFront;                // setting the nodes next pointer to previous front
    prevFront->prev = node;                // linking previous front and new node
    header->next = node;                   // setting the node as the new front

    size++;
}

template<class T>
void DoublyLinkedList<T>::insertBack(T* d) {
    ListNode<T>* node = new ListNode<T>(d); // creates new element

    ListNode<T>* prevBack = trailer->prev; // capturing the previous back
    node->next = trailer;                  // setting the nodes next pointer to trailer sentinel
    node->prev = prevBack;                 // setting the nodes previous pointer to previous back
    prevBack->next = node;                 // linking previous back and new node
    trailer->prev = node;                  // setting the node as the new back

    ++size;
}

template<class T>
T* DoublyLinkedList<T>::removeFront() {
    T* data = NULL;
    if (!isEmpty()) {
        ListNode<T>* node = header->next;  // capturing the pointer to the first element
        header->next = node->next;         // making the second element as the first
        node->next->prev = header;         // linking the new front back to header sentinel
        data = node->data;                 // collecting pointer to the data
        delete node;
        --size;
    }
    return data;
}

template<class T>
T* DoublyLinkedList<T>::removeBack() {
    T* data = NULL;
    if (!isEmpty()) {
        ListNode<T>* node = trailer->prev;  // capturing the trailer to the first element
        trailer->prev = node->prev;         // making the previous element as the first
        node->prev->next = trailer;         // linking the previous back to trailer sentinel
        data = node->data;                  // collecting pointer to the data
        delete node;
        --size;
    }
    return data;
}


template<class T>
T* DoublyLinkedList<T>::getFront() {
    T* data = NULL;
    if (!isEmpty()) {
        data = header->next->data;         // collecting pointer to the data
    }
    return data;
}

template<class T>
T* DoublyLinkedList<T>::getBack() {
    T* data = NULL;
    if (!isEmpty()) {
        data = trailer->prev->data;        // collecting pointer to the data
    }
    return data;
}

/*
template<class T>
T* DoublyLinkedList<T>::removePos(int pos) {

    if (size < (pos + 1)) {
        return NULL;
    }

    ListNode<T>* temp = header->next;

    for (int i = 0;  i < pos; i++) {
        temp = temp->next;
    }

    T* retdata = temp->data;
    --size;
    // FIX
    return (temp->data);
}
*/
