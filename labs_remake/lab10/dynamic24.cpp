#include "dynamic24.h"
#include "queue.h"
#include "utils.h"
#include "nodeio.h"
#include <iostream>
#include <fstream>

static bool inputManual(Queue& q1, Queue& q2) {
    int count = 0;

    if (!readInt("Размер каждой очереди: ", 1, 50, count)) {
        return false;
    }

    std::cout << "Элементы первой очереди добавляются от начала к концу.\n";

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент первой очереди " << (i + 1) << ": ";
        int x = 0;

        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        q1.pushBack(x);
    }

    std::cout << "Элементы второй очереди добавляются от начала к концу.\n";

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент второй очереди " << (i + 1) << ": ";
        int x = 0;

        if (!readIntNoPrompt(-10000, 10000, x)) {
            return false;
        }

        q2.pushBack(x);
    }

    return true;
}

static bool inputRandom(Queue& q1, Queue& q2) {
    initRandom();

    int count = randomInt(3, 8);

    for (int i = 0; i < count; ++i) {
        q1.pushBack(randomInt(-100, 100));
    }

    for (int i = 0; i < count; ++i) {
        q2.pushBack(randomInt(-100, 100));
    }

    std::cout << "\nСлучайные данные:\n";

    std::cout << "Первая очередь: ";
    q1.print();

    std::cout << "Вторая очередь: ";
    q2.print();

    return true;
}

static bool inputFile(Queue& q1, Queue& q2) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    int count = 0;
    if (!(in >> count)) {
        std::cout << "Не удалось прочитать размер очередей.\n";
        return false;
    }

    if (count < 1 || count > 100000) {
        std::cout << "Некорректный размер очередей.\n";
        return false;
    }

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы первой очереди.\n";
            return false;
        }

        q1.pushBack(x);
    }

    for (int i = 0; i < count; ++i) {
        int x = 0;

        if (!(in >> x)) {
            std::cout << "Не удалось прочитать элементы второй очереди.\n";
            return false;
        }

        q2.pushBack(x);
    }

    return true;
}

static void interleaveQueues(Queue& q1, Queue& q2, Queue& result) {
    int count = q1.count();

    TNode* cur1 = q1.headNode();
    TNode* cur2 = q2.headNode();

    TNode* newHead = 0;
    TNode* newTail = 0;

    for (int i = 0; i < count; ++i) {
        TNode* next1 = cur1 ? cur1->Next : 0;
        TNode* next2 = cur2 ? cur2->Next : 0;

        if (!newHead) {
            newHead = cur1;
            newTail = cur2;
        } else {
            newTail->Next = cur1;
            newTail = cur2;
        }

        if (cur1) {
            cur1->Next = cur2;
        }

        if (cur2) {
            cur2->Next = next1;
        }

        cur1 = next1;
        cur2 = next2;
    }

    if (newTail) {
        newTail->Next = 0;
    }

    q1.release();
    q2.release();
    result.adopt(newHead, newTail, count * 2);
}

void runDynamic24(int mode) {
    Queue q1;
    Queue q2;
    Queue result;

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(q1, q2);
    } else if (mode == 2) {
        ok = inputRandom(q1, q2);
    } else if (mode == 3) {
        ok = inputFile(q1, q2);
    }

    if (!ok) {
        return;
    }

    if (q1.isEmpty() || q2.isEmpty()) {
        std::cout << "По условию очереди должны быть непустыми.\n";
        return;
    }

    if (q1.count() != q2.count()) {
        std::cout << "По условию очереди должны содержать одинаковое количество элементов.\n";
        return;
    }

    std::cout << "\nПервая очередь: ";
    q1.print();

    std::cout << "Вторая очередь: ";
    q2.print();

    interleaveQueues(q1, q2, result);

    std::cout << "Полученная очередь: ";
    result.print();

    printNodePointer("Адрес начала полученной очереди: ", result.headNode());
    printNodePointer("Адрес конца полученной очереди: ", result.tailNode());
}