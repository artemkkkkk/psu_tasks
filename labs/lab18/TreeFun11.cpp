#include "TreeFun11.h"
#include "Map.h"
#include "Queue.h"
#include "Set.h"
#include <stdexcept>

void TreeFun11::buildParentMap(TreeNode* node, TreeNode* parent, Map<TreeNode*, TreeNode*>& parentMap) {
    if (node == nullptr) {
        return;
    }
    parentMap.put(node, parent);
    buildParentMap(node->getLeft(), node, parentMap);
    buildParentMap(node->getRight(), node, parentMap);
}

DynamicArray<TreeNode*> TreeFun11::getNeighbors(TreeNode* node, const Map<TreeNode*, TreeNode*>& parentMap) {
    DynamicArray<TreeNode*> neighbors;
    if (node->getLeft() != nullptr) {
        neighbors.pushBack(node->getLeft());
    }
    if (node->getRight() != nullptr) {
        neighbors.pushBack(node->getRight());
    }
    if (parentMap.contains(node)) {
        TreeNode* parent = parentMap.get(node);
        if (parent != nullptr) {
            neighbors.pushBack(parent);
        }
    }
    return neighbors;
}

TreeNode* TreeFun11::findNode(int value) const {
    Queue<TreeNode*> q;
    if (root != nullptr) {
        q.push(root);
    }
    while (!q.isEmpty()) {
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

DynamicArray<DynamicArray<int>> TreeFun11::simulateFire(TreeNode* startNode) {
    DynamicArray<DynamicArray<int>> result;
    if (startNode == nullptr) {
        return result;
    }
    Map<TreeNode*, TreeNode*> parentMap;
    buildParentMap(root, nullptr, parentMap);
    Set<TreeNode*> visited;
    Queue<TreeNode*> q;
    q.push(startNode);
    visited.insert(startNode);
    while (!q.isEmpty()) {
        int levelSize = q.getSize();
        DynamicArray<int> currentLevel;
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = q.front();
            q.pop();
            currentLevel.pushBack(current->getValue());
            DynamicArray<TreeNode*> neighbors = getNeighbors(current, parentMap);
            for (int j = 0; j < neighbors.getSize(); ++j) {
                TreeNode* neighbor = neighbors[j];
                if (!visited.contains(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        result.pushBack(currentLevel);
    }
    return result;
}

DynamicArray<int> TreeFun11::getFireOrder(int startValue) {
    TreeNode* startNode = findNode(startValue);
    if (startNode == nullptr) {
        throw std::runtime_error("Узел с значением не найден");
    }
    DynamicArray<DynamicArray<int>> levels = simulateFire(startNode);
    DynamicArray<int> order;
    for (int i = 0; i < levels.getSize(); ++i) {
        for (int j = 0; j < levels[i].getSize(); ++j) {
            order.pushBack(levels[i][j]);
        }
    }
    return order;
}