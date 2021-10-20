#pragma once
#include <iostream>
#include "DrawAPI.h"
class Brick
{
public:
    Brick(){}
    virtual void draw() = 0;
    virtual std::string getBrickName() = 0;
};