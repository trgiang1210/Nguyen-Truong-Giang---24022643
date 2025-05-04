#include "Game.h"
#include "Texture.h"


using namespace std;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            cout << "Hunting Snake start !!!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (TTF_Init() == -1) {
            cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
            isRunning = false;
        }

        font = TTF_OpenFont("Schluber.ttf", 40);

        isRunning = true;
    }
    else {
        isRunning = false;
    }

    srand(time(0));

    mapSnake = Texture::LoadTexture("map3.png");

    headUpTex = Texture::LoadTexture("snakeup.png");
    headDownTex = Texture::LoadTexture("snakedown.png");
    headLeftTex = Texture::LoadTexture("snakeleft.png");
    headRightTex= Texture::LoadTexture("snakeright.png");
    appleTex = Texture::LoadTexture("apple.png");
    bodyTex = Texture::LoadTexture("bodySnake.png");

    menuGame = Texture::LoadTexture("menu1.png");

    headSnakeTex = headRightTex;

    snakePos = {10, 10};
    headSnakeRect = { snakePos.x * 32, snakePos.y * 32, 32, 32 };

    spawnApple();

    snakeBody.push_back(headSnakeRect);

}

void Game::spawnApple() {
    int cols = 1440 / 32;
    int rows = 960 / 32;
    const int menuHeight = 128;

    bool applePosition = false;
    int randomX, randomY;

    while (!applePosition) {
        randomX = rand() % cols;
        randomY = rand() % rows;

        applePosition = true;

        if(randomY * 32 <= menuHeight){
            applePosition = false;
            continue;
        }

        for (size_t i=0; i < snakeBody.size(); i++) {
            if ((randomX * 32 == snakeBody[i].x && randomY * 32 == snakeBody[i].y) ) {
                applePosition = false;
                break;
            }
        }
    }

    appleRect = { randomX * 32, randomY * 32, 32, 32 };
}

void Game::handleEvent(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    if (dir != RIGHT){
                        dir = LEFT;
                        headSnakeTex = headLeftTex;
                        }
                    break;
                case SDLK_RIGHT:
                    if (dir != LEFT){
                        dir = RIGHT;
                        headSnakeTex = headRightTex;
                        }
                    break;
                case SDLK_UP:
                    if (dir != DOWN ){
                        dir = UP;
                        headSnakeTex = headUpTex;
                    }
                    break;
                case SDLK_DOWN:
                    if (dir != UP){
                        dir = DOWN;
                        headSnakeTex = headDownTex;
                    }
                    break;
            }
        }
    }
}

void Game::menu() {
    bool startMenu = true;
    SDL_Event event;

    SDL_Rect menuRect = {0, 0, 1440, 960};

    while (startMenu) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                startMenu = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        startMenu = false;
                        break;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuGame, NULL, &menuRect);
        SDL_RenderPresent(renderer);
    }
}



void Game::displayBoard(int score) {
    SDL_Rect fillRect = {0, 0, 1440, 128};
    SDL_SetRenderDrawColor(renderer, 61, 72, 73, 255);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_Color color = {255, 255, 255};
    int texW = 0, texH = 0;

    SDL_Surface* surface = TTF_RenderText_Solid(font, "Welcome to my Hunting Snake game!", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {450, 30, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, "Score:", color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrectTwo = {630, 75, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrectTwo);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    string scoreText = to_string(score);
    surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrectThree = {730, 75, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrectThree);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


void Game::clean() {

    SDL_DestroyTexture(mapSnake);

    SDL_DestroyTexture(headSnakeTex);
    SDL_DestroyTexture(headUpTex);
    SDL_DestroyTexture(headDownTex);
    SDL_DestroyTexture(headLeftTex);
    SDL_DestroyTexture(headRightTex);
    SDL_DestroyTexture(appleTex);
    SDL_DestroyTexture(bodyTex);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
