//
// Created by testing on 21.07.22.
//

#include "Assignment2.h"

Assignment2::Assignment2(size_t numberOfThreads) : Assignment(numberOfThreads),
                                                   next_executed_number(0),
                                                   next_executed_number_lock(PTHREAD_MUTEX_INITIALIZER),
                                                   next_executed_number_cond(PTHREAD_COND_INITIALIZER)
{

}

//This method 'execute' is called by multiple Threads

//***Parameters***
//Each Thread has a unique ascending number and this number is passed to this method as the parameter 'number'

void Assignment2::execute(size_t number)
{
  //****Do not change this Method****
  for (int i = 0; i < 10; ++i)
  {
    sched_yield();
    if(number % 2)
      execute_A();
    else
      execute_B();
    sched_yield();
  }
}


//***GOAL***
//The goal is that the Methods 'producer' and 'consumer' must be executed alternating
void Assignment2::execute_A()
{
  pthread_mutex_lock(&next_executed_number_lock);
  while(next_executed_number != 0)
    pthread_cond_wait(&next_executed_number_cond, &next_executed_number_lock);

  print("Execute A");

  next_executed_number = 1;
  pthread_mutex_unlock(&next_executed_number_lock);
  pthread_cond_broadcast(&next_executed_number_cond);
}

void Assignment2::execute_B()
{
  pthread_mutex_lock(&next_executed_number_lock);
  while(next_executed_number != 1)
    pthread_cond_wait(&next_executed_number_cond, &next_executed_number_lock);

  print("Execute B");

  next_executed_number = 0;
  pthread_mutex_unlock(&next_executed_number_lock);
  pthread_cond_broadcast(&next_executed_number_cond);
}

bool Assignment2::checkOutput()
{
  char output_line[1000] = {0};
  bool a_side = true;
  string expected_value = "Execute A";
  string actual_value;
  bool return_value = true;

  //Go through all lines in asc order
  pthread_mutex_lock(&output_string_lock_);
  output_string_.getline(output_line, sizeof(output_line));
  while(output_line[0] != 0)
  {
    actual_value = string(output_line);

    stringstream line_output;
    line_output << "Expected: " << std::setw(6) << expected_value << "\t\t";
    line_output << "Actual: " << std::setw(6) << output_line;

    if(expected_value != actual_value)
    {
      line_output << "\t\tERROR";
      return_value = false;
    }

    ThreadHelper::printLine(line_output.str());

    a_side = !a_side;
    if(a_side)
      expected_value = "Execute A";
    else
      expected_value = "Execute B";
    output_string_.getline(output_line, sizeof(output_line));
  }
  pthread_mutex_unlock(&output_string_lock_);

  return return_value;
}

string Assignment2::name()
{
  return "Assignment2";
}