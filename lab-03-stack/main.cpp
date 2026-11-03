// Lab 03 - Stack (linked-list based) + application: balanced brackets checker
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Stack {
    struct Node { T data; Node* next; };
    Node* topNode = nullptr;
    int count = 0;

public:
    ~Stack() { while (!isEmpty()) pop(); }
    void push(const T& value) { topNode = new Node{value, topNode}; count++; }   // O(1)
    T pop() {                                                                    // O(1)
        if (isEmpty()) throw std::underflow_error("stack is empty");
        Node* t = topNode;
        T value = t->data;
        topNode = t->next;
        delete t;
        count--;
        return value;
    }
    T peek() const {
        if (isEmpty()) throw std::underflow_error("stack is empty");
        return topNode->data;
    }
    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }
};

bool isBalanced(const std::string& expr) {
    Stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') s.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (s.isEmpty()) return false;
            char open = s.pop();
            if ((c == ')' && open != '(') || (c == ']' && open != '[') || (c == '}' && open != '{')) return false;
        }
    }
    return s.isEmpty();
}

int main() {
    Stack<int> s;
    for (int v : {10, 20, 30}) { s.push(v); std::cout << "push " << v << " (size " << s.size() << ")\n"; }
    std::cout << "peek -> " << s.peek() << '\n';
    while (!s.isEmpty()) std::cout << "pop  -> " << s.pop() << '\n';
    try { s.pop(); } catch (const std::underflow_error& e) { std::cout << "pop on empty stack: " << e.what() << '\n'; }

    std::cout << "\nBalanced brackets checker:\n";
    for (std::string e : {"{[a+b]*(c-d)}", "(a+b]", "((x)", "[()]{}"})
        std::cout << "  " << e << "  ->  " << (isBalanced(e) ? "balanced" : "NOT balanced") << '\n';
    return 0;
}
