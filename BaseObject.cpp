#include "BaseObject.h"
#include "SDL_Utils.h"
#include <SDL_image.h>
#include <SDL.h>

BaseObject::BaseObject(){
    newTexture = NULL;
    rect.x=0;
    rect.y=0;
    rect.w=0;
    rect.h=0;
}

BaseObject::~BaseObject()
{
    free();
}

bool BaseObject::LoadImg(std::string path,SDL_Renderer* renderer){
    free();
    SDL_Texture* gTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else {
        SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        gTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( gTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        else{
            rect.w=loadedSurface->w;
            rect.h=loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    newTexture = gTexture;
    return newTexture != NULL;

}
void BaseObject::render(SDL_Renderer* renderer,const SDL_Rect* clip){
    SDL_Rect renderquad = {rect.x,rect.y,rect.w,rect.h};
    SDL_RenderCopy(renderer,newTexture,clip,&renderquad);
}

void BaseObject::free(){
    if(newTexture != NULL){
        SDL_DestroyTexture(newTexture);
        newTexture = NULL;
        rect.w=0;
        rect.h=0;
    }
}
