//
// Created by testing on 21.07.22.
//

#ifndef RACECONDITIONTESTS_ASSIGNMENT_H
#define RACECONDITIONTESTS_ASSIGNMENT_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "ThreadHelper.h"

using std::stringstream;
using std::string;
using std::endl;

class Assignment
{
public:
    size_t number_of_threads_;
    stringstream output_string_;
    pthread_mutex_t output_string_lock_;

    Assignment(size_t numberOfThreads);

    Assignment(Assignment& org);

    virtual ~Assignment();

    Assignment& operator=(const Assignment &rhs) = delete;

    void execute_internal(size_t number);

    virtual void execute(size_t number) = 0;

    virtual string name() = 0;

    virtual bool checkOutput() = 0;

    void print(string line);
};

#endif //RACECONDITIONTESTS_ASSIGNMENT_H
