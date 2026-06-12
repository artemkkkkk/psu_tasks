#ifndef EXPRESSION_CONVERTER_H
#define EXPRESSION_CONVERTER_H

#include <string>
#include <vector>
#include <set>
#include "stack.h"
#include "exceptions.h"

class ExpressionConverter {
private:
    std::set<char> validOperators;
    int tempVarCounter;

    bool isValidOperator(char c) const;
    bool isValidOperand(char c) const;
    void validateExpression(const std::string& expression);

public:
    ExpressionConverter();

    std::vector<std::string> convertToInstructions(const std::string& postfixExpression);
    void printInstructions(const std::vector<std::string>& instructions);
};

#endif // EXPRESSION_CONVERTER_H