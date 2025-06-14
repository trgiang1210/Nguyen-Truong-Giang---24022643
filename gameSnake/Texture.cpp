#include "Texture.h"
#include "Game.h"

SDL_Texture* Texture::LoadTexture(const char* texture){

    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;

}

