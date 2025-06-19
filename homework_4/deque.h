#ifndef DEQUE_H_
#define DEQUE_H_
#include "bag.h"

template <class T>
class Deque : public Bag<T> {
    template <typename U>
    friend ostream& operator<<(ostream&, const Deque<U>&);

public:
    // Constructor
    Deque(int DequeSize) : Bag<T>(DequeSize) {
        front = rear = -1;
        q_count = 0;  // q_count --> to track number of elements
        strcpy(this->name, "Deque");
    };

    // Destructor
    ~Deque() {};

    // Push to the front
    void Pushf(const T& x) {
        // Check if deque is full (using q_count counter)
        if (q_count == this->MaxSize) {
            this->Full(x);
            return;
        }

        // If deque is initially empty
        if (front == -1) {
            front = rear = 0;
        }
        else {
            // Update front circularly
            front = (front - 1 + this->MaxSize) % this->MaxSize;
        }

        this->array[front] = x;
        q_count = q_count + 1;
        this->top = q_count;  // Update top for Bag compatibility
    }

    // Push to the rear
    void Pushr(const T& x) {
        // Check if deque is full (using q_count counter)
        if (q_count == this->MaxSize) {
            this->Full(x);
            return;
        }

        // If deque is initially empty
        if (front == -1) {
            front = rear = 0;
        }
        else {
            // Update rear circularly
            rear = (rear + 1) % this->MaxSize;
        }

        this->array[rear] = x;
        q_count = q_count + 1;
        this->top = q_count;  // Update top for Bag compatibility
    }

    // Pop from the front
    T* Popf(T& x) {
        if (front == -1) {
            this->Empty();
            return nullptr;
        }

        x = this->array[front];

        // If only one element
        if (front == rear) {
            front = rear = -1;
        }
        else {
            // Update front circularly
            front = (front + 1) % this->MaxSize;
        }

        q_count = q_count - 1;
        this->top = q_count;  // Update top for Bag compatibility
        this->message(x);
        return &x;
    }

    // Pop from the rear
    T* Popr(T& x) {
        if (front == -1) {
            this->Empty();
            return nullptr;
        }

        x = this->array[rear];

        // If only one element
        if (front == rear) {
            front = rear = -1;
        }
        else {
            // Update rear circularly
            rear = (rear - 1 + this->MaxSize) % this->MaxSize;
        }

        q_count = q_count - 1;
        this->top = q_count;  // Update top for Bag compatibility
        this->message(x);
        return &x;
    }

private:
    int rear, front, q_count;  // Added q_count to track number of elements
};

template <class T>
ostream& operator<<(ostream& os, const Deque <T>& d) {
    os << "   All data in " << right << setw(6) << d.name << "[" << d.MaxSize << "] are: ";

    for (int i = 0; i < d.MaxSize; i++) {
        os << "(" << i << ") " << d.array[i] << setw(3) << " ";
    }

    os << "\n   Valid data among them are: ";

    if (d.front != -1) {
        if (d.front <= d.rear) {
            // Deque not wrapped around
            for (int i = d.front; i <= d.rear; i++) {
                os << "(" << i << ") " << d.array[i] << setw(3) << " ";
            }
        }
        else {
            // Deque wrapped around
            for (int i = d.front; i < d.MaxSize; i++) {
                os << "(" << i << ") " << d.array[i] << setw(3) << " ";
            }
            for (int i = 0; i <= d.rear; i++) {
                os << "(" << i << ") " << d.array[i] << setw(3) << " ";
            }
        }
    }
    os << "\n\n";

    return os;
}

#endif
