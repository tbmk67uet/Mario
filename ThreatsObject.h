#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "SDL_Utils.h"
#include "BaseObject.h"

#define THREAT_FRAME_NUMBER 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define BLANK_TILE 0

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();
    void set_x_val(const float& xVal){x_val=xVal;}
    void set_y_val(const float& yVal){y_val=yVal;}
    void set_x_pos(const float& xp){x_val=xp;}
    void set_y_pos(const float& yp){y_val=yp;}
    float get_x_pos() const{return x_pos;}
    float get_y_pos() const{return y_pos;}
    void SetMapXY(const int& mpx,const int& mpy){map_x=mpx;map_y=mpy;}
    void setClip();
    bool LoadImg(std::string path,SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);
    int get_width_frame() const {return wframe;}
    int get_height_frame() const {return hframe;}
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);
private:
    SDL_Rect frameClip[THREAT_FRAME_NUMBER];
    int wframe;
    int hframe;
    int frame;
    bool onGround;
    float x_pos;
    float y_pos;
    float x_val;
    float y_val;
    int map_x;
    int map_y;
    int come_back_time;
};

#endif // THREATSOBJECT_H_INCLUDED
