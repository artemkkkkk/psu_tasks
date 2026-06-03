#include <iostream>
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

void convert(Node* curr, Node*& prev, Node*& head) {
    if (!curr) return;
    convert(curr->left, prev, head);
    if (prev) {
        prev->right = curr;
        curr->left = prev;
    } else {
        head = curr;
    }
    prev = curr;
    convert(curr->right, prev, head);
}

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

    cout << "Исходное бинарное дерево поиска:\n";
    printTreeSideways(root, "", true);
    cout << "\n";

    Node* prev = nullptr;
    Node* head = nullptr;
    convert(root, prev, head);

    cout << "Получившийся двусвязный список:\n";
    Node* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->right) cout << " <-> ";
        curr = curr->right;
    }
    cout << "\n\n";

    deleteTree(root);
    return 0;
}