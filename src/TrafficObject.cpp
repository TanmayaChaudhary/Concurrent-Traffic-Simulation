#include <algorithm>
#include <iostream>
#include <chrono>
#include "TrafficObject.h"

// init static variable
int TrafficObject::id_cnt_ = 0;

std::mutex TrafficObject::mtx_;

void TrafficObject::setPosition(double x, double y)
{
    posX_ = x;
    posY_ = y;
}

void TrafficObject::getPosition(double &x, double &y)
{
    x = posX_;
    y = posY_;
}

TrafficObject::TrafficObject()
{
    type_ = ObjectType::noObject;
    id_ = id_cnt_++;
}

TrafficObject::~TrafficObject()
{
  
    // set up thread barrier before this object is destroyed
    std::for_each(threads_.begin(), threads_.end(), [](std::thread &t) {
        t.join();
    });
}