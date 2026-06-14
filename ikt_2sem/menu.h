#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
public:
    void displayMainMenu();
    void displayInputMenu();
    void displayInfo();
    std::string getExpressionFromConsole();
    std::string getExpressionFromFile();
    std::string generateRandomExpression();
    bool askContinue();
    void clearScreen();
    void pause();
};

#endif // MENU_H