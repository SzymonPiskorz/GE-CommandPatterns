#pragma once
#include "Brick.h"
#include <iostream>

class ClayBrick : public Brick
{
    DrawAPI* api;
public: 
    ClayBrick(DrawAPI* t_api) : api(t_api)
    {

    }
    ClayBrick(){};
    
    void draw()
    {
        api->Draw();
    }

    std::string getBrickName()
    {
        return "Clay Brick";
    }
};