#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include "list.h"

using namespace std;

extern int debug;
extern int debug_queue;

//  A simple linked-list queue that reuses List<T>
template <class T>
class Queue {
public:
    Queue() = default; // default ctor
    Queue(const Queue& rhs) : qlist(rhs.qlist) {} // copy ctor
    ~Queue() { // dtor with debug
        if (debug && debug_queue) {
            cout << "\ndelete Queue->";
        }
    }

    Queue& operator=(const Queue& rhs) { // copy assignment
        qlist = rhs.qlist;
        return *this;
    }

    // capacity check
    bool IsEmpty() const { return qlist.num == 0; }
    bool IsFull()  const { return false; } // never full???

    // modifiers 
    void Push(const T& item); // enqueue
    T    Pop(); // dequeue and return the value

    // observer
    T    Front() const; // read front element

    // debug print
    template <class U>
    friend ostream& operator<<(ostream&, const Queue<U>&);

private:
    List<T> qlist; // underlying list

    // print only when debug switches are on
    static void QueueEmpty() {
        if (debug && debug_queue) cout << "Queue is empty\n";
    }
};

// insert to rear
template <class T>
void Queue<T>::Push(const T& item)
{
    if (debug && debug_queue)
        cout << "\nnew queue node (" << item << ")->";
    qlist.InsertBack(item);
}

// remove from front
template <class T>
T Queue<T>::Pop()
{
    if (IsEmpty()) { QueueEmpty(); return T(); }
    Node<T>* n = qlist.Pop();
    T val = n->data;
    if (debug && debug_queue)
        cout << "\nrecycle node (" << val << ")->";
    delete n;
    return val;
}

// peek front element
template <class T>
T Queue<T>::Front() const
{
    if (IsEmpty()) { QueueEmpty(); return T(); }
    return qlist.first->data;
}

// dump queue content
template <class U>
ostream& operator<<(ostream& os, const Queue<U>& q)
{
    os << "\n The contents in the Queue are:\n";
    Node<U>* cur = q.qlist.first;
    int idx = 0;
    while (cur) {
        os << '(' << ++idx << ") " << cur->data << setw(4) << " ";
        cur = cur->link;
    }
    os << '\n';
    return os;
}

#endif
