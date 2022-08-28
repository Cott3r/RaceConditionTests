//
// Created by testing on 28.08.22.
//

#ifndef RACECONDITIONTESTS_ASSIGNMENT3_H
#define RACECONDITIONTESTS_ASSIGNMENT3_H

#include "Assignment.h"
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define TOTAL (10000ull)

class Assignment3 : public Assignment
{
public:
    sem_t buffer_free_elements;
    sem_t buffer_available_elements;
    int buffer[16] = { 0 };

    sem_t buffer_lock;
    ssize_t numbers_produced = 0;
    sem_t numbers_produced_lock;
    ssize_t numbers_consumed = 0;
    sem_t numbers_consumed_lock;
    int cnt = 1;
    sem_t cnt_lock;

    Assignment3(size_t numberOfThreads);

    void execute(size_t number);

    void producer(size_t number);

    void consumer(size_t number);

    string name();

    bool checkOutput();

    void print_number_elements(string name);
};

#endif //RACECONDITIONTESTS_ASSIGNMENT3_H
