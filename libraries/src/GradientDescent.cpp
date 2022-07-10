//
// Created by testing on 10.07.22.
//

#include <iomanip>
#include "GradientDescent.h"

#define NUMBER_OF_POSITIONS (11)

void GradientDescent::findPosition()
{
  Position new_position = position;
  Position position_top[NUMBER_OF_POSITIONS];
  Position position_right[NUMBER_OF_POSITIONS];
  Position position_bottom[NUMBER_OF_POSITIONS];
  Position position_left[NUMBER_OF_POSITIONS];

  bool changed_position = true;
  Position_Move_Direction used_direction = Top;
  int starting_exponent = 0;
  int exponent = 0;
  int used_exponent = 0;
  long double speed = 0.0;
  long double used_Speed = 0.0;

  //Get an initial value for the starting position so that we can compare
  terrainFunction(position);

  while(++number_of_steps_ <= max_number_of_steps_ && changed_position)
  {
    //Use NewPosition to check the differences so that we still have the old position
    new_position = position;
    changed_position = false;

    //Try all directions
    for (size_t i = 0; i < NUMBER_OF_POSITIONS; ++i)
    {
      exponent = starting_exponent + (i - (NUMBER_OF_POSITIONS / 2));
      if(exponent >= 0)
        speed = (long double)(1ULL << exponent);
      else
        speed = (long double)1.0 / ((long double)(1ULL << -exponent));
//      cout << exponent << "  " << speed << endl;

      position_top[i].setPosition(position, Top, speed);
      terrainFunction(position_top[i]);
      //    position_top.gradient = (position.value - position_top.value) / (position.x - position_top.x);

      position_right[i].setPosition(position, Right, speed);
      terrainFunction(position_right[i]);

      position_bottom[i].setPosition(position, Bottom, speed);
      terrainFunction(position_bottom[i]);

      position_left[i].setPosition(position, Left, speed);
      terrainFunction(position_left[i]);

      //Check all the values of the directions
      if(position_top[i].value <= new_position.value) {new_position = position_top[i]; changed_position = true; used_direction = Top; used_Speed = speed; used_exponent = exponent;}
      if(position_right[i].value <= new_position.value) {new_position = position_right[i]; changed_position = true; used_direction = Right; used_Speed = speed; used_exponent = exponent;}
      if(position_bottom[i].value <= new_position.value) {new_position = position_bottom[i]; changed_position = true; used_direction = Bottom; used_Speed = speed; used_exponent = exponent;}
      if(position_left[i].value <= new_position.value) {new_position = position_left[i]; changed_position = true; used_direction = Left; used_Speed = speed; used_exponent = exponent;}
    }



    //Update the position
    position = new_position;
    starting_exponent = used_exponent;

    //Print the position
    cout << "Position: " << position.toString();
    cout << "\tUsed direction: " << (used_direction == Top ? "Top" : "") << (used_direction == Right ? "Right" : "") << (used_direction == Bottom ? "Bottom" : "") << (used_direction == Left ? "Left" : "");
    cout << "\tUsed Speed: " << used_Speed << "\tUsed Exponent: " << used_exponent << endl;


  }


  this->printPosition();
  cout << std::setprecision(20) << "Number of Steps: " << number_of_steps_ << " ; Position: x: " << position.x << " y: " << position.y << endl;
}

void GradientDescent::printPosition()
{
  cout << "Number of Steps: " << to_string(number_of_steps_) << " ; Position: x: " << to_string(position.x) << " y: " << to_string(position.y) << endl;
}

long double GradientDescent::terrainFunction(Position& position)
{
  long double x_offset = 10.0 + 1.0 / 4.0;
  long double y_offset = 1000000;

  long double x = position.x + x_offset;
  long double y = position.y + y_offset;

  position.value = x * x + y * y;

  return position.value;
}
