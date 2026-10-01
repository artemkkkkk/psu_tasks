#ifdef _WIN32
#include <windows.h>
#endif

#include <clocale>

#include "menu.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    setlocale(LC_ALL, "RU-ru");

    mainMenu();
    return 0;
}