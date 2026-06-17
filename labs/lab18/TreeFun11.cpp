#include "TreeFun11.h"
#include <queue>
#include <set>
#include <stdexcept>

void TreeFun11::buildParentMap(TreeNode* node, TreeNode* parent, std::map<TreeNode*, TreeNode*>& parentMap) {
    if (node == nullptr) {
        return;
    }
    parentMap[node] = parent;
    buildParentMap(node->getLeft(), node, parentMap);
    buildParentMap(node->getRight(), node, parentMap);
}

std::vector<TreeNode*> TreeFun11::getNeighbors(TreeNode* node, const std::map<TreeNode*, TreeNode*>& parentMap) {
    std::vector<TreeNode*> neighbors;
    if (node->getLeft() != nullptr) {
        neighbors.push_back(node->getLeft());
    }
    if (node->getRight() != nullptr) {
        neighbors.push_back(node->getRight());
    }
    auto it = parentMap.find(node);
    if (it != parentMap.end() && it->second != nullptr) {
        neighbors.push_back(it->second);
    }
    return neighbors;
}

TreeNode* TreeFun11::findNode(int value) const {
    std::queue<TreeNode*> q;
    if (root != nullptr) {
        q.push(root);
    }
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current->getValue() == value) {
            return current;
        }
        if (current->getLeft() != nullptr) {
            q.push(current->getLeft());
        }
        if (current->getRight() != nullptr) {
            q.push(current->getRight());
        }
    }
    return nullptr;
}

std::vector<std::vector<int>> TreeFun11::simulateFire(TreeNode* startNode) {
    std::vector<std::vector<int>> result;
    if (startNode == nullptr) {
        return result;
    }
    std::map<TreeNode*, TreeNode*> parentMap;
    buildParentMap(root, nullptr, parentMap);
    std::set<TreeNode*> visited;
    std::queue<TreeNode*> q;
    q.push(startNode);
    visited.insert(startNode);
    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int> currentLevel;
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = q.front();
            q.pop();
            currentLevel.push_back(current->getValue());
            std::vector<TreeNode*> neighbors = getNeighbors(current, parentMap);
            for (TreeNode* neighbor : neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        result.push_back(currentLevel);
    }
    return result;
}

std::vector<int> TreeFun11::getFireOrder(int startValue) {
    TreeNode* startNode = findNode(startValue);
    if (startNode == nullptr) {
        throw std::runtime_error("Узел с значением " + std::to_string(startValue) + " не найден");
    }
    std::vector<std::vector<int>> levels = simulateFire(startNode);
    std::vector<int> order;
    for (const auto& level : levels) {
        for (int value : level) {
            order.push_back(value);
        }
    }
    return order;
}