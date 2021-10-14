#pragma once
#include <vector>
#include "Brick.h"

class Factory
{
public:
    virtual std::vector<Brick*> getBricks(int t_numOfBricks, DrawAPI* t_drawApi) = 0;
};