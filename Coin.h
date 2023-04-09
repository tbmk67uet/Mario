#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "SDL_Utils.h"
#include "BaseObject.h"
#include "GameMap.h"

#define COIN_FRAME_NUMBER 3
#define MAX_JUMP_SPEED 3
#define JUMP_VAL 1

class Coin : public BaseObject
{
public:
    Coin();
    ~Coin();
    void setClip();
    virtual bool LoadImg(std::string path,SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer,int x_pos,int y_pos);
private:
    SDL_Rect frameClip[COIN_FRAME_NUMBER];
    int wframe;
    int hframe;
    int frame;
};




#endif // COIN_H_INCLUDED
