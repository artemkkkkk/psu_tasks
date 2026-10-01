#include "task3.h"
#include "utils.h"
#include "vigenere.h"
#include <iostream>
#include <fstream>
#include <cstring>

static bool inputManual(char* key, char* message) {
    if (!readNonEmptyString("Введите ключ: ", key, 128)) {
        return false;
    }

    if (!vigenereKeyValid(key)) {
        std::cout << "Ключ должен содержать хотя бы одну букву русского алфавита.\n";
        return false;
    }

    if (!readNonEmptyString("Введите сообщение: ", message, 256)) {
        return false;
    }

    return true;
}

static bool inputRandom(char* key, char* message) {
    initRandom();

    static const char* keys[] = { "КОД", "КЛЮЧ", "ШИФР", "СЕКРЕТ" };
    static const char* messages[] = {
        "СЕКРЕТНОЕ СООБЩЕНИЕ",
        "ВАЖНЫЕ НОВОСТИ",
        "ВСТРЕЧА В ПОЛНОЧЬ",
        "ГРУЗ ДОСТАВЛЕН"
    };

    copyString(key, 128, keys[randomInt(0, 3)]);
    copyString(message, 256, messages[randomInt(0, 3)]);

    std::cout << "\nСлучайный ключ: " << key << '\n';
    std::cout << "Случайное сообщение: " << message << '\n';

    return true;
}

static bool inputFile(char* key, char* message) {
    char fileName[256];

    if (!readFileName("Введите имя файла: ", fileName, 256)) {
        return false;
    }

    std::ifstream in(fileName);
    if (!in) {
        std::cout << "Не удалось открыть файл.\n";
        return false;
    }

    char line[256];

    if (!in.getline(key, 128)) {
        std::cout << "Не удалось прочитать ключ.\n";
        return false;
    }

    trimString(key);

    if (!in.getline(message, 256)) {
        std::cout << "Не удалось прочитать сообщение.\n";
        return false;
    }

    trimString(message);

    if (!vigenereKeyValid(key)) {
        std::cout << "Ключ должен содержать хотя бы одну букву русского алфавита.\n";
        return false;
    }

    if (message[0] == '\0') {
        std::cout << "Сообщение пустое.\n";
        return false;
    }

    return true;
}

void runTask3(int mode) {
    char key[128];
    char message[256];

    bool ok = false;

    if (mode == 1) {
        ok = inputManual(key, message);
    } else if (mode == 2) {
        ok = inputRandom(key, message);
    } else if (mode == 3) {
        ok = inputFile(key, message);
    }

    if (!ok) {
        return;
    }

    char encrypted[512];
    char decrypted[512];

    vigenereCrypt(message, key, encrypted, 512, true);
    vigenereCrypt(encrypted, key, decrypted, 512, false);

    std::cout << "\nИсходное сообщение: " << message << '\n';
    std::cout << "Ключ: " << key << '\n';
    std::cout << "Зашифрованное сообщение: " << encrypted << '\n';
    std::cout << "Расшифрованное сообщение: " << decrypted << '\n';

    if (std::strcmp(decrypted, message) == 0) {
        std::cout << "Дешифрование выполнено верно.\n";
    } else {
        std::cout << "Дешифрование дало другой результат!\n";
    }
}