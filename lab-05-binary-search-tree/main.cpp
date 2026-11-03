// Lab 05 - Binary Search Tree: insert, search, delete, traversals, height
#include <iostream>

struct TreeNode {
    int key;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int k) : key(k) {}
};

class BST {
    TreeNode* root = nullptr;

    TreeNode* insert(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;                                   // duplicates are ignored
    }
    TreeNode* minNode(TreeNode* node) const {
        while (node && node->left) node = node->left;
        return node;
    }
    TreeNode* remove(TreeNode* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            if (!node->left) { TreeNode* r = node->right; delete node; return r; }
            if (!node->right) { TreeNode* l = node->left; delete node; return l; }
            TreeNode* successor = minNode(node->right);  // two children
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }
        return node;
    }
    void inorder(TreeNode* n) const { if (n) { inorder(n->left); std::cout << n->key << ' '; inorder(n->right); } }
    void preorder(TreeNode* n) const { if (n) { std::cout << n->key << ' '; preorder(n->left); preorder(n->right); } }
    void postorder(TreeNode* n) const { if (n) { postorder(n->left); postorder(n->right); std::cout << n->key << ' '; } }
    int height(TreeNode* n) const {
        if (!n) return 0;
        int l = height(n->left), r = height(n->right);
        return 1 + (l > r ? l : r);
    }
    void destroy(TreeNode* n) { if (n) { destroy(n->left); destroy(n->right); delete n; } }

public:
    ~BST() { destroy(root); }
    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool contains(int key) const {
        TreeNode* cur = root;
        while (cur) {
            if (key == cur->key) return true;
            cur = key < cur->key ? cur->left : cur->right;
        }
        return false;
    }
    void printAll() const {
        std::cout << "  inorder  : "; inorder(root); std::cout << '\n';
        std::cout << "  preorder : "; preorder(root); std::cout << '\n';
        std::cout << "  postorder: "; postorder(root); std::cout << '\n';
        std::cout << "  height   : " << height(root) << '\n';
    }
};

int main() {
    BST tree;
    for (int k : {50, 30, 70, 20, 40, 60, 80, 35}) tree.insert(k);
    std::cout << "Tree built from 50 30 70 20 40 60 80 35\n";
    tree.printAll();
    std::cout << "contains 60? " << (tree.contains(60) ? "yes" : "no")
              << ", contains 65? " << (tree.contains(65) ? "yes" : "no") << '\n';
    tree.remove(30);   // node with two children
    std::cout << "After deleting 30 (two children):\n";
    tree.printAll();
    return 0;
}
