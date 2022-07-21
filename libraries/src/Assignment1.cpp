//
// Created by testing on 21.07.22.
//

#include "Assignment1.h"

//This method 'execute' is called by multiple Threads

//***Parameters***
//Each Thread has a unique ascending number and this number is passed to this method as the parameter 'number'

//***GOAL***
//The goal is that the 'print' is called in ascending order

void Assignment1::execute(size_t number)
{
  print(to_string(number));
}

string Assignment1::name()
{
  return "Assignment1";
}

bool Assignment1::checkOutput()
{
  char output_line[1000] = {0};
  size_t expected_number = 0;
  size_t actual_number;
  bool return_value = true;

  //Go through all lines in asc order
  pthread_mutex_lock(&output_string_lock_);
  output_string_.getline(output_line, sizeof(output_line));
  while(output_line[0] != 0)
  {
    sscanf(output_line, "%lu", &actual_number);

    stringstream line_output;
    line_output << "Expected: " << std::setw(6) << expected_number << "\t\t";
    line_output << "Actual: " << std::setw(6) << output_line;

    if(expected_number != actual_number)
    {
      line_output << "\t\tERROR";
      return_value = false;
    }

    ThreadHelper::printLine(line_output.str());

    expected_number++;
    output_string_.getline(output_line, sizeof(output_line));
  }
  pthread_mutex_unlock(&output_string_lock_);

  return return_value;
}