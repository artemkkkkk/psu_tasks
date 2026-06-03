#include <iostream>
#include <stack>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

void insert(Node*& root, int val) {
    if (!root) {
        root = new Node(val);
        return;
    }
    if (val < root->val) insert(root->left, val);
    else insert(root->right, val);
}

void printTreeSideways(Node* root, string prefix, bool isLeft) {
    if (!root) return;
    printTreeSideways(root->right, prefix + (isLeft ? "│   " : "    "), false);
    cout << prefix << (isLeft ? "┌── " : "└── ") << root->val << "\n";
    printTreeSideways(root->left, prefix + (isLeft ? "    " : "│   "), true);
}

class TreeIterator {
    stack<Node*> st;
    void pushLeft(Node* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
public:
    TreeIterator(Node* root) {
        pushLeft(root);
    }
    bool hasNext() {
        return !st.empty();
    }
    int next() {
        Node* node = st.top();
        st.pop();
        int val = node->val;
        pushLeft(node->right);
        return val;
    }
};

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Node* root = nullptr;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) insert(root, v);

    cout << "Исходное бинарное дерево:\n";
    printTreeSideways(root, "", true);
    cout << "\n";

    cout << "Результат работы итератора (лево-корень-право):\n";
    TreeIterator it(root);
    while (it.hasNext()) {
        cout << it.next() << " ";
    }
    cout << "\n\n";

    deleteTree(root);
    return 0;
}