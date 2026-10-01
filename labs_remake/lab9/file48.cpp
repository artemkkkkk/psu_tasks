#include "file48.h"
#include "utils.h"
#include "binaryio.h"
#include <iostream>
#include <fstream>
#include <new>

static const int MAX_FILE48_COUNT = 10000;

static bool inputArray(const char* title, int* arr, int count) {
    std::cout << title << '\n';

    for (int i = 0; i < count; ++i) {
        std::cout << "Элемент " << (i + 1) << ": ";
        if (!readIntNoPrompt(-100000, 100000, arr[i])) {
            return false;
        }
    }

    return true;
}

static bool prepareManual(int*& a, int*& b, int*& c, int& count) {
    if (!readInt("Размер каждого файла: ", 1, 8, count)) {
        return false;
    }

    a = new (std::nothrow) int[count];
    b = new (std::nothrow) int[count];
    c = new (std::nothrow) int[count];

    if (!a || !b || !c) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!inputArray("Файл SA:", a, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!inputArray("Файл SB:", b, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!inputArray("Файл SC:", c, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!writeIntArray("file48_SA.bin", a, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!writeIntArray("file48_SB.bin", b, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!writeIntArray("file48_SC.bin", c, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    std::cout << "Созданы файлы file48_SA.bin, file48_SB.bin, file48_SC.bin\n";
    return true;
}

static bool prepareRandom(int*& a, int*& b, int*& c, int& count) {
    initRandom();

    count = randomInt(3, 8);

    a = new (std::nothrow) int[count];
    b = new (std::nothrow) int[count];
    c = new (std::nothrow) int[count];

    if (!a || !b || !c) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    for (int i = 0; i < count; ++i) {
        a[i] = randomInt(-1000, 1000);
        b[i] = randomInt(-1000, 1000);
        c[i] = randomInt(-1000, 1000);
    }

    if (!writeIntArray("file48_SA.bin", a, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!writeIntArray("file48_SB.bin", b, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    if (!writeIntArray("file48_SC.bin", c, count)) {
        delete[] a;
        delete[] b;
        delete[] c;
        a = b = c = 0;
        return false;
    }

    std::cout << "\nСлучайные данные:\n";
    std::cout << "Размер файлов: " << count << '\n';

    std::cout << "SA: ";
    for (int i = 0; i < count; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

    std::cout << "SB: ";
    for (int i = 0; i < count; ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << '\n';

    std::cout << "SC: ";
    for (int i = 0; i < count; ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << '\n';

    return true;
}

static bool interleaveFiles(const int* a, const int* b, const int* c, int count, const char* outputName) {
    if (count < 0) {
        return false;
    }

    if (count == 0) {
        return writeIntArray(outputName, 0, 0);
    }

    int* out = new (std::nothrow) int[count * 3];

    if (!out) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        out[i * 3] = a[i];
        out[i * 3 + 1] = b[i];
        out[i * 3 + 2] = c[i];
    }

    bool ok = writeIntArray(outputName, out, count * 3);

    delete[] out;
    return ok;
}

static void printFile48Result(bool ok, const char* outputName, int count) {
    std::ofstream out("output_file48.txt");

    std::cout << "\nРезультат:\n";

    if (!ok) {
        std::cout << "Не удалось создать итоговый файл.\n";

        if (out) {
            out << "Error\n";
        }

        return;
    }

    std::cout << "Итоговый файл создан: " << outputName << '\n';
    std::cout << "Размер каждого исходного файла: " << count << '\n';
    std::cout << "Размер итогового файла: " << (count * 3) << '\n';

    if (out) {
        out << count * 3 << '\n';
    }
}

void runFile48(int mode) {
    int* a = 0;
    int* b = 0;
    int* c = 0;
    int count = 0;

    char sa[256];
    char sb[256];
    char sc[256];
    char sd[256];

    sa[0] = '\0';
    sb[0] = '\0';
    sc[0] = '\0';
    sd[0] = '\0';

    bool ok = false;

    if (mode == 1) {
        ok = prepareManual(a, b, c, count);
        copyString(sd, 256, "file48_SD.bin");
    } else if (mode == 2) {
        ok = prepareRandom(a, b, c, count);
        copyString(sd, 256, "file48_SD.bin");
    } else if (mode == 3) {
        if (!readFileName("Введите имя файла SA: ", sa, 256)) {
            return;
        }

        if (!readFileName("Введите имя файла SB: ", sb, 256)) {
            return;
        }

        if (!readFileName("Введите имя файла SC: ", sc, 256)) {
            return;
        }

        if (!readFileName("Введите имя выходного файла: ", sd, 256)) {
            return;
        }

        int ca = 0;
        int cb = 0;
        int cc = 0;

        if (!readIntArray(sa, a, ca)) {
            std::cout << "Не удалось прочитать файл SA.\n";
            return;
        }

        if (!readIntArray(sb, b, cb)) {
            std::cout << "Не удалось прочитать файл SB.\n";
            delete[] a;
            return;
        }

        if (!readIntArray(sc, c, cc)) {
            std::cout << "Не удалось прочитать файл SC.\n";
            delete[] a;
            delete[] b;
            return;
        }

        if (ca != cb || ca != cc) {
            std::cout << "Файлы должны иметь одинаковый размер.\n";
            delete[] a;
            delete[] b;
            delete[] c;
            return;
        }

        if (ca > MAX_FILE48_COUNT) {
            std::cout << "Файлы слишком большие.\n";
            delete[] a;
            delete[] b;
            delete[] c;
            return;
        }

        count = ca;
        ok = true;
    }

    if (!ok) {
        delete[] a;
        delete[] b;
        delete[] c;
        return;
    }

    ok = interleaveFiles(a, b, c, count, sd);
    printFile48Result(ok, sd, count);

    delete[] a;
    delete[] b;
    delete[] c;
}