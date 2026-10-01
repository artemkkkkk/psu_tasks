#include "task2.h"
#include "line.h"
#include "dependentline.h"
#include "utils.h"
#include <iostream>
#include <fstream>

static bool inputManual(
    int line1[4],
    int line2[3],
    int modLine1[4],
    int modLine2[3],
    int finalEnd[2]
) {
    std::cout << "Начальная линия 1:\n";

    if (!readInt("X начала: ", -1000, 1000, line1[0])) return false;
    if (!readInt("Y начала: ", -1000, 1000, line1[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, line1[2])) return false;
    if (!readInt("Y конца: ", -1000, 1000, line1[3])) return false;

    std::cout << "Начальная линия 2 (горизонтальная):\n";

    if (!readInt("Y: ", -1000, 1000, line2[0])) return false;
    if (!readInt("X начала: ", -1000, 1000, line2[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, line2[2])) return false;

    std::cout << "Изменение линии 1:\n";

    if (!readInt("X начала: ", -1000, 1000, modLine1[0])) return false;
    if (!readInt("Y начала: ", -1000, 1000, modLine1[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, modLine1[2])) return false;
    if (!readInt("Y конца: ", -1000, 1000, modLine1[3])) return false;

    std::cout << "Изменение линии 2 (горизонтальной):\n";

    if (!readInt("Y: ", -1000, 1000, modLine2[0])) return false;
    if (!readInt("X начала: ", -1000, 1000, modLine2[1])) return false;
    if (!readInt("X конца: ", -1000, 1000, modLine2[2])) return false;

    std::cout << "Новый конец линии 1 (начало не меняется):\n";

    if (!readInt("X конца: ", -1000, 1000, finalEnd[0])) return false;
    if (!readInt("Y конца: ", -1000, 1000, finalEnd[1])) return false;

    return true;
}

static bool inputRandom(
    int line1[4],
    int line2[3],
    int modLine1[4],
    int modLine2[3],
    int finalEnd[2]
) {
    initRandom();

    line1[0] = randomInt(-20, 20);
    line1[1] = randomInt(-20, 20);
    line1[2] = randomInt(-20, 20);
    line1[3] = randomInt(-20, 20);

    line2[0] = randomInt(-20, 20);
    line2[1] = randomInt(-30, -10);
    line2[2] = randomInt(10, 30);

    modLine1[0] = randomInt(-20, 20);
    modLine1[1] = randomInt(-20, 20);
    modLine1[2] = randomInt(-20, 20);
    modLine1[3] = randomInt(-20, 20);

    modLine2[0] = randomInt(-20, 20);
    modLine2[1] = randomInt(-30, -10);
    modLine2[2] = randomInt(10, 30);

    finalEnd[0] = randomInt(-20, 20);
    finalEnd[1] = randomInt(-20, 20);

    std::cout << "\nСлучайные данные сгенерированы.\n";
    return true;
}

static bool inputFile(
    int line1[4],
    int line2[3],
    int modLine1[4],
    int modLine2[3],
    int finalEnd[2]
) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    if (!(in >> line1[0] >> line1[1] >> line1[2] >> line1[3])) {
        std::cout << "Не удалось прочитать данные линии 1.\n";
        return false;
    }

    if (!(in >> line2[0] >> line2[1] >> line2[2])) {
        std::cout << "Не удалось прочитать данные линии 2.\n";
        return false;
    }

    if (!(in >> modLine1[0] >> modLine1[1] >> modLine1[2] >> modLine1[3])) {
        std::cout << "Не удалось прочитать данные изменения линии 1.\n";
        return false;
    }

    if (!(in >> modLine2[0] >> modLine2[1] >> modLine2[2])) {
        std::cout << "Не удалось прочитать данные изменения линии 2.\n";
        return false;
    }

    if (!(in >> finalEnd[0] >> finalEnd[1])) {
        std::cout << "Не удалось прочитать новый конец линии 1.\n";
        return false;
    }

    return true;
}

void runTask2(int mode) {
    int line1Data[4];
    int line2Data[3];
    int modLine1Data[4];
    int modLine2Data[3];
    int finalEndData[2];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(line1Data, line2Data, modLine1Data, modLine2Data, finalEndData);
    } else if (mode == 2) {
        ok = inputRandom(line1Data, line2Data, modLine1Data, modLine2Data, finalEndData);
    } else if (mode == 3) {
        ok = inputFile(line1Data, line2Data, modLine1Data, modLine2Data, finalEndData);
    }

    if (!ok) {
        return;
    }

    Line line1(line1Data[0], line1Data[1], line1Data[2], line1Data[3]);
    Line line2(line2Data[1], line2Data[0], line2Data[2], line2Data[0]);
    DependentLine line3(&line1, &line2);

    std::cout << "\nИсходные линии:\n";

    std::cout << "Линия 1: ";
    line1.print();

    std::cout << "Линия 2: ";
    line2.print();

    std::cout << "Линия 3: ";
    line3.print();

    line1.setCoordinates(modLine1Data[0], modLine1Data[1], modLine1Data[2], modLine1Data[3]);
    line2.setCoordinates(modLine2Data[1], modLine2Data[0], modLine2Data[2], modLine2Data[0]);

    std::cout << "\nПосле изменения линии 1 и линии 2:\n";

    std::cout << "Линия 1: ";
    line1.print();

    std::cout << "Линия 2: ";
    line2.print();

    std::cout << "Линия 3: ";
    line3.print();

    line1.setEnd(Point(finalEndData[0], finalEndData[1]));

    std::cout << "\nПосле изменения только конца линии 1:\n";

    std::cout << "Линия 1: ";
    line1.print();

    std::cout << "Линия 3: ";
    line3.print();

    std::cout << "Координаты линии 3 не изменились, так как изменился только конец линии 1.\n";
}