// Lab 01 - Singly Linked List
// insert at head / tail / position, delete by value, search, reverse, display
#include <iostream>

struct Node {
    int data;
    Node* next;
    explicit Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
    Node* head = nullptr;
    int size = 0;

public:
    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtHead(int value) {            // O(1)
        Node* n = new Node(value);
        n->next = head;
        head = n;
        size++;
    }

    void insertAtTail(int value) {            // O(n)
        Node* n = new Node(value);
        if (!head) { head = n; size++; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
        size++;
    }

    bool insertAt(int pos, int value) {       // pos is 0-based, O(n)
        if (pos < 0 || pos > size) return false;
        if (pos == 0) { insertAtHead(value); return true; }
        Node* cur = head;
        for (int i = 0; i < pos - 1; i++) cur = cur->next;
        Node* n = new Node(value);
        n->next = cur->next;
        cur->next = n;
        size++;
        return true;
    }

    bool remove(int value) {                  // O(n)
        Node* cur = head;
        Node* prev = nullptr;
        while (cur && cur->data != value) { prev = cur; cur = cur->next; }
        if (!cur) return false;
        if (prev) prev->next = cur->next; else head = cur->next;
        delete cur;
        size--;
        return true;
    }

    int search(int value) const {             // returns index or -1, O(n)
        int index = 0;
        for (Node* cur = head; cur; cur = cur->next, index++)
            if (cur->data == value) return index;
        return -1;
    }

    void reverse() {                          // O(n), in place
        Node* prev = nullptr;
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
    }

    void display() const {
        std::cout << "[size " << size << "] ";
        for (Node* cur = head; cur; cur = cur->next) std::cout << cur->data << " -> ";
        std::cout << "NULL\n";
    }
};

int main() {
    SinglyLinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtHead(5);
    std::cout << "After inserts:        "; list.display();
    list.insertAt(2, 15);
    std::cout << "Insert 15 at index 2: "; list.display();
    std::cout << "Search 20 -> index " << list.search(20) << ", search 99 -> " << list.search(99) << '\n';
    list.remove(10);
    std::cout << "Remove 10:            "; list.display();
    list.reverse();
    std::cout << "Reversed:             "; list.display();
    return 0;
}
