#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
public:
    void displayMainMenu();
    void displayInfo();
    std::string getExpressionInput();
    bool askContinue();
    void clearScreen();
    void pause();
};

#endif // MENU_H