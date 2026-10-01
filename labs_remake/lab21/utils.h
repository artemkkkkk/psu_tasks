#ifndef UTILS_H
#define UTILS_H

bool readInt(const char* prompt, int min, int max, int& value);
bool readIntNoPrompt(int min, int max, int& value);
bool readFileName(const char* prompt, char* buffer, int bufferSize);
void initRandom();
int randomInt(int min, int max);

#endif