#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stack>
#include <cmath>

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
    bool checkCommutativeSwap(Node* root) {
        if (!root) return true;
        if (root->getVal() == -1) {
            if (root->getRight() && root->getRight()->getVal() == -100) {
                return false;
            }
        }
        return checkCommutativeSwap(root->getLeft()) && checkCommutativeSwap(root->getRight());
    }

    int evaluate(Node* root, int x_val) {
        if (!root) return 0;
        if (root->getVal() == -100) return x_val;
        if (root->getVal() >= 0) return root->getVal();

        int leftVal = evaluate(root->getLeft(), x_val);
        int rightVal = evaluate(root->getRight(), x_val);

        switch (root->getVal()) {
            case -1: return leftVal + rightVal;
            case -2: return leftVal - rightVal;
            case -3: return leftVal * rightVal;
            case -4: return rightVal != 0 ? leftVal / rightVal : 0;
            case -5: return rightVal != 0 ? leftVal % rightVal : 0;
            case -6: return pow(leftVal, rightVal);
        }
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
        return buildFromInfix(line);
    }

    Node* buildFromString(const string& infix) {
        return buildFromInfix(infix);
    }

    Node* buildFromConsole() {
        cout << "Введите инфиксное выражение: ";
        string line;
        getline(cin, line);
        return buildFromInfix(line);
    }

private:
    int getPriority(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/' || op == '%') return 2;
        if (op == '^') return 3;
        return 0;
    }

    int getOpCode(char op) {
        if (op == '+') return -1;
        if (op == '-') return -2;
        if (op == '*') return -3;
        if (op == '/') return -4;
        if (op == '%') return -5;
        if (op == '^') return -6;
        return 0;
    }

    vector<string> infixToPostfix(const string& infix) {
        vector<string> output;
        stack<char> ops;
        stringstream ss(infix);
        string token;
        while (ss >> token) {
            if (token == "x") {
                output.push_back("x");
            } else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^") {
                while (!ops.empty() && getPriority(ops.top()) >= getPriority(token[0])) {
                    output.push_back(string(1, ops.top()));
                    ops.pop();
                }
                ops.push(token[0]);
            } else if (token == "(") {
                ops.push('(');
            } else if (token == ")") {
                while (!ops.empty() && ops.top() != '(') {
                    output.push_back(string(1, ops.top()));
                    ops.pop();
                }
                if (!ops.empty()) ops.pop();
            } else {
                output.push_back(token);
            }
        }
        while (!ops.empty()) {
            output.push_back(string(1, ops.top()));
            ops.pop();
        }
        return output;
    }

    Node* buildFromInfix(const string& infix) {
        vector<string> postfix = infixToPostfix(infix);
        stack<Node*> st;
        for (const string& token : postfix) {
            if (token == "x") {
                st.push(new Node(-100));
            } else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^") {
                Node* node = new Node(getOpCode(token[0]));
                Node* right = st.top(); st.pop();
                Node* left = st.top(); st.pop();
                node->setLeft(left);
                node->setRight(right);
                st.push(node);
            } else {
                st.push(new Node(stoi(token)));
            }
        }
        return st.empty() ? nullptr : st.top();
    }
};

void printTree(Node* root, string prefix, bool isLeft) {
    if (!root) return;
    printTree(root->getRight(), prefix + (isLeft ? "│   " : "    "), false);
    string valStr = (root->getVal() == -100) ? "x" : to_string(root->getVal());
    cout << prefix << (isLeft ? "┌── " : "└── ") << valStr << "\n";
    printTree(root->getLeft(), prefix + (isLeft ? "    " : "│   "), true);
}

void transformAXtoXA(Node* root) {
    if (!root) return;
    transformAXtoXA(root->getLeft());
    transformAXtoXA(root->getRight());
    if (root->getVal() == -1 && root->getRight() && root->getRight()->getVal() == -100) {
        Node* temp = root->getLeft();
        root->setLeft(root->getRight());
        root->setRight(temp);
    }
}

void writePrefix(Node* root, ofstream& fout) {
    if (!root) return;
    if (root->getVal() == -100) fout << "x ";
    else if (root->getVal() < 0) {
        char op = (root->getVal() == -1) ? '+' : (root->getVal() == -2) ? '-' : (root->getVal() == -3) ? '*' : (root->getVal() == -4) ? '/' : (root->getVal() == -5) ? '%' : '^';
        fout << op << " ";
    } else {
        fout << root->getVal() << " ";
    }
    writePrefix(root->getLeft(), fout);
    writePrefix(root->getRight(), fout);
}

void writePostfix(Node* root, ofstream& fout) {
    if (!root) return;
    writePostfix(root->getLeft(), fout);
    writePostfix(root->getRight(), fout);
    if (root->getVal() == -100) fout << "x ";
    else if (root->getVal() < 0) {
        char op = (root->getVal() == -1) ? '+' : (root->getVal() == -2) ? '-' : (root->getVal() == -3) ? '*' : (root->getVal() == -4) ? '/' : (root->getVal() == -5) ? '%' : '^';
        fout << op << " ";
    } else {
        fout << root->getVal() << " ";
    }
}

void writeInfix(Node* root, ofstream& fout) {
    if (!root) return;
    fout << "(";
    writeInfix(root->getLeft(), fout);
    if (root->getVal() == -100) fout << "x";
    else if (root->getVal() < 0) {
        char op = (root->getVal() == -1) ? '+' : (root->getVal() == -2) ? '-' : (root->getVal() == -3) ? '*' : (root->getVal() == -4) ? '/' : (root->getVal() == -5) ? '%' : '^';
        fout << op;
    } else {
        fout << root->getVal();
    }
    writeInfix(root->getRight(), fout);
    fout << ")";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    TreeBuilder builder;
    TreeValidator validator;

    Node* root = builder.buildFromFile("input1.txt");
    if (!root) {
        root = builder.buildFromString("2 + x * 3");
    }

    cout << "Дерево ДО преобразования:\n";
    printTree(root, "", true);
    cout << "\n";

    int x_val = 5;
    int resultBefore = validator.evaluate(root, x_val);

    transformAXtoXA(root);

    cout << "Дерево ПОСЛЕ преобразования:\n";
    printTree(root, "", true);
    cout << "\n";

    ofstream fout("input2.txt");
    if (fout.is_open()) {
        fout << "Результат при x=" << x_val << ": " << resultBefore << "\n\n";
        fout << "Префиксная: ";
        writePrefix(root, fout);
        fout << "\n";
        fout << "Постфиксная: ";
        writePostfix(root, fout);
        fout << "\n";
        fout << "Инфиксная: ";
        writeInfix(root, fout);
        fout << "\n";
        fout.close();
    }

    bool isValid = validator.checkCommutativeSwap(root);
    cout << "Проверка преобразования A+x -> x+A: " << (isValid ? "УСПЕХ" : "ОШИБКА") << "\n";

    delete root;
    return 0;
}