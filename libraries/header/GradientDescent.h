//
// Created by testing on 10.07.22.
//

#ifndef RACECONDITIONTESTS_GRADIENTDESCENT_H
#define RACECONDITIONTESTS_GRADIENTDESCENT_H

#include "iostream"

using namespace std;

enum Position_Move_Direction
{
    Top,
    Right,
    Bottom,
    Left
};

typedef struct POSITION_
{
    POSITION_() : x(0.0), y(0.0), move_speed(1.0) {}
    POSITION_(long double x, long double y, long double move_speed) : x(x), y(y), move_speed(move_speed) {};

    long double x;
    long double y;
    long double move_speed;
    long double value;
    long double gradient;

    void setPosition(POSITION_ position, Position_Move_Direction direction, long double new_movement_speed)
    {
      x = position.x;
      y = position.y;
      move_speed = new_movement_speed;

      switch (direction)
      {
        case Top:
          x += move_speed;
          break;
        case Right:
          y += move_speed;
          break;
        case Bottom:
          x -= move_speed;
          break;
        case Left:
          y -= move_speed;
          break;
      }
    }

    const string toString()
    {
      return "X: " + to_string(x) + " y: " + to_string(y) + " val: " + to_string(value);
    }
} Position;


class GradientDescent
{
public:
    GradientDescent(size_t max_number_of_steps_) :
                        max_number_of_steps_(max_number_of_steps_),
                        number_of_steps_(0),
                        position(Position()) {};

    long double terrainFunction(Position& position);

    void findPosition();

    void printPosition();

    size_t number_of_steps_;
    Position position;
    size_t max_number_of_steps_;
};


#endif //RACECONDITIONTESTS_GRADIENTDESCENT_H
