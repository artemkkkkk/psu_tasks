#include "expression_converter.h"
#include <iostream>
#include <sstream>

ExpressionConverter::ExpressionConverter() : tempVarCounter(1) {
    validOperators.insert('+');
    validOperators.insert('-');
    validOperators.insert('*');
    validOperators.insert('/');
}

bool ExpressionConverter::isValidOperator(char c) const {
    return validOperators.find(c) != validOperators.end();
}

bool ExpressionConverter::isValidOperand(char c) const {
    return std::isalpha(c) || (c >= '0' && c <= '9');
}

void ExpressionConverter::validateExpression(const std::string& expression) {
    if (expression.empty()) {
        throw ValidationException("Выражение не может быть пустым");
    }
    
    Stack<char> validationStack;
    
    for (char c : expression) {
        if (std::isspace(c)) continue;

        if (isValidOperand(c)) {
            validationStack.push(c);
        } else if (isValidOperator(c)) {
            if (validationStack.size() < 2) {
                throw ValidationException("Некорректное постфиксное выражение: недостаточно операндов");
            }
            validationStack.pop();
            validationStack.pop();
            validationStack.push('R');
        } else {
            throw ValidationException("Недопустимый символ в выражении: " + std::string(1, c));
        }
    }

    if (validationStack.size() != 1) {
        throw ValidationException("Некорректное постфиксное выражение");
    }
}

std::vector<std::string> ExpressionConverter::convertToInstructions(const std::string& postfixExpression) {
    std::vector<std::string> instructions;
    Stack<std::string> operandStack;
    tempVarCounter = 1;
    std::string lastTempVar;

    validateExpression(postfixExpression);

    for (char c : postfixExpression) {
        if (std::isspace(c)) continue;

        if (isValidOperand(c)) {
            operandStack.push(std::string(1, c));
        } else if (isValidOperator(c)) {
            std::string right = operandStack.pop();
            std::string left = operandStack.pop();

            std::string tempVar;
            if (operandStack.isEmpty()) {
                if (!lastTempVar.empty()) {
                    tempVar = lastTempVar;
                } else {
                    tempVar = "T" + std::to_string(tempVarCounter++);
                }
            } else {
                tempVar = "T" + std::to_string(tempVarCounter++);
            }

            lastTempVar = tempVar;

            std::string opCode;
            switch (c) {
                case '+': opCode = "AD"; break;
                case '-': opCode = "SB"; break;
                case '*': opCode = "ML"; break;
                case '/': opCode = "DV"; break;
            }

            instructions.push_back("LD " + left);
            instructions.push_back(opCode + " " + right);
            instructions.push_back("ST " + tempVar);

            operandStack.push(tempVar);
        }
    }

    if (!instructions.empty() && instructions.back().substr(0, 3) == "ST ") {
        instructions.pop_back();
    }
    
    return instructions;
}

void ExpressionConverter::printInstructions(const std::vector<std::string>& instructions) {
    std::cout << "\n=== Сгенерированные инструкции ===\n";
    for (size_t i = 0; i < instructions.size(); ++i) {
        std::cout << instructions[i] << "\n";
    }
    std::cout << "===================================\n";
    std::cout << "Всего инструкций: " << instructions.size() << "\n";
}