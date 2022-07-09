//
// Created by testing on 08.07.22.
//

#include "Factory.h"

string Factory::toString()
{
  return "Test";
}

bool Factory::runTest()
{
  pthread_t tid;
  int returnValue;

  pthread_create(&tid, 0, (void*(*)(void*))runFactory, 0);
  pthread_join(tid, (void**)&returnValue);

  return returnValue == 1;
}

int Factory::runFactory()
{
  cout << "runFactory" << endl;

  return 1;
}
