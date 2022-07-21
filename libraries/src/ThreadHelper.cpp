//
// Created by testing on 09.07.22.
//

#include "ThreadHelper.h"
#include "Assignment1.h"


size_t ThreadHelper::runFactory(Factory* factory)
{
  size_t return_value = factory->run();

  delete factory;

  return return_value;
}


bool ThreadHelper::runTest(Assignment* assignment)
{
  size_t number_of_threads = assignment->number_of_threads_;
  pthread_t tid[number_of_threads];
  int tid_num = 0;
  size_t returnValue;

  //Start tests in new Threads
  for (size_t i = 0; i < number_of_threads; ++i)
    pthread_create(&tid[tid_num++], 0, (void*(*)(void*))runFactory, (void*)new Factory(assignment));


  //Wait for tests to finish
  while(--tid_num >= 0)
    pthread_join((tid[tid_num]), (void **) &returnValue);



  //Check the test result
  return assignment->checkOutput();
}

void ThreadHelper::printLine(string line)
{
  pthread_mutex_lock(&print_Lock);

  cout << line.c_str() << endl;

  pthread_mutex_unlock(&print_Lock);
}

void ThreadHelper::SetUp()
{
  Factory::nextFactoryNumber_ = 0;

  pthread_mutex_lock(&Factory::waiting_to_start_run_counter_lock);
  Factory::waiting_to_start_run_counter = 0;
  pthread_mutex_unlock(&Factory::waiting_to_start_run_counter_lock);

  pthread_mutex_lock(&Factory::waiting_to_end_run_counter_lock);
  Factory::waiting_to_end_run_counter = 0;
  pthread_mutex_unlock(&Factory::waiting_to_end_run_counter_lock);
}
