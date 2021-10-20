#pragma once
#include "Brick.h"
#include <iostream>

class LegoBrick  : public Brick
{
    DrawAPI* api;
public:
    LegoBrick(DrawAPI* t_api) : api(t_api)
    {

    }
    LegoBrick(){};

    void draw()
    {
        api->Draw();
    }

    std::string getBrickName()
    {
        return "Lego Brick";
    }
};