//
// Created by testing on 08.07.22.
//

#include "Factory.h"
#include "ThreadHelper.h"

Factory::Factory(size_t factoryNumber) : factoryNumber_(factoryNumber) {}


string Factory::name()
{
  return "Factory";
}

size_t Factory::run()
{
  ThreadHelper::printLine(this->name() + "Factory <" + to_string(this->factoryNumber_) + "> Start run");
  size_t returnValue = 2;





  ThreadHelper::printLine(this->name() + "Factory <" + to_string(this->factoryNumber_) + "> End run Returnvalue <" + to_string(returnValue) + ">");
  return returnValue;
}
