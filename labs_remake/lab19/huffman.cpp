#include "huffman.h"
#include <iostream>
#include <cstdio>
#include <cstring>

struct HuffNode {
    Symbol sym;
    bool hasSym;
    int freq;
    HuffNode* left;
    HuffNode* right;
};

static HuffNode* makeNode(const Symbol* s, int freq) {
    HuffNode* node = new HuffNode();

    if (s) {
        node->sym = *s;
        node->hasSym = true;
    } else {
        node->hasSym = false;
    }

    node->freq = freq;
    node->left = 0;
    node->right = 0;

    return node;
}

static void huffmanDispose(HuffNode* node) {
    if (!node) {
        return;
    }

    huffmanDispose(node->left);
    huffmanDispose(node->right);
    delete node;
}

static HuffNode* buildTree(const Symbol* distinct, const int* freqs, int d) {
    HuffNode** arr = new HuffNode*[d];

    for (int i = 0; i < d; ++i) {
        arr[i] = makeNode(&distinct[i], freqs[i]);
    }

    int count = d;

    while (count > 1) {
        int m1 = -1;
        int m2 = -1;

        for (int i = 0; i < count; ++i) {
            if (m1 < 0 || arr[i]->freq < arr[m1]->freq) {
                m2 = m1;
                m1 = i;
            } else if (m2 < 0 || arr[i]->freq < arr[m2]->freq) {
                m2 = i;
            }
        }

        HuffNode* parent = makeNode(0, arr[m1]->freq + arr[m2]->freq);
        parent->left = arr[m1];
        parent->right = arr[m2];

        int a = m1 < m2 ? m1 : m2;
        int b = m1 < m2 ? m2 : m1;

        arr[a] = parent;

        for (int i = b; i < count - 1; ++i) {
            arr[i] = arr[i + 1];
        }

        --count;
    }

    HuffNode* root = arr[0];
    delete[] arr;
    return root;
}

static void printCodes(HuffNode* node, char* buffer, int depth, std::ostream& out, int& totalBits) {
    if (!node) {
        return;
    }

    if (node->hasSym) {
        buffer[depth] = '\0';

        out << node->sym.bytes << " : ";

        if (depth > 0) {
            out << buffer;
        } else {
            out << '0';
        }

        out << " (частота " << node->freq << ")\n";

        totalBits += node->freq * (depth > 0 ? depth : 1);
        return;
    }

    buffer[depth] = '0';
    printCodes(node->left, buffer, depth + 1, out, totalBits);

    buffer[depth] = '1';
    printCodes(node->right, buffer, depth + 1, out, totalBits);
}

static void nodeLabel(const HuffNode* node, char* buf, int size) {
    if (node->hasSym) {
        int i = 0;

        while (i < size - 1 && node->sym.bytes[i]) {
            buf[i] = node->sym.bytes[i];
            ++i;
        }

        buf[i] = '\0';
    } else {
        std::snprintf(buf, size, "(%d)", node->freq);
    }
}

static void printTreeRec(HuffNode* node, int level, const char* parentLabel, bool hasParent, std::ostream& out) {
    if (!node) {
        return;
    }

    char label[32];
    nodeLabel(node, label, 32);

    printTreeRec(node->right, level + 1, label, true, out);

    for (int i = 0; i < level; ++i) {
        out << "    ";
    }

    out << label;

    if (hasParent) {
        out << " [<- " << parentLabel << "]";
    } else {
        out << " [root]";
    }

    out << '\n';

    printTreeRec(node->left, level + 1, label, true, out);
}

void huffmanBuildAndReport(const char* text, std::ostream& out) {
    Symbol syms[512];
    int total = parseSymbols(text, syms, 512);

    if (total == 0) {
        out << "Текст пуст.\n";
        return;
    }

    Symbol distinct[256];
    int freqs[256];
    int d = 0;

    for (int i = 0; i < total; ++i) {
        int found = -1;

        for (int j = 0; j < d; ++j) {
            if (symbolsEqual(distinct[j], syms[i])) {
                found = j;
                break;
            }
        }

        if (found >= 0) {
            ++freqs[found];
        } else {
            distinct[d] = syms[i];
            freqs[d] = 1;
            ++d;
        }
    }

    HuffNode* root = buildTree(distinct, freqs, d);

    out << "\nКоды символов:\n";

    char buffer[64];
    int huffmanBits = 0;

    printCodes(root, buffer, 0, out, huffmanBits);

    out << "\nДерево кодирования:\n";
    printTreeRec(root, 0, 0, false, out);

    int uniformBits = 1;
    while ((1 << uniformBits) < d) {
        ++uniformBits;
    }

    out << "\nРазмер при равномерном кодировании: " << total << " * " << uniformBits
        << " = " << total * uniformBits << " бит\n";
    out << "Размер при кодировании Хаффмана: " << huffmanBits << " бит\n";

    huffmanDispose(root);
}