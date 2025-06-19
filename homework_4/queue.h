#ifndef QUEUE_H_
#define QUEUE_H_

#include "bag.h"

template <class T>
class Queue : public Bag<T> {
    template <typename U>
    friend ostream& operator<<(ostream&, const Queue<U>&);

public:
	// constructor
    Queue(int QueueSize) :Bag<T>(QueueSize) {
        front = rear = q_count = 0;
        strcpy(this->name, "Queue");
    };

	// destructor
    ~Queue() {};

	// pop front element from queue
    T* Pop(T& x) {
        if (q_count == 0) {
            this->Empty();
            return nullptr;
        }
        else {
            x = this->array[front];
            front = (front + 1) % this->MaxSize;
            q_count = q_count - 1;
            this->top = q_count;
            this->message(x);
            return &x;
        }
    }

	// push element into queue 
    void Push(const T& x) {
        if (q_count >= this->MaxSize - 1) {
            this->Full(x);
            return;
        }
        else {
            this->array[rear] = x;
            rear = (rear + 1) % this->MaxSize;
            q_count = q_count + 1;
            this->top = q_count;
        }
    }

private:
    int rear, front, q_count;
};

// Overload << operator to print the queue
template <class T>
ostream& operator<<(ostream& os, const Queue <T>& q) {
    os << "   All data in " << right << setw(6) << q.name << "[" << q.MaxSize << "] are: ";

    for (int i = 0; i < q.MaxSize; i++) {
        os << "(" << i << ") ";

        if (q.q_count == 0) {
            os << "-1" << setw(3) << " ";
        }
        else {
			// Check if the index is valid in the circular queue
            bool is_valid = false;

            if (q.front <= q.rear) {
                is_valid = (i >= q.front && i < q.rear);
            }
            else {
                is_valid = (i >= q.front || i < q.rear);
            }

            if (is_valid) {
                os << q.array[i] << setw(3) << " ";
            }
            else {
                os << "-1" << setw(2) << " ";
            }
        }
    }

    os << "\n   Valid data among them are: ";
    if (q.q_count > 0) {
        int i = q.front;
        int remain = q.q_count;

        while (remain > 0) {
            os << "(" << i << ") " << q.array[i] << setw(3) << " ";
            i = (i + 1) % q.MaxSize;
            remain = remain - 1;
        }
    }
    os << "\n\n";

    return os;
}

#endif
