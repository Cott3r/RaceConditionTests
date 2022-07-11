//
// Created by testing on 10.07.22.
//

#ifndef RACECONDITIONTESTS_GRADIENTDESCENT_H
#define RACECONDITIONTESTS_GRADIENTDESCENT_H

#include <complex>
#include <utility>
#include <vector>
#include "iostream"
#include "pthread.h"

using namespace std;

//template <typename T>
class GradientDescentDimension
{
public:
    GradientDescentDimension(string name, long double initial_position): name_(name), position_(initial_position) {};
    GradientDescentDimension(GradientDescentDimension& org): name_(org.name_), position_(org.position_) {};
    ~GradientDescentDimension() {};

    string name_;
    long double position_;
};


class GradientDescentPosition
{
public:
    GradientDescentPosition() : dimensions_(), move_speed_(1.0), value_(0.0) {}
    GradientDescentPosition(GradientDescentPosition& org) : dimensions_(), move_speed_(org.move_speed_), value_(org.value_)
    {
      for(auto org_dimension : org.dimensions_)
        dimensions_.push_back(new GradientDescentDimension(*org_dimension));
    }

    GradientDescentPosition& operator=(GradientDescentPosition& org)
    {
      move_speed_ = org.move_speed_;
      value_ = org.value_;

      dimensions_.clear();
      for(auto org_dimension : org.dimensions_)
        dimensions_.push_back(new GradientDescentDimension(*org_dimension));

      return *this;
    }

    ~GradientDescentPosition()
    {
      for(auto org_dimension : dimensions_)
        delete org_dimension;
    }


    vector<GradientDescentDimension*> dimensions_;
//    long double x;
//    long double y;
    long double move_speed_;
    long double value_;

    int dimension_move_directions()
    {
      return dimensions_.size() * 2;
    }

    void setPositionAndMove(GradientDescentPosition& position, size_t direction, long double new_movement_speed)
    {
      //Position Must have the same dimension
      if(this->dimensions_.size() != position.dimensions_.size())
        exit(10);


      move_speed_ = new_movement_speed;

      //Copy the position of the position
      for(size_t dim_nr = 0; dim_nr < this->dimensions_.size(); dim_nr++)
        this->dimensions_[dim_nr]->position_ = position.dimensions_[dim_nr]->position_;


      //Move in the direction with the used speed
      auto& dimension_this = this->dimensions_[direction / 2];

      if(direction % 2)
        dimension_this->position_ += move_speed_;
      else
        dimension_this->position_ -= move_speed_;
    }

    const string toString()
    {
      string return_string = "";

      for(auto dimension : dimensions_)
        return_string += dimension->name_ + ": " + to_string(dimension->position_) + " ";

      return return_string;
    }

    void addDimension(GradientDescentDimension* dimension)
    {
      dimensions_.push_back(dimension);
    }

    const string direction_toString(size_t direction)
    {
      if(direction == -1ULL)
        return "";

      string return_string;
      auto& dimension_direction = this->dimensions_[direction / 2];

      return_string += dimension_direction->name_ + " ";
      if(direction % 2)
        return_string += "Positive";
      else
        return_string += "Negative";

      return return_string;
    }
};


class GradientDescent
{
public:
    GradientDescent(GradientDescentPosition& position, size_t max_number_of_steps) :
            initial_position_(position)
    {
      max_number_of_steps_ = max_number_of_steps;
    };

    std::complex<long double> zeta(const std::complex<long double>& s);

    static long double terrainFunction(GradientDescentPosition& position);
    long double terrainFunctionZeta(GradientDescentPosition& position);

    static void findPosition(GradientDescentPosition* position_ptr);

    static void printPosition(size_t number_of_steps, GradientDescentPosition position_);

    void findMultiplePositions();

    GradientDescentPosition initial_position_;
    inline static size_t max_number_of_steps_;
};


#endif //RACECONDITIONTESTS_GRADIENTDESCENT_H
