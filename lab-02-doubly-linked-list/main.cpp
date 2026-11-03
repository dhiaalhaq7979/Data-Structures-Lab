// Lab 02 - Doubly Linked List
// every node knows its previous and next node, so we can traverse in both directions
#include <iostream>

struct DNode {
    int data;
    DNode* prev = nullptr;
    DNode* next = nullptr;
    explicit DNode(int value) : data(value) {}
};

class DoublyLinkedList {
    DNode* head = nullptr;
    DNode* tail = nullptr;

public:
    ~DoublyLinkedList() {
        while (head) { DNode* t = head; head = head->next; delete t; }
    }

    void pushFront(int value) {               // O(1)
        DNode* n = new DNode(value);
        n->next = head;
        if (head) head->prev = n; else tail = n;
        head = n;
    }

    void pushBack(int value) {                // O(1) thanks to the tail pointer
        DNode* n = new DNode(value);
        n->prev = tail;
        if (tail) tail->next = n; else head = n;
        tail = n;
    }

    bool remove(int value) {                  // O(n) to find, O(1) to unlink
        DNode* cur = head;
        while (cur && cur->data != value) cur = cur->next;
        if (!cur) return false;
        if (cur->prev) cur->prev->next = cur->next; else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev; else tail = cur->prev;
        delete cur;
        return true;
    }

    void printForward() const {
        std::cout << "NULL <-> ";
        for (DNode* c = head; c; c = c->next) std::cout << c->data << " <-> ";
        std::cout << "NULL\n";
    }

    void printBackward() const {
        std::cout << "NULL <-> ";
        for (DNode* c = tail; c; c = c->prev) std::cout << c->data << " <-> ";
        std::cout << "NULL\n";
    }
};

int main() {
    DoublyLinkedList list;
    for (int v : {3, 6, 9}) list.pushBack(v);
    list.pushFront(1);
    std::cout << "Forward : "; list.printForward();
    std::cout << "Backward: "; list.printBackward();
    list.remove(6);
    list.remove(1);
    std::cout << "After removing 6 and 1:\n";
    std::cout << "Forward : "; list.printForward();
    std::cout << "Backward: "; list.printBackward();
    return 0;
}
