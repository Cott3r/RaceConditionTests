//
// Created by testing on 28.08.22.
//

#include "Assignment3.h"

Assignment3::Assignment3(size_t numberOfThreads) : Assignment(numberOfThreads)
{
  sem_init(&buffer_free_elements,0,16);
  sem_init(&buffer_available_elements,0,0);
  sem_init(&buffer_lock,0,1);
  sem_init(&numbers_produced_lock,0,1);
  sem_init(&numbers_consumed_lock,0,1);
  sem_init(&cnt_lock,0,1);
}

//This method 'execute' is called by multiple Threads

//***Parameters***
//Each Thread has a unique ascending number and this number is passed to this method as the parameter 'number'

void Assignment3::execute(size_t number)
{
  //****Do not change this Method****
    if(number % 2)
      producer(number);
    else
      consumer(number);
}


//***GOAL***
//The goal is that the Methods 'producer' and 'consumer' must be executed alternating
void Assignment3::producer(size_t number)
{
  print("Start producer: " + to_string(number));

  sem_wait(&numbers_produced_lock);
  while (numbers_produced < TOTAL)
  {
    numbers_produced++;
    sem_post(&numbers_produced_lock);
    int success = 0;
    sem_wait(&cnt_lock);
    int r = cnt++;
    sem_post(&cnt_lock);
    {
      sem_wait(&buffer_free_elements);
      sem_wait(&buffer_lock);
      print_number_elements("Producer: " + to_string(number));
      for (size_t i = 0; i < 16; ++i)
      {
        if (buffer[i] == 0)
        {
          buffer[i] = r;
          success = 1;
          break;
        }
      }
      if (success == 0)
        exit(printf("ERRRRRORRRR!!!!!\n"));


      sem_post(&buffer_lock);
      sem_post(&buffer_available_elements);

    }
    sem_wait(&numbers_produced_lock);
  }
  sem_post(&numbers_produced_lock);

}

void Assignment3::consumer(size_t number)
{
  print("Start consumer: " + to_string(number));

  sem_wait(&numbers_consumed_lock);
  while (numbers_consumed < TOTAL)
  {
    numbers_consumed++;
    sem_post(&numbers_consumed_lock);
    int success = 0;
    int r = 0;
    {
      sem_wait(&buffer_available_elements);
      sem_wait(&buffer_lock);
      print_number_elements("Consumer: " + to_string(number));
      for (size_t i = 0; i < 16; ++i)
      {
        if (buffer[i] != 0)
        {
          r = buffer[i];
          buffer[i] = 0;
          success = 1;
          break;
        }
      }
      sem_post(&buffer_lock);
      if (success == 0)
        exit(printf("ERRRRRORRRR!!!!!\n"));
      sem_post(&buffer_free_elements);
    }

//    print(to_string(r));

    sem_wait(&numbers_consumed_lock);
  }
  sem_post(&numbers_consumed_lock);
}

bool Assignment3::checkOutput()
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
//    line_output << "Expected: " << std::setw(6) << expected_value << "\t\t";
    line_output << "Actual: " << std::setw(6) << output_line;

//    if(expected_value != actual_value)
//    {
//      line_output << "\t\tERROR";
//      return_value = false;
//    }

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

string Assignment3::name()
{
  return "Assignment3";
}

void Assignment3::print_number_elements(string name)
{
  int sval_available_elements = 0;
  int sval_free_elements = 0;
  sem_getvalue(&buffer_available_elements, &sval_available_elements);
  sem_getvalue(&buffer_free_elements, &sval_free_elements);
  print(name + " free_elements: " + to_string(sval_free_elements) + " available_elements: " + to_string(sval_available_elements));
}
