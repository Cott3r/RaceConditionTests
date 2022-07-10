//
// Created by testing on 10.07.22.
//

#ifndef RACECONDITIONTESTS_GRADIENTDESCENT_H
#define RACECONDITIONTESTS_GRADIENTDESCENT_H

#include <complex>
#include "iostream"

using namespace std;

enum Position_Move_Direction
{
    None,
    Top,
    Top_Right,
    Right,
    Bottom_Right,
    Bottom,
    Bottom_Left,
    Left,
    Top_Left,
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
          y += move_speed;
          break;
        case Top_Right:
          x += move_speed;
          y += move_speed;
          break;
        case Right:
          x += move_speed;
          break;
        case Bottom_Right:
          x += move_speed;
          y -= move_speed;
          break;
        case Bottom:
          y -= move_speed;
          break;
        case Bottom_Left:
          x -= move_speed;
          y -= move_speed;
          break;
        case Left:
          x -= move_speed;
          break;
        case Top_Left:
          x -= move_speed;
          y += move_speed;
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
    long double terrainFunctionZeta(Position& position);

    void findPosition();

    void printPosition();

    std::complex<long double> zeta(const std::complex<long double>& s);

    size_t number_of_steps_;
    Position position;
    size_t max_number_of_steps_;
};


#endif //RACECONDITIONTESTS_GRADIENTDESCENT_H
