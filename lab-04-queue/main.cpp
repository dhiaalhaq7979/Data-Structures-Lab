// Lab 04 - Queue using a circular array
#include <iostream>

class CircularQueue {
    static const int CAPACITY = 5;
    int items[CAPACITY];
    int front = 0, rear = -1, count = 0;

public:
    bool enqueue(int value) {                       // O(1)
        if (isFull()) return false;
        rear = (rear + 1) % CAPACITY;
        items[rear] = value;
        count++;
        return true;
    }
    bool dequeue(int& out) {                        // O(1)
        if (isEmpty()) return false;
        out = items[front];
        front = (front + 1) % CAPACITY;
        count--;
        return true;
    }
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == CAPACITY; }
    void display() const {
        std::cout << "front -> ";
        for (int i = 0; i < count; i++) std::cout << items[(front + i) % CAPACITY] << ' ';
        std::cout << "<- rear  (" << count << "/" << CAPACITY << ")\n";
    }
};

int main() {
    CircularQueue q;
    for (int v = 1; v <= 6; v++)
        std::cout << "enqueue " << v << ": " << (q.enqueue(v * 10) ? "ok" : "queue is FULL") << '\n';
    q.display();
    int x = 0;
    q.dequeue(x); std::cout << "dequeue -> " << x << '\n';
    q.dequeue(x); std::cout << "dequeue -> " << x << '\n';
    q.enqueue(60); q.enqueue(70);
    std::cout << "after adding 60 and 70 (wraps around the array):\n";
    q.display();
    return 0;
}
