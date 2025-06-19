#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

#define DefaultQSize 100

void QueueEmpty();
void QueueFull();

/* ---------- Generic circular‑array queue ---------- */
template <typename T>
class Queue {
public:
    /* Constructor & destructor */
    explicit Queue(int MaxQueueSize = DefaultQSize)
        : front(-1), rear(-1), MaxSize(MaxQueueSize), top(0)
    {
        queue = new T[MaxSize];
    }

    Queue(const Queue& rhs) { copyFrom(rhs); }
    Queue& operator=(const Queue& rhs) { if (this != &rhs) { delete[] queue; copyFrom(rhs); } return *this; }
    ~Queue() { delete[] queue; }

    /* Status checkers */
    bool IsEmpty() const { return front == -1; }
    bool IsFull() const { return rear == MaxSize - 1; }

    /* Insert at rear */
    void Push(const T& x) {
        if (IsFull()) { QueueFull(); return; }
        queue[++rear] = x;
        if (front == -1) front = 0;
        top = rear + 1;
    }

    /* Remove from front, return pointer to value */
    T* Delete(T& x) {
        if (IsEmpty()) { QueueEmpty(); return nullptr; }
        x = queue[front];
        (front == rear) ? front = rear = -1 : ++front;
        return &x;
    }
    /* Alias required by assignment spec */
    T* Pop(T& x) { return Delete(x); }

    /* Debug print */
    friend ostream& operator<<(ostream& os, const Queue<T>& q) {
        for (int i = q.front; i != -1 && i <= q.rear; ++i) os << q.queue[i] << ' ';
        return os;
    }

private:
    /* Deep copy helper */
    void copyFrom(const Queue& rhs) {
        front = rhs.front;  rear = rhs.rear; MaxSize = rhs.MaxSize; top = rhs.top;
        queue = new T[MaxSize];
        for (int i = 0; i < top; ++i) queue[i] = rhs.queue[i];
    }

    int front, rear, MaxSize, top;
    T* queue;
};

#endif
