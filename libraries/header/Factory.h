//
// Created by testing on 08.07.22.
//

#ifndef RACECONDITIONTESTS_FACTORY_H
#define RACECONDITIONTESTS_FACTORY_H

#include <iostream>

using namespace std;

class Factory
{
public:
    Factory(size_t factoryNumber);

    size_t factoryNumber_;

    string name();

    size_t run();
};


#endif //RACECONDITIONTESTS_FACTORY_H
