#include "Game.h"
#include "GameLogic.h"
#include <iostream>

GameLogic *game = nullptr;

const double FPS = 60;
const double frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

int main(int argc, char* argv[]){
    game = new GameLogic();

    game->init("Hunting Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 960, false);

    game->menu();


    while(game->running()){

        frameStart = SDL_GetTicks();

        game->handleEvent();
        game->gameLogic();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();

    return 0;
}
