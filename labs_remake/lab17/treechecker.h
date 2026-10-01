#ifndef TREECHECKER_H
#define TREECHECKER_H

#include "calctree.h"

class TreeChecker {
private:
    static bool evalPostfixTokens(const int* tokens, int count, int& result);

public:
    static bool checkCalcTree1(
        const int* tokens,
        int count,
        const CalcTree& original,
        const CalcTree& transformed
    );

    static bool checkCalcTree23(
        const CalcTree& original,
        const CalcTree& transformed,
        int x
    );
};

#endif