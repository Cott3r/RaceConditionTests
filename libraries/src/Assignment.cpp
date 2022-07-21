//
// Created by testing on 21.07.22.
//

#include "ThreadHelper.h"
#include "Assignment.h"


Assignment::Assignment(size_t numberOfThreads) :  number_of_threads_(numberOfThreads),
                                                  output_string_(""),
                                                  output_string_lock_(PTHREAD_MUTEX_INITIALIZER)
{

}

Assignment::Assignment(Assignment& org):  number_of_threads_(org.number_of_threads_),
                                          output_string_(""),
                                          output_string_lock_(PTHREAD_MUTEX_INITIALIZER)
{

}

Assignment::~Assignment()
{

}

void Assignment::execute_internal(size_t number)
{
  this->execute(number);
}

void Assignment::print(string line)
{
  pthread_mutex_lock(&output_string_lock_);
  output_string_ << line << endl;
  pthread_mutex_unlock(&output_string_lock_);
}
