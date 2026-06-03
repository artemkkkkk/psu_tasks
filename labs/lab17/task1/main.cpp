#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stack>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

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
    void setVal(int v) { val = v; }
    Node* getLeft() const { return left; }
    void setLeft(Node* l) { left = l; }
    Node* getRight() const { return right; }
    void setRight(Node* r) { right = r; }
};

class TreeValidator {
public:
    bool hasSubtraction(Node* root) {
        if (!root) return false;
        if (root->getVal() == -2) return true;
        return hasSubtraction(root->getLeft()) || hasSubtraction(root->getRight());
    }

    int evaluate(Node* root) {
        if (!root) return 0;
        if (root->getVal() >= 0) return root->getVal();
        int leftVal = evaluate(root->getLeft());
        int rightVal = evaluate(root->getRight());
        if (root->getVal() == -1) return leftVal + rightVal;
        if (root->getVal() == -2) return leftVal - rightVal;
        if (root->getVal() == -3) return leftVal * rightVal;
        return 0;
    }
};

class TreeBuilder {
public:
    Node* buildFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) return nullptr;
        string line;
        getline(fin, line);
        return buildFromRPN(line);
    }

    Node* buildFromString(const string& rpn) {
        return buildFromRPN(rpn);
    }

    Node* buildFromConsole() {
        cout << "Vvedite RPN vyrazhenie: ";
        string line;
        getline(cin, line);
        return buildFromRPN(line);
    }

private:
    Node* buildFromRPN(const string& rpn) {
        stack<Node*> st;
        stringstream ss(rpn);
        string token;
        while (ss >> token) {
            if (token == "+") st.push(new Node(-1));
            else if (token == "-") st.push(new Node(-2));
            else if (token == "*") st.push(new Node(-3));
            else {
                st.push(new Node(stoi(token)));
            }

            if (token == "+" || token == "-" || token == "*") {
                Node* right = st.top(); st.pop();
                Node* left = st.top(); st.pop();
                st.top()->setLeft(left);
                st.top()->setRight(right);
            }
        }
        return st.empty() ? nullptr : st.top();
    }
};

void printTree(Node* root, string prefix, bool isLeft) {
    if (!root) return;
    printTree(root->getRight(), prefix + (isLeft ? "│   " : "    "), false);
    string valStr = to_string(root->getVal());
    cout << prefix << (isLeft ? "┌── " : "└── ") << valStr << "\n";
    printTree(root->getLeft(), prefix + (isLeft ? "    " : "│   "), true);
}

void removeSubtraction(Node* root) {
    if (!root) return;

    removeSubtraction(root->getLeft());
    removeSubtraction(root->getRight());

    if (root->getVal() == -2) {
        TreeValidator validator;
        int res = validator.evaluate(root);

        Node* oldLeft = root->getLeft();
        Node* oldRight = root->getRight();

        root->setLeft(nullptr);
        root->setRight(nullptr);

        delete oldLeft;
        delete oldRight;

        root->setVal(res);
    }
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
        root = builder.buildFromString("3 4 - 5 *");
    }

    cout << "Дерево до преобразования:\n";
    printTree(root, "", true);
    cout << "\n";

    removeSubtraction(root);

    cout << "Дерево после преобразования:\n";
    printTree(root, "", true);
    cout << "\n";

    bool isValid = !validator.hasSubtraction(root);
    cout << "Проверка отсутствия вычитания: " << (isValid ? "Успех" : "Ошибка") << "\n";
    cout << "Указатель на корень: " << root << "\n";

    delete root;
    return 0;
}