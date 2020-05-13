#pragma once

// ListNode is the element of DoublyLinkedList
template <class T>
class ListNode {
public:
    T* data;
    ListNode<T>* next;  // pointer to next
    ListNode<T>* prev;  // pointer to prev

    ListNode(T* data);  // constructor
    ~ListNode();        // destructor

};


template <class T>
ListNode<T>::ListNode(T* d) {
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode() {
}
