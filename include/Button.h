#pragma once

#include <SDL.h>
#include "Command.h"
#include <iostream>

class Button
{
private:
    Command* m_command;
    float m_posX;
    float m_posY;
    float m_width = 100;
    float m_height = 100;
    SDL_Rect background;
    SDL_Renderer* m_renderer; 
    std::string m_buttonName;

public:
    Button(float t_posX, float t_posY, SDL_Renderer* t_sdl_renderer, Command* t_command, std::string t_btnName)
    {
        m_posX = t_posX;
        m_posY = t_posY;

        background.x = m_posX;
        background.y = m_posY;
        background.h = m_height;
        background.w = m_width;
        m_renderer = t_sdl_renderer;
        AssignCommand(t_command);
        m_buttonName = t_btnName;
    }

    ~Button();

    void AssignCommand(Command* command)
    {
        m_command = command;
    }

    bool ButtonPress(float X, float Y)
    {
        if(X > background.x && X < background.x + background.w && Y > background.y && Y < background.x + background.h)
        {
            return true;
        }
        return false;
    }

    void ButtonClick()
    {
        m_command->execute();
    }

    void Draw()
    {
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(m_renderer, &background);
    }
};
