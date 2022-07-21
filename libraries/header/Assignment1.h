//
// Created by testing on 21.07.22.
//

#ifndef RACECONDITIONTESTS_ASSIGNMENT1_H
#define RACECONDITIONTESTS_ASSIGNMENT1_H

#include "Assignment.h"

using namespace std;

class Assignment1 : public Assignment
{
public:
    Assignment1(size_t numberOfThreads) : Assignment(numberOfThreads) {};

    void execute(size_t number);

    string name();

    bool checkOutput();
};

#endif //RACECONDITIONTESTS_ASSIGNMENT1_H
