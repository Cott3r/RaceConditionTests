//
// Created by testing on 10.07.22.
//

#include <iomanip>
#include "GradientDescent.h"
#include <cmath>
#include <iostream>
#include <complex>
//#include <numbers>

#define NUMBER_OF_POSITIONS (11)

void GradientDescent::findPosition()
{
  position.x = 0.5;
  position.y = -2e2;
  Position new_position = position;
  Position positions[8][NUMBER_OF_POSITIONS];

  bool changed_position = true;
  Position_Move_Direction used_direction = None;
  int starting_exponent = 0;
  int exponent = 0;
  int used_exponent = 0;
  long double speed = 0.0;
  long double used_Speed = 0.0;

  //Get an initial value for the starting position so that we can compare
  terrainFunction(position);
  cout << "Position: " << position.toString() << endl;

  while(++number_of_steps_ <= max_number_of_steps_ && changed_position)
  {
    //Use NewPosition to check the differences so that we still have the old position
    new_position = position;
    changed_position = false;
    used_direction = None;
    used_Speed = 0.0;
    used_exponent = 0;

    //Try different speeds
    for (size_t i = 0; i < NUMBER_OF_POSITIONS; ++i)
    {
      exponent = starting_exponent + (i - (NUMBER_OF_POSITIONS / 2)) * 2;
      if(exponent >= 0)
        speed = (long double)(1ULL << exponent);
      else
        speed = (long double)1.0 / ((long double)(1ULL << -exponent));

      //Try all directions
      for (Position_Move_Direction direction = Top; direction <= Top_Left ; direction = (Position_Move_Direction)((int)direction + 1))
      {
        positions[direction][i].setPosition(position, direction, speed);
//        terrainFunctionZeta(positions[direction][i]);
        terrainFunction(positions[direction][i]);

        if(
//           positions[direction][i].x >= 0 && positions[direction][i].x <= 1.0 && //Only find root of the zeta function in the critical region
           positions[direction][i].value < new_position.value)
        {
          new_position = positions[direction][i];
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
    cout << "Position: " << position.toString();
    cout << "\tUsed direction: " << (used_direction == Top ? "Top" : "") << (used_direction == Right ? "Right" : "") << (used_direction == Bottom ? "Bottom" : "") << (used_direction == Left ? "Left" : "")
                                 << (used_direction == Top_Right ? "Top_Right" : "") << (used_direction == Bottom_Right ? "Bottom_Right" : "") << (used_direction == Bottom_Left ? "Bottom_Left" : "") << (used_direction == Top_Left ? "Top_Left" : "");
    cout << "\t\tUsed Speed: " << used_Speed << "\tUsed Exponent: " << used_exponent << endl;
  }


  this->printPosition();
}

void GradientDescent::printPosition()
{
  cout << "Number of Steps: " << to_string(number_of_steps_) << " ; Position: x: " << to_string(position.x) << " y: " << to_string(position.y) << endl;
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


long double GradientDescent::terrainFunction(Position& position)
{
  long double x_offset = -100.0 + 1.0 / 4.0;
  long double y_offset = 123456789;
  x_offset = 0;
  y_offset = 0;

  long double x = position.x + x_offset;
  long double y = position.y + y_offset;

  position.value = 657.5 * pow(x,4.0) + 19.07 * pow(x,3.0) + 1.3275 * pow(x,2.0) + 27.0 * x + 2.650 +
                   357.7 * pow(y,4.0) + 171.30 * pow(y,3.0) + 82.7 * pow(y,2.0) + 3873.0 * y + 1.0 +
                   18.0 * pow(x,4.0)*pow(y,4.0) + 9782.230 * pow(x,3.0)*pow(y,3.0) + 217.0 * pow(x,2.0)*pow(y,2.0) + 328.220 * x*y;

  return position.value;
}

long double GradientDescent::terrainFunctionZeta(Position &position)
{
  std::complex<long double> complex_position (position.x, position.y);
  std::complex<long double> zeta_result = zeta(complex_position);
  position.value = abs(zeta_result);

  return position.value;
}