#ifndef BINARYIO_H
#define BINARYIO_H

bool writeIntArray(const char* fileName, const int* data, int count);
bool readIntArray(const char* fileName, int*& data, int& count);
bool truncateIntBinaryFile(const char* fileName, int limit, int& initialCount, int& finalCount);

#endif