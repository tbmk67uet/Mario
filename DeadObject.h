#ifndef DEADOBJECT_H_INCLUDED
#define DEADOBJECT_H_INCLUDED

#include "SDL_Utils.h"
#include "BaseObject.h"

#define THREAT_FRAME_NUMBER 7
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define BLANK_TILE 0
#define THREAT_SPEED 3

class DeadObject : public BaseObject
{
public:
    DeadObject();
    ~DeadObject();
    enum typeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_pos(const float& xp){x_pos=xp;}
    void set_y_pos(const float& yp){y_pos=yp;}

    float get_x_pos() const{return x_pos;}
    float get_y_pos() const{return y_pos;}

    void set_x_val(const float& xVal){x_val = xVal;}
    void set_y_val(const float& yVal){y_val = yVal;}



    bool LoadImg(std::string path,SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);


    void DoPlayer(Map& gMap);

    void setAlive(bool aLive){alive = aLive;}
    void setTypeMove(const int& typeMove){type_move = typeMove;}


    void ImpMoveType(SDL_Renderer* renderer);

private:

    int wframe;
    int hframe;

    float x_pos;
    float y_pos;
    float x_val;
    float y_val;

    int type_move;

    bool alive;
    Input input_type;
};

#endif // DEADOBJECT_H_INCLUDED
