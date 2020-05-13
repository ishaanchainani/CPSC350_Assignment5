#include <iostream>
#include "GenQueue.h"
#include <fstream>

enum class opType { INSERTION = 0, DELETION = 1 };

template <class T>
class Operation {
public:

    opType operation;
    int key;
    T* data;

    Operation(opType ot, int key, T* data) { operation = ot; this->key = key; this->data = data; }
};
// class OperationLog keeps track of operations, used for rollback function
template <class T>
class OperationsLog {
private:
    GenQueue<Operation<T>> queue;

public:
    OperationsLog();
    ~OperationsLog();

    void logInsertion(int key);
    void logDeletion(int key, T *data);

    Operation<T> *undoLastOp();
};

template <class T>
OperationsLog<T>::OperationsLog() {
}

template <class T>
OperationsLog<T>::~OperationsLog() {
}

// log when student/faculty is inserted
template <class T>
void OperationsLog<T>::logInsertion(int key) {
    T* data = NULL;
    Operation<T>* op = new Operation<T>(opType::INSERTION, key, data);
    queue.enqueue(op);
}

// log when student/faculty is deleted
template <class T>
void OperationsLog<T>::logDeletion(int key, T *data) {
    Operation<T>* op = new Operation<T>(opType::DELETION, key, data);
    queue.enqueue(op);
}

// rollback
template <class T>
Operation<T>* OperationsLog<T>::undoLastOp() {
    if (queue.isEmpty()) {
        return NULL;
    }
    return (queue.dequeue());
}
