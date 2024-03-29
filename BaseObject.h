#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "SDL_Utils.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x,const int& y){rect.x=x,rect.y=y;}
    SDL_Rect getRect() const{return rect;}
    virtual bool LoadImg(std::string path,SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer,const SDL_Rect* clip = NULL);
    void free();
    SDL_Texture* getTexture(){return newTexture;}
protected:
    SDL_Texture* newTexture;
    SDL_Rect rect;
};


#endif // BASEOBJECT_H_INCLUDED
