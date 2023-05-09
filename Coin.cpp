#include "Coin.h"
#include "BaseObject.h"

Coin::Coin()
{
    wframe=0;
    hframe=0;
    frame=0;
    check=0;
}
Coin::~Coin()
{

}

bool Coin::LoadImg(std::string path,SDL_Renderer* renderer)
{
    bool ret = BaseObject::LoadImg(path,renderer);
    if(ret)
    {
        wframe = rect.w/COIN_FRAME_NUMBER;
        hframe = rect.h;

    }
}

void Coin::setClip()
{
    if(wframe >0 && hframe>0)
    {
        frameClip[0].x=0;
        frameClip[0].y=0;
        frameClip[0].w=wframe;
        frameClip[0].h=hframe;

        frameClip[1].x=wframe;
        frameClip[1].y=0;
        frameClip[1].w=wframe;
        frameClip[1].h=hframe;

        frameClip[2].x=2*wframe;
        frameClip[2].y=0;
        frameClip[2].w=wframe;
        frameClip[2].h=hframe;


    }
}

void Coin::Show(SDL_Renderer* renderer,int x_pos,int y_pos)
{
        check++;
        if(check%2==0) frame++;
        if(frame >= 3) frame = 0;
        SDL_Rect* currentClip = &frameClip[frame];
        SDL_Rect renderQuad = {x_pos,y_pos,wframe,hframe};
        SDL_RenderCopy(renderer,newTexture,currentClip,&renderQuad);
}






