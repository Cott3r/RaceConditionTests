//
// Created by testing on 08.07.22.
//

#ifndef RACECONDITIONTESTS_FACTORY_H
#define RACECONDITIONTESTS_FACTORY_H

#include <iostream>
#include "Assignment.h"

using std::string;

class Assignment;

class Factory
{
public:
    inline static size_t nextFactoryNumber_ = 0;
    inline static size_t waiting_to_start_run_counter = 0;
    inline static pthread_mutex_t waiting_to_start_run_counter_lock = PTHREAD_MUTEX_INITIALIZER;
    inline static pthread_cond_t waiting_to_start_run_counter_condition = PTHREAD_COND_INITIALIZER;

    inline static size_t waiting_to_end_run_counter = 0;
    inline static pthread_mutex_t waiting_to_end_run_counter_lock = PTHREAD_MUTEX_INITIALIZER;
    inline static pthread_cond_t waiting_to_end_run_counter_condition = PTHREAD_COND_INITIALIZER;

    Factory(Assignment* assignment1);

    Assignment* assignment_;
    size_t factoryNumber_;

    string name();

    size_t run();

    void waitToStartRun();

    void waitToEndRun();
};


#endif //RACECONDITIONTESTS_FACTORY_H
