#pragma once
#include "Factory.h"
#include "LegoBrick.h"

class LegoBrickFactory : public Factory
{
public:
    std::vector<Brick*> getBricks(int t_numOfBricks, DrawAPI* t_drawApi)
    {
        std::vector<Brick*> brickValues;

        for(int i = 0; i< t_numOfBricks; i++)
        {
            brickValues.push_back(new LegoBrick(t_drawApi));
        }

        return brickValues;
    }

    Brick* getBrick()
    {
        return new LegoBrick();
    }
};