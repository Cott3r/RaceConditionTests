//
// Created by testing on 09.07.22.
//

#ifndef RACECONDITIONTESTS_THREADHELPER_H
#define RACECONDITIONTESTS_THREADHELPER_H


#include "pthread.h"
#include "Factory.h"
#include <string>

using std::string;

//Forward declaration
class Factory;
class Assignment;


class ThreadHelper
{
    static size_t runFactory(Factory* factory);
    inline static pthread_mutex_t print_Lock = PTHREAD_MUTEX_INITIALIZER;

public:
    static bool runTest(Assignment* assignment);

    static void printLine(string line);

    static void SetUp();
};


#endif //RACECONDITIONTESTS_THREADHELPER_H
