#include <iostream>
#include "../include/Game.h"
#include <SDL.h>
#include <iostream>

#include "../include/ClayBrickFactory.h"
#include "../include/LegoBrickFactory.h"
#include "../include/WoodBrickFactory.h"
#include "../include/DrawImpl.h"

void drawBricks(std::vector<Brick*> bricks)
{
    for(Brick* brick: bricks)
    {
        brick->draw();
    }
}

void createBricks()
{
    Factory* clayFactory = new ClayBrickFactory();
    std::vector<Brick*>cBricks = clayFactory->getBricks(2, new DrawImpl("Clay"));
    drawBricks(cBricks);
    Factory* legoFactory = new LegoBrickFactory();
    std::vector<Brick*>lBricks = legoFactory->getBricks(2, new DrawImpl("Lego"));
    drawBricks(lBricks);
    Factory* woodFactory = new WoodBrickFactory();
    std::vector<Brick*>wBricks = woodFactory->getBricks(2, new DrawImpl("Wood"));
    drawBricks(wBricks);

}

int main(int argc, char** argv)
{
    //createBricks();

    Game* game = new Game();
    game->init("yes", 150,250,800,600, SDL_WINDOW_INPUT_FOCUS);
    bool test = true;
    while(game->IsRunning())
    {
        game->HandleEvents();
        game->Update();
        game->Render();
    }
    game->CleanUp();

    return 0;
}