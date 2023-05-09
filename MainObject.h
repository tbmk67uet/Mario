#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "SDL_Utils.h"
#include "BaseObject.h"
#include <vector>

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 20
#define PLAYER_JUMP_VAL 30
#define PLAYER_SPEED 6
#define BLANK_TILE 0

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();
    enum WalkType
    {
        WALK_NONE=0,
        WALK_RIGHT=1,
        WALK_LEFT=2
    };
    bool LoadImg(std::string path,SDL_Renderer* renderer);
    void HandleInput(SDL_Event e,SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);
    void setclips();
    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    bool CheckToBlocks(Map& map_data);
    void SetMapXY(const int mapx,const int mapy){map_x = mapx;map_y = mapy;}
    void CenterEntityOnMap(Map& map_data);
    void updateImagePlayer(SDL_Renderer* renderer);
    int makeX() const {return pos1;}
    int makeY() const {return pos2;}
    float getXpos() const {return x_pos;}
    float getYpos() const {return y_pos;}
    float getXval() const {return x_val;}
    float getYval() const {return y_val;}
    void setYval(const float& yVal){y_val = yVal;}
    void setXval(const float& xVal){x_val = xVal;}
    void setYpos(const float& yPos){y_pos = yPos;}
    void setXpos(const float& xPos){x_pos = xPos;}


private:
    int pos1;
    int pos2;
    float x_val;
    float y_val;
    float x_pos;
    float y_pos;
    int wframe;
    int hframe;

    SDL_Rect frameClip[7];
    Input input_type;
    int frame;
    int status;
    bool onGround=false;
    int map_x;
    int map_y;

    int check;
    int come_back_time;
};


#endif // MAINOBJECT_H_INCLUDED
