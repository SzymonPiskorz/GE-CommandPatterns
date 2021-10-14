#pragma once

#include "DrawAPI.h"
#include <iostream>
#include <string>

class DrawImpl : public DrawAPI
{
    std::string typeOfBrick;
public:
    DrawImpl(std::string t_nameOfBrick) : typeOfBrick(t_nameOfBrick)
    {

    }

    void Draw() 
    { 
        std::cout << typeOfBrick << std::endl; 
    }
};