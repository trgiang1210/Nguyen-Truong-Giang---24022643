#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

const int SPEED = 1;

struct GridPos {
    int x, y;
};

class Game {
public:
    Game();
    ~Game();

    vector<SDL_Rect> snakeBody;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvent();
    void clean();
    bool running() { return isRunning; }
    void spawnApple();
    void displayBoard(int score);
    void menu();



    static SDL_Renderer* renderer;

protected:
    SDL_Window* window;
    bool isRunning;


    SDL_Texture* mapSnake;

    TTF_Font* font = nullptr;

    SDL_Texture* menuGame;

    SDL_Texture* bodyTex;
    SDL_Texture* headSnakeTex;
    SDL_Texture* headUpTex;
    SDL_Texture* headDownTex;
    SDL_Texture* headLeftTex;
    SDL_Texture* headRightTex;
    SDL_Texture* appleTex;

    SDL_Rect headSnakeRect;
    SDL_Rect appleRect;

    GridPos snakePos;

    Direction dir = RIGHT;

    Uint32 lastMove = 0;

};

#endif
