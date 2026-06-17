#include "DoublyList.h"

DoublyList::DoublyList() : head(nullptr), tail(nullptr) {}

DoublyList::DoublyList(TreeNode* head, TreeNode* tail) : head(head), tail(tail) {}

TreeNode* DoublyList::getHead() const {
    return head;
}

TreeNode* DoublyList::getTail() const {
    return tail;
}

void DoublyList::printForward(std::ostream& out) const {
    if (head == nullptr) {
        out << "(пустой список)" << std::endl;
        return;
    }
    TreeNode* current = head;
    out << "Прямой порядок: ";
    while (current != nullptr) {
        out << current->getValue();
        if (current->getRight() != nullptr) {
            out << " <-> ";
        }
        current = current->getRight();
    }
    out << std::endl;
}

void DoublyList::printBackward(std::ostream& out) const {
    if (tail == nullptr) {
        out << "(пустой список)" << std::endl;
        return;
    }
    TreeNode* current = tail;
    out << "Обратный порядок: ";
    while (current != nullptr) {
        out << current->getValue();
        if (current->getLeft() != nullptr) {
            out << " <-> ";
        }
        current = current->getLeft();
    }
    out << std::endl;
}