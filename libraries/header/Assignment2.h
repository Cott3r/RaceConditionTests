//
// Created by testing on 21.07.22.
//

#ifndef RACECONDITIONTESTS_ASSIGNMENT2_H
#define RACECONDITIONTESTS_ASSIGNMENT2_H

#include "Assignment.h"

class Assignment2 : public Assignment
{
public:
    size_t next_executed_number;
    pthread_mutex_t next_executed_number_lock;
    pthread_cond_t  next_executed_number_cond;

    Assignment2(size_t numberOfThreads);

    void execute(size_t number);

    void execute_A();

    void execute_B();

    string name();

    bool checkOutput();
};

#endif //RACECONDITIONTESTS_ASSIGNMENT2_H
