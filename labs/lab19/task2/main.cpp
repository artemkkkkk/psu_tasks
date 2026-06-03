#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string str, map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
        return;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

void printTreeSideways(Node* root, string prefix, bool isLeft, const map<char, string>& huffmanCode) {
    if (root == nullptr) return;

    printTreeSideways(root->right, prefix + (isLeft ? "│   " : "    "), false, huffmanCode);

    cout << prefix;
    cout << (isLeft ? "┌──" : "└──");

    if (!root->left && !root->right) {
        string charDisplay = (root->ch == ' ') ? "' '" : string(1, root->ch);
        cout << " [" << charDisplay << "] : " << huffmanCode.at(root->ch)
             << " (частота: " << root->freq << ")\n";
    } else {
        cout << " Внутренний узел (сумма частот: " << root->freq << ")\n";
    }

    printTreeSideways(root->left, prefix + (isLeft ? "    " : "│   "), true, huffmanCode);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // Включаем UTF-8 в выводе консоли
    SetConsoleCP(CP_UTF8);        // (опционально) для ввода
#endif

    string text = "abracadabra";
    cout << "Исходный текст: \"" << text << "\"" << endl;
    cout << "Длина текста: " << text.length() << " символов\n" << endl;

    map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (auto pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    Node* root = minHeap.top();

    map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "=== ДЕРЕВО КОДИРОВАНИЯ ХАФФМАНА ===" << endl;
    printTreeSideways(root, "", true, huffmanCode);
    cout << "===================================\n" << endl;

    int uniformSize = text.length() * 8;
    int huffmanSize = 0;

    cout << "=== ТАБЛИЦА КОДИРОВАНИЯ ===" << endl;
    cout << "Символ | Частота | Код Хаффмана | Размер в битах" << endl;
    cout << "------------------------------------------------" << endl;
    for (auto pair : freqMap) {
        string code = huffmanCode[pair.first];
        int bitsForChar = pair.second * code.length();
        huffmanSize += bitsForChar;

        string charDisplay = (pair.first == ' ') ? "' '" : string(1, pair.first);
        cout << "  " << charDisplay << "   |    " << pair.second
             << "    | " << code << string(10 - code.length(), ' ') << "| " << bitsForChar << endl;
    }

    cout << "\n=== СРАВНЕНИЕ РАЗМЕРОВ ===" << endl;
    cout << "Размер при равномерном кодировании (8 бит/символ): " << uniformSize << " бит" << endl;
    cout << "Размер при кодировании Хаффмана:                   " << huffmanSize << " бит" << endl;
    cout << "Экономия места: " << uniformSize - huffmanSize << " бит ("
         << (100.0 * (uniformSize - huffmanSize) / uniformSize) << "%)" << endl;

    deleteTree(root);

    return 0;
}