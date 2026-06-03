#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class TreeBuilder;

class Node {
private:
    int val;
    Node* left;
    Node* right;
public:
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left;
        delete right;
    }
    int getVal() const { return val; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }
    friend class TreeBuilder;
};

class TreeValidator {
public:
    bool isValidBST(Node* root) {
        return isValidBSTHelper(root, -2147483648, 2147483647);
    }
private:
    bool isValidBSTHelper(Node* node, int minVal, int maxVal) {
        if (!node) return true;
        if (node->getVal() <= minVal || node->getVal() >= maxVal) return false;
        return isValidBSTHelper(node->getLeft(), minVal, node->getVal()) &&
               isValidBSTHelper(node->getRight(), node->getVal(), maxVal);
    }
};

class TreeBuilder {
public:
    Node* buildFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) return nullptr;
        string line;
        getline(fin, line);
        return buildFromString(line);
    }

    Node* buildFromString(const string& data) {
        Node* root = nullptr;
        stringstream ss(data);
        int val;
        while (ss >> val) {
            insert(root, val);
        }
        return root;
    }

    Node* buildFromConsole() {
        cout << "Введите числа через пробел для построения дерева: ";
        string line;
        getline(cin, line);
        return buildFromString(line);
    }

private:
    void insert(Node*& root, int val) {
        if (!root) {
            root = new Node(val);
            return;
        }
        if (val < root->val) {
            insert(root->left, val);
        } else {
            insert(root->right, val);
        }
    }
};

void printTree(Node* root, string prefix, bool isLeft) {
    if (!root) return;
    printTree(root->getRight(), prefix + (isLeft ? "│   " : "    "), false);
    cout << prefix << (isLeft ? "┌── " : "└── ") << root->getVal() << "\n";
    printTree(root->getLeft(), prefix + (isLeft ? "    " : "│   "), true);
}

void postOrder(Node* root, vector<int>& result) {
    if (!root) return;
    postOrder(root->getLeft(), result);
    postOrder(root->getRight(), result);
    result.push_back(root->getVal());
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    TreeBuilder builder;
    TreeValidator validator;

    Node* root = builder.buildFromFile("input.txt");
    if (!root) {
        root = builder.buildFromString("50 30 70 20 40 60 80");
    }

    cout << "Дерево ДО выполнения задачи:\n";
    printTree(root, "", true);
    cout << "\n";

    vector<int> result;
    postOrder(root, result);

    cout << "Концевой обход (лево-право-корень): ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i + 1 == result.size() ? "" : " ");
    }
    cout << "\n\n";

    cout << "Дерево ПОСЛЕ выполнения задачи (структура не изменилась):\n";
    printTree(root, "", true);
    cout << "\n";

    cout << "Проверка валидности BST: " << (validator.isValidBST(root) ? "УСПЕХ" : "ОШИБКА") << "\n";

    delete root;
    return 0;
}