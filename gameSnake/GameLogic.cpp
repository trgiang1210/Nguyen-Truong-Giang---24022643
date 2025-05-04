#include "GameLogic.h"
#include "Game.h"


void GameLogic::gameLogic() {
    Uint32 current = SDL_GetTicks();
    if (current - lastMove > 120) {
    switch (dir) {
        case LEFT:
            snakePos.x -= SPEED;
            break;
        case RIGHT:
            snakePos.x += SPEED;
            break;
        case UP:
            snakePos.y -= SPEED;
            break;
        case DOWN:
            snakePos.y += SPEED;
            break;
    }

    headSnakeRect.x = snakePos.x * 32;
    headSnakeRect.y = snakePos.y * 32;

    snakeBody.insert(snakeBody.begin(), headSnakeRect);

    if (headSnakeRect.x == appleRect.x && headSnakeRect.y == appleRect.y) {
        spawnApple();
    } else {
        snakeBody.pop_back();
    }

    if (snakePos.x < 0 || snakePos.x >= 1440 / 32 || snakePos.y < 128 / 32 || snakePos.y >= 960 / 32) {
        isRunning = false;
        cout << "Game Over !!!" << endl;
        return;
    }

    for(size_t i = 1; i <= snakeBody.size(); i++){
        if(snakeBody[0].x == snakeBody[i].x && snakeBody[0].y == snakeBody[i].y ){
            isRunning = false;
            cout << "Game over !!!" << endl ;
            return ;
        }
    }

    lastMove = current;
    }
}


void GameLogic::render() {

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, mapSnake, NULL, NULL);

    SDL_RenderCopy(renderer, appleTex, NULL, &appleRect);

    for (long long unsigned int i = 0; i < snakeBody.size(); ++i) {
        if (i == 0) {
            SDL_RenderCopy(renderer, headSnakeTex, NULL, &snakeBody[i]);
        }
        else {
            SDL_RenderCopy(renderer, bodyTex, NULL, &snakeBody[i]);
        }
    }

    displayBoard((int)((snakeBody.size() - 1) * 10));



    SDL_RenderPresent(renderer);
}
