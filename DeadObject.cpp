#include "DeadObject.h"

DeadObject::DeadObject()
{
    wframe = 0;
    hframe = 0;
    x_pos = 0.0;
    y_pos = 0.0;
    x_val = 0.0;
    y_val = 0.0;

}

DeadObject::~DeadObject()
{

}

bool DeadObject::LoadImg(std::string path,SDL_Renderer* renderer)
{
    bool ret = BaseObject::LoadImg(path,renderer);
    if(ret)
    {
        wframe = rect.w/7;
        hframe = rect.h;
    }
    return ret;
}

void DeadObject::Show(SDL_Renderer* renderer)
{
    rect.x=x_pos;
    rect.y=y_pos;
    SDL_Rect* currentClip = &frameClip[frame];
    SDL_Rect renderQuad = {rect.x,rect.y,wframe,hframe};
    SDL_RenderCopy(renderer,newTexture,currentClip,&renderQuad);
}


