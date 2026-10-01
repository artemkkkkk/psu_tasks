#ifndef VIGENERE_H
#define VIGENERE_H

bool vigenereKeyValid(const char* key);
void vigenereCrypt(const char* message, const char* key, char* out, int outSize, bool encrypt);

#endif