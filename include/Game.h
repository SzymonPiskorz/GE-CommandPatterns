#pragma once
#include <iostream>
#include <SDL.h>
#include "Button.h"
#include "Command.h"

class Game
{
public:

    void init(std::string t_windowName, int t_x, int t_y, 
    int t_width, int t_height, Uint32 t_flags);

    bool IsRunning();
    void HandleEvents();
    void Update();
    void Render();
    void CleanUp();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool gameRunning = true;

    std::vector<Button*> buttons;

    MacroCommand* m_macros;
};