#pragma once
#include "Brick.h"
#include <iostream>

class WoodBrick  : public Brick
{
    DrawAPI* api;
public:
    WoodBrick(DrawAPI* t_api) : api(t_api)
    {

    }
    WoodBrick(){};

    void draw()
    {
        api->Draw();
    }

    std::string getBrickName()
    {
        return "Wood Brick";
    }
};