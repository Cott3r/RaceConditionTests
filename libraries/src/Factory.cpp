//
// Created by testing on 08.07.22.
//

#include "Factory.h"

Factory::Factory(Assignment* assignment) : assignment_(assignment), factoryNumber_(nextFactoryNumber_++) {}


string Factory::name()
{
  return "Factory";
}

size_t Factory::run()
{
//  ThreadHelper::printLine("Factory <" + to_string(this->factoryNumber_) + "> Start run");
  size_t returnValue = 0;


  Factory::waitToStartRun();
  assignment_->execute_internal(factoryNumber_);
  Factory::waitToEndRun();



//  ThreadHelper::printLine("Factory <" + to_string(this->factoryNumber_) + "> End run Returnvalue <" + to_string(returnValue) + ">");
  return returnValue;
}

void Factory::waitToStartRun()
{
  //Count the number of threads that are waiting to run execute_internal
  pthread_mutex_lock(&waiting_to_start_run_counter_lock);
  waiting_to_start_run_counter++;

  //Wait for all other threads until all threads are waiting
  while(waiting_to_start_run_counter < assignment_->number_of_threads_)
    pthread_cond_wait(&waiting_to_start_run_counter_condition, &waiting_to_start_run_counter_lock);
  pthread_mutex_unlock(&waiting_to_start_run_counter_lock);

  //Tell all other threads, that now every thread is waiting
  pthread_cond_broadcast(&waiting_to_start_run_counter_condition);
}

void Factory::waitToEndRun()
{
  //Count the number of threads that are waiting to run execute_internal
  pthread_mutex_lock(&waiting_to_end_run_counter_lock);
  waiting_to_end_run_counter++;

  //Wait for all other threads until all threads are waiting
  while(waiting_to_end_run_counter < assignment_->number_of_threads_)
    pthread_cond_wait(&waiting_to_end_run_counter_condition, &waiting_to_end_run_counter_lock);
  pthread_mutex_unlock(&waiting_to_end_run_counter_lock);

  //Tell all other threads, that now every thread is waiting
  pthread_cond_broadcast(&waiting_to_end_run_counter_condition);
}
