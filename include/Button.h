#pragma once

#include <SDL.h>
#include "Command.h"
#include <iostream>
#include <functional>

class Game;

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
        if(X > background.x && X < background.x + background.w && Y > background.y && Y < background.y + background.h)
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

    void UndoClick()
    {
        m_command->undo();
    }

    void RedoClick()
    {
        m_command->redo();
    }

    virtual void click(MacroCommand* macro)
    {
        macro->add(m_command);
        if(m_command)
            m_command->execute();
    }
};


class ButtonCommand : public Button
{
public:
    ButtonCommand(float t_posX, float t_posY, SDL_Renderer* t_sdl_renderer, Command* t_command, std::string t_btnName) :
        Button(t_posX, t_posY, t_sdl_renderer, t_command, t_btnName)
    {
       
    }

    void addFunc(std::function<void(Game*)> t_func, Game* t_caller)
    {
        m_caller = t_caller;
        m_func = t_func;
    }

    void removeCommand(bool t_removeCommand)
    {
        std::cout << "Remove command" << std::endl;
        m_removeCommand = t_removeCommand;
    }

    virtual void click(MacroCommand* t_macro)override
    {
        if (m_caller == nullptr && m_func == nullptr)
        {
            if (m_removeCommand)
                t_macro->remove();
            else
                t_macro->undo();
        }
        else
        {
            m_func(m_caller);
        }
    }
private:
    bool m_removeCommand;
    std::function<void(Game*)> m_func;
    Game* m_caller;
};
