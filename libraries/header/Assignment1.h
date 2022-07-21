//
// Created by testing on 21.07.22.
//

#ifndef RACECONDITIONTESTS_ASSIGNMENT1_H
#define RACECONDITIONTESTS_ASSIGNMENT1_H

#include "Assignment.h"

class Assignment1 : public Assignment
{
public:
    size_t next_executed_number;
    pthread_mutex_t next_executed_number_lock;
    pthread_cond_t  next_executed_number_cond;

    Assignment1(size_t numberOfThreads);

    void execute(size_t number);

    string name();

    bool checkOutput();
};

#endif //RACECONDITIONTESTS_ASSIGNMENT1_H
