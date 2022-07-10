//
// Created by testing on 09.07.22.
//

#include "ThreadHelper.h"


int ThreadHelper::runFactory(Factory* factory)
{
  return factory->run();
}


bool ThreadHelper::runTest(Factory* factory)
{
  pthread_t tid[10] = {0};
  int tid_num = 0;
  size_t returnValue;

  //Start tests in new Threads
  pthread_create(&tid[tid_num++], 0, (void*(*)(void*))runFactory, (void*)factory);
//  pthread_create(&tid[tid_num++], 0, (void*(*)(void*))runFactory, (void*)new Factory(1));
//  pthread_create(&tid[tid_num++], 0, (void*(*)(void*))runFactory, (void*)new Factory(2));


  //Wait for tests to finish
  while(--tid_num >= 0)
    pthread_join((tid[tid_num]), (void **) &returnValue);

  return true;
}

void ThreadHelper::printLine(string line)
{
  pthread_mutex_lock(&print_Lock);

  cout << line.c_str() << endl;

  pthread_mutex_unlock(&print_Lock);
}
