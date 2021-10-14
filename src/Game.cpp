#include "../include/Game.h"

void Game::init(std::string t_windowName, int t_x, int t_y, int t_width, int t_height, Uint32 t_flags)
{
    window = SDL_CreateWindow(t_windowName.c_str(), t_x, t_y, t_width, t_height, t_flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Button* btn = new Button(50, 50, renderer, new BuildClayBrickCommand(), "clay make");
    buttons.push_back(btn);
}

 bool Game::IsRunning()
 {
     return gameRunning;
 }

void Game::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == 'w')
                {
                    std::cout << "w";
                    std::cout << std::endl;
                }
                else if (event.key.keysym.sym == 's')
                {
                    std::cout << "S";
                    std::cout << std::endl;
                }
            default:
                break;
        }
         int x,y;
        Uint32 mouseBtns;

        mouseBtns = SDL_GetMouseState(&x, &y);

        if((mouseBtns && SDL_BUTTON_LMASK) != 0)
        {
            for (Button* btn : buttons)
            {
                if(btn->ButtonPress(x, y))
                {
                    btn->ButtonClick();
                }
            }
        }
    }
}
    
void Game::Update()
{
    //std::cout << "Updating";
    //std::cout << std::endl;
}
    
void Game::Render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for (Button* btn : buttons)
    {
        btn->Draw();
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}
    
void Game::CleanUp()
{
    //std::cout << "Cleaning Up";
    //std::cout << std::endl;
    SDL_DestroyWindow(window);
}