//
// Created by testing on 09.07.22.
//

#ifndef RACECONDITIONTESTS_THREADHELPER_H
#define RACECONDITIONTESTS_THREADHELPER_H


#include "pthread.h"
#include "Factory.h"

class ThreadHelper
{
    static int runFactory(Factory* factory);
    inline static pthread_mutex_t print_Lock = PTHREAD_MUTEX_INITIALIZER;

public:
    static bool runTest(Factory* factory);

    static void printLine(string line);
};


#endif //RACECONDITIONTESTS_THREADHELPER_H
