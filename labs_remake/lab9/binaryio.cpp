#include "binaryio.h"
#include <fstream>
#include <new>

static const long long MAX_BINARY_ELEMENTS = 1000000LL;

bool writeIntArray(const char* fileName, const int* data, int count) {
    if (!fileName || count < 0) {
        return false;
    }

    std::ofstream out(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!out) {
        return false;
    }

    if (count == 0) {
        return true;
    }

    if (!data) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(data), count * sizeof(int));
    return static_cast<bool>(out);
}

bool readIntArray(const char* fileName, int*& data, int& count) {
    data = 0;
    count = 0;

    if (!fileName) {
        return false;
    }

    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    if (!in) {
        return false;
    }

    in.seekg(0, std::ios::end);
    std::streamoff fileSize = in.tellg();

    if (fileSize < 0) {
        return false;
    }

    if (fileSize == 0) {
        return true;
    }

    long long elements = static_cast<long long>(fileSize) / static_cast<long long>(sizeof(int));

    if (elements <= 0) {
        return true;
    }

    if (elements > MAX_BINARY_ELEMENTS) {
        return false;
    }

    count = static_cast<int>(elements);
    data = new (std::nothrow) int[count];

    if (!data) {
        count = 0;
        return false;
    }

    in.seekg(0, std::ios::beg);
    in.read(reinterpret_cast<char*>(data), count * sizeof(int));

    if (!in) {
        delete[] data;
        data = 0;
        count = 0;
        return false;
    }

    return true;
}

bool truncateIntBinaryFile(const char* fileName, int limit, int& initialCount, int& finalCount) {
    initialCount = 0;
    finalCount = 0;

    if (!fileName || limit < 0) {
        return false;
    }

    int* data = 0;
    int count = 0;

    if (!readIntArray(fileName, data, count)) {
        return false;
    }

    initialCount = count;
    finalCount = count <= limit ? count : limit;

    bool ok = writeIntArray(fileName, data, finalCount);

    delete[] data;
    return ok;
}