#include "ExpressionTree.h"
#include <stack>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cmath>

ExpressionTree::ExpressionTree() : root(nullptr) {}

ExpressionTree::ExpressionTree(const ExpressionTree& other) : root(copyTree(other.root)) {}

ExpressionTree& ExpressionTree::operator=(const ExpressionTree& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

ExpressionTree::~ExpressionTree() {
    destroyTree(root);
}

void ExpressionTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }
}

TreeNode* ExpressionTree::copyTree(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TreeNode* newNode;
    if (node->isVar()) {
        newNode = new TreeNode("x");
    } else {
        newNode = new TreeNode(node->getValue());
    }
    newNode->setLeft(copyTree(node->getLeft()));
    newNode->setRight(copyTree(node->getRight()));
    return newNode;
}

TreeNode* ExpressionTree::getRoot() const {
    return root;
}

void ExpressionTree::setRoot(TreeNode* root) {
    this->root = root;
}

bool ExpressionTree::isEmpty() const {
    return root == nullptr;
}

void ExpressionTree::buildFromPostfix(const std::string& expression) {
    std::stack<TreeNode*> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (token == "+") {
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left = stack.top(); stack.pop();
            TreeNode* op = new TreeNode(-1);
            op->setLeft(left);
            op->setRight(right);
            stack.push(op);
        } else if (token == "-") {
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left = stack.top(); stack.pop();
            TreeNode* op = new TreeNode(-2);
            op->setLeft(left);
            op->setRight(right);
            stack.push(op);
        } else if (token == "*") {
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left = stack.top(); stack.pop();
            TreeNode* op = new TreeNode(-3);
            op->setLeft(left);
            op->setRight(right);
            stack.push(op);
        } else if (token == "/") {
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left = stack.top(); stack.pop();
            TreeNode* op = new TreeNode(-4);
            op->setLeft(left);
            op->setRight(right);
            stack.push(op);
        } else if (token == "%") {
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left = stack.top(); stack.pop();
            TreeNode* op = new TreeNode(-5);
            op->setLeft(left);
            op->setRight(right);
            stack.push(op);
        } else if (token == "^") {
            TreeNode* right = stack.top(); stack.pop();
            TreeNode* left = stack.top(); stack.pop();
            TreeNode* op = new TreeNode(-6);
            op->setLeft(left);
            op->setRight(right);
            stack.push(op);
        } else if (token == "x") {
            stack.push(new TreeNode("x"));
        } else {
            int value = std::stoi(token);
            stack.push(new TreeNode(value));
        }
    }

    if (!stack.empty()) {
        root = stack.top();
    }
}

void ExpressionTree::buildFromInfix(const std::string& expression) {
    std::stack<TreeNode*> valueStack;
    std::stack<char> opStack;
    std::string expr = expression;

    auto precedence = [](char op) -> int {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/' || op == '%') return 2;
        if (op == '^') return 3;
        return 0;
    };

    auto applyOperator = [&]() {
        char op = opStack.top();
        opStack.pop();
        TreeNode* right = valueStack.top();
        valueStack.pop();
        TreeNode* left = valueStack.top();
        valueStack.pop();
        TreeNode* opNode;
        if (op == '+') opNode = new TreeNode(-1);
        else if (op == '-') opNode = new TreeNode(-2);
        else if (op == '*') opNode = new TreeNode(-3);
        else if (op == '/') opNode = new TreeNode(-4);
        else if (op == '%') opNode = new TreeNode(-5);
        else if (op == '^') opNode = new TreeNode(-6);
        else throw std::runtime_error("Неизвестная операция");
        opNode->setLeft(left);
        opNode->setRight(right);
        valueStack.push(opNode);
    };

    size_t i = 0;
    while (i < expr.length()) {
        if (std::isspace(expr[i])) {
            i++;
            continue;
        }
        if (expr[i] == '(') {
            opStack.push(expr[i]);
            i++;
        } else if (expr[i] == 'x') {
            valueStack.push(new TreeNode("x"));
            i++;
        } else if (std::isdigit(expr[i])) {
            std::string num;
            while (i < expr.length() && std::isdigit(expr[i])) {
                num += expr[i];
                i++;
            }
            valueStack.push(new TreeNode(std::stoi(num)));
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || 
                   expr[i] == '/' || expr[i] == '%' || expr[i] == '^') {
            while (!opStack.empty() && opStack.top() != '(' &&
                   precedence(opStack.top()) >= precedence(expr[i])) {
                applyOperator();
            }
            opStack.push(expr[i]);
            i++;
        } else if (expr[i] == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                applyOperator();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
            i++;
        } else {
            i++;
        }
    }

    while (!opStack.empty()) {
        applyOperator();
    }

    if (!valueStack.empty()) {
        root = valueStack.top();
    }
}

int ExpressionTree::evaluate(TreeNode* node, int xValue) const {
    if (node == nullptr) {
        throw std::runtime_error("Пустой узел");
    }
    if (node->isVar()) {
        return xValue;
    }
    if (!node->isOperator()) {
        return node->getValue();
    }
    int leftVal = evaluate(node->getLeft(), xValue);
    int rightVal = evaluate(node->getRight(), xValue);
    switch (node->getValue()) {
        case -1: return leftVal + rightVal;
        case -2: return leftVal - rightVal;
        case -3: return leftVal * rightVal;
        case -4:
            if (rightVal == 0) throw std::runtime_error("Деление на ноль");
            return leftVal / rightVal;
        case -5:
            if (rightVal == 0) throw std::runtime_error("Деление на ноль");
            return leftVal % rightVal;
        case -6:
            return static_cast<int>(std::pow(leftVal, rightVal));
        default:
            throw std::runtime_error("Неизвестная операция");
    }
}

int ExpressionTree::calculate(int xValue) const {
    return evaluate(root, xValue);
}

bool ExpressionTree::containsVariable(TreeNode* node) const {
    if (node == nullptr) {
        return false;
    }
    if (node->isVar()) {
        return true;
    }
    return containsVariable(node->getLeft()) || containsVariable(node->getRight());
}

void ExpressionTree::printGraphical(TreeNode* node, const std::string& prefix, bool isLeft, std::ostream& out) const {
    if (node == nullptr) {
        return;
    }
    out << prefix;
    out << (isLeft ? "├── " : "└── ");
    if (node->isVar()) {
        out << "x";
    } else if (node->isOperator()) {
        out << node->getOperatorSymbol();
    } else {
        out << node->getValue();
    }
    out << std::endl;
    printGraphical(node->getLeft(), prefix + (isLeft ? "│   " : "    "), true, out);
    printGraphical(node->getRight(), prefix + (isLeft ? "│   " : "    "), false, out);
}

void ExpressionTree::printGraphical(std::ostream& out) const {
    if (root == nullptr) {
        out << "(пустое дерево)" << std::endl;
        return;
    }
    printGraphical(root, "", true, out);
}

void ExpressionTree::toPrefix(TreeNode* node, std::vector<std::string>& result) const {
    if (node == nullptr) {
        return;
    }
    if (node->isVar()) {
        result.push_back("x");
    } else if (node->isOperator()) {
        result.push_back(node->getOperatorSymbol());
    } else {
        result.push_back(std::to_string(node->getValue()));
    }
    toPrefix(node->getLeft(), result);
    toPrefix(node->getRight(), result);
}

void ExpressionTree::toPostfix(TreeNode* node, std::vector<std::string>& result) const {
    if (node == nullptr) {
        return;
    }
    toPostfix(node->getLeft(), result);
    toPostfix(node->getRight(), result);
    if (node->isVar()) {
        result.push_back("x");
    } else if (node->isOperator()) {
        result.push_back(node->getOperatorSymbol());
    } else {
        result.push_back(std::to_string(node->getValue()));
    }
}

void ExpressionTree::toInfix(TreeNode* node, std::string& result) const {
    if (node == nullptr) {
        return;
    }
    if (!node->isOperator()) {
        if (node->isVar()) {
            result += "x";
        } else {
            result += std::to_string(node->getValue());
        }
        return;
    }
    result += "(";
    toInfix(node->getLeft(), result);
    result += node->getOperatorSymbol();
    toInfix(node->getRight(), result);
    result += ")";
}

std::string ExpressionTree::getPrefixNotation() const {
    std::vector<std::string> result;
    toPrefix(root, result);
    std::string str;
    for (size_t i = 0; i < result.size(); ++i) {
        str += result[i];
        if (i < result.size() - 1) str += " ";
    }
    return str;
}

std::string ExpressionTree::getPostfixNotation() const {
    std::vector<std::string> result;
    toPostfix(root, result);
    std::string str;
    for (size_t i = 0; i < result.size(); ++i) {
        str += result[i];
        if (i < result.size() - 1) str += " ";
    }
    return str;
}

std::string ExpressionTree::getInfixNotation() const {
    std::string result;
    toInfix(root, result);
    return result;
}