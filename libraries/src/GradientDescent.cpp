//
// Created by testing on 10.07.22.
//

#include <iomanip>
#include "GradientDescent.h"
#include <cmath>
#include <iostream>
#include <complex>
//#include <numbers>

#define NUMBER_OF_SPEEDS (11)

void GradientDescent::findPosition(GradientDescentPosition* position_ptr)
{
  GradientDescentPosition& position = *position_ptr;
  GradientDescentPosition new_position = position;
  GradientDescentPosition positions[position.dimension_move_directions()][NUMBER_OF_SPEEDS];

  size_t number_of_steps = 0;
  bool changed_position = true;
  size_t used_direction = -1ULL;
  int starting_exponent = 0;
  int exponent = 0;
  int used_exponent = 0;
  long double speed = 0.0;
  long double used_Speed = 0.0;

  //Get an initial value for the starting position so that we can compare
  terrainFunction(position);
//  printPosition(number_of_steps, position);

  //Init all possible positions
  for (size_t speeds = 0; speeds < NUMBER_OF_SPEEDS; ++speeds)
    for (size_t direction = 0; direction < position.dimension_move_directions() ; direction++)
      positions[direction][speeds] = position;



  //Run the gradient descent
  while(++number_of_steps <= max_number_of_steps_ && changed_position)
  {
    //Use NewPosition to check the differences so that we still have the old position
    new_position = position;
    changed_position = false;
    used_direction = -1ULL;
    used_Speed = 0.0;
    used_exponent = 0;

    //Try different speeds
    for (size_t speeds = 0; speeds < NUMBER_OF_SPEEDS; ++speeds)
    {
      exponent = starting_exponent + (speeds - (NUMBER_OF_SPEEDS / 2)) * 1;
      if(exponent >= 0)
        speed = (long double)(1ULL << exponent);
      else
        speed = (long double)1.0 / ((long double)(1ULL << -exponent));

      //Try all directions
      for (size_t direction = 0; direction < position.dimension_move_directions() ; direction++)
      {
        positions[direction][speeds].setPositionAndMove(position, direction, speed);
//        terrainFunctionZeta(positions[direction][speeds]);
        terrainFunction(positions[direction][speeds]);

        if(
//           positions[direction][speeds].x >= 0 && positions[direction][speeds].x <= 1.0 && //Only find root of the zeta function in the critical region
           positions[direction][speeds].value_ < new_position.value_)
        {
          new_position = positions[direction][speeds];
          changed_position = true;
          used_direction = direction;
          used_Speed = speed;
          used_exponent = exponent;
        }
      }
    }


    //Update the position
    position = new_position;
    starting_exponent = used_exponent;

    //Print the position
//    cout << "GradientDescentPosition: " << position.toString();
//    cout << "\tUsed direction: " << position.direction_toString(used_direction);
//    cout << "\t\tUsed Speed: " << used_Speed << "\tUsed Exponent: " << used_exponent << endl;
  }


  printPosition(number_of_steps, position);
  delete position_ptr;
}

void GradientDescent::printPosition(size_t number_of_steps, GradientDescentPosition position)
{
  cout << "Number of Steps: " << to_string(number_of_steps) << " ; GradientDescentPosition: " << position.toString() << endl;
}


//*********************
//Implementation from StackOverflow
//https://stackoverflow.com/questions/41549533/riemann-zeta-function-with-complex-argument
//Start
const long double LOWER_THRESHOLD = 1.0e-15;
const long double UPPER_BOUND = 1.0e+4;
const int MAXNUM = 1000;

std::complex<long double> GradientDescent::zeta(const std::complex<long double>& s)
{
  std::complex<long double> a_arr[MAXNUM + 1];
  std::complex<long double> half(0.5, 0.0);
  std::complex<long double> one(1.0, 0.0);
  std::complex<long double> two(2.0, 0.0);
  std::complex<long double> rev(-1.0, 0.0);
  std::complex<long double> sum(0.0, 0.0);
  std::complex<long double> prev(1.0e+20, 0.0);

  a_arr[0] = half / (one - std::pow(two, (one - s))); //initialize with a_0 = 0.5 / (1 - 2^(1-s))
  sum += a_arr[0];

  for (int n = 1; n <= MAXNUM; n++)
  {
    std::complex<long double> nCplx(n, 0.0); //complex index

    for (int k = 0; k < n; k++)
    {
      std::complex<long double> kCplx(k, 0.0); //complex index

      a_arr[k] *= half * (nCplx / (nCplx - kCplx));
      sum += a_arr[k];
    }

    a_arr[n] = (rev * a_arr[n - 1] * std::pow((nCplx / (nCplx + one)), s) / nCplx);
    sum += a_arr[n];


    if (std::abs(prev - sum) < LOWER_THRESHOLD)//If the difference is less than or equal to the threshold value, it is considered to be convergent and the calculation is terminated.
      break;

    if (std::abs(sum) > UPPER_BOUND)//doesn't work for large values, so it gets terminated when it exceeds UPPER_BOUND
      break;

    prev = sum;
  }

  return sum;
}
//End


long double GradientDescent::terrainFunction(GradientDescentPosition& position)
{
  long double x_offset = -100.0 + 1.0 / 4.0;
  long double y_offset = 123456789;
  long double z_offset = 10.0;
//  x_offset = 0;
//  y_offset = 0;

  long double x = position.dimensions_[0]->position_ + x_offset;
  long double y = position.dimensions_[1]->position_ + y_offset;
  long double z = position.dimensions_[2]->position_ + z_offset;

  position.value_ = x*x + y*y + z*z;
  return position.value_;

  position.value_ = 657.5 * pow(x,4.0) + 19.07 * pow(x,3.0) + 1.3275 * pow(x,2.0) + 27.0 * x + 2.650 +
                   357.7 * pow(y,4.0) + 171.30 * pow(y,3.0) + 82.7 * pow(y,2.0) + 3873.0 * y + 1.0 +
                   18.0 * pow(x,4.0)*pow(y,4.0) + 9782.230 * pow(x,3.0)*pow(y,3.0) + 217.0 * pow(x,2.0)*pow(y,2.0) + 328.220 * x*y;

  position.value_ += z*z * 100;

  return position.value_;
}

long double GradientDescent::terrainFunctionZeta(GradientDescentPosition &position)
{
  std::complex<long double> complex_position (position.dimensions_[0]->position_, position.dimensions_[1]->position_);
  std::complex<long double> zeta_result = zeta(complex_position);
  position.value_ = abs(zeta_result);

  return position.value_;
}

void GradientDescent::findMultiplePositions()
{
  size_t number_of_threads = 10;
  pthread_t tid[number_of_threads];



  for (size_t i = 0; i < number_of_threads; ++i)
  {
    auto new_position = new GradientDescentPosition(initial_position_);
    for (int dimension_number = 0; dimension_number < new_position->dimensions_.size(); ++dimension_number)
      new_position->dimensions_[dimension_number]->position_ = (double)rand()/(double)rand()*(double)rand();


    pthread_create(&tid[i], 0, (void *(*)(void *)) this->findPosition,(void *) new_position);
  }

  for (size_t i = 0; i < number_of_threads; ++i)
    pthread_join(tid[i], 0);
}