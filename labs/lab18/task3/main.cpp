#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
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

bool findPath(Node* root, int target, vector<Node*>& path) {
    if (!root) return false;
    path.push_back(root);
    if (root->val == target) return true;
    if (findPath(root->left, target, path) || findPath(root->right, target, path)) {
        return true;
    }
    path.pop_back();
    return false;
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
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int v : vals) insert(root, v);

    cout << "Исходное бинарное дерево:\n";
    printTreeSideways(root, "", true);
    cout << "\n";

    int sourceVal = 25;
    cout << "Источник пожара: " << sourceVal << "\n\n";

    vector<Node*> path;
    if (!findPath(root, sourceVal, path)) {
        cout << "Узел не найден!\n";
        return 0;
    }

    unordered_map<Node*, int> burnTime;
    queue<pair<Node*, int>> q;
    int k = path.size() - 1;

    for (int i = 0; i <= k; ++i) {
        Node* curr = path[i];
        int time = k - i;
        if (burnTime.count(curr) && burnTime[curr] <= time) continue;
        burnTime[curr] = time;

        Node* otherChild = nullptr;
        if (i < k) {
            if (curr->left == path[i+1]) otherChild = curr->right;
            else otherChild = curr->left;
        }

        if (otherChild) {
            q.push({otherChild, time + 1});
        }
        if (i == k) {
            if (curr->left) q.push({curr->left, 1});
            if (curr->right) q.push({curr->right, 1});
        }
    }

    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        Node* node = front.first;
        int time = front.second;
        if (burnTime.count(node) && burnTime[node] <= time) continue;
        burnTime[node] = time;
        if (node->left) q.push({node->left, time + 1});
        if (node->right) q.push({node->right, time + 1});
    }

    struct BurnEvent {
        int time;
        int val;
    };
    vector<BurnEvent> events;
    for (auto& p : burnTime) {
        events.push_back({p.second, p.first->val});
    }
    sort(events.begin(), events.end(), [](const BurnEvent& a, const BurnEvent& b) {
        if (a.time != b.time) return a.time < b.time;
        return a.val < b.val;
    });

    int currentTime = -1;
    for (auto& ev : events) {
        if (ev.time != currentTime) {
            if (currentTime != -1) cout << "\n";
            cout << "Шаг " << ev.time << ": ";
            currentTime = ev.time;
        } else {
            cout << ", ";
        }
        cout << ev.val;
    }
    cout << "\n\n";

    deleteTree(root);
    return 0;
}