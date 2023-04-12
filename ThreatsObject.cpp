#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    alive = true;
    wframe=0;
    hframe=0;
    x_val=0.0;
    y_val=0.0;
    x_pos=0.0;
    y_pos=0.0;
    onGround=0;
    come_back_time=0;
    frame=0;
    map_x=0;
    map_y=0;
    animationA=0;
    animationB=0;
    input_type.left=1;
    type_move = STATIC_THREAT;
}
ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadImg(std::string path,SDL_Renderer* renderer)
{
    bool ret = BaseObject::LoadImg(path,renderer);
    if(ret)
    {
        wframe = rect.w/THREAT_FRAME_NUMBER;
        hframe = rect.h;

    }
}

void ThreatsObject::setClip()
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

        frameClip[3].x=3*wframe;
        frameClip[3].y=0;
        frameClip[3].w=wframe;
        frameClip[3].h=hframe;

        frameClip[4].x=4*wframe;
        frameClip[4].y=0;
        frameClip[4].w=wframe;
        frameClip[4].h=hframe;

        frameClip[5].x=5*wframe;
        frameClip[5].y=0;
        frameClip[5].w=wframe;
        frameClip[5].h=hframe;

        frameClip[6].x=6*wframe;
        frameClip[6].y=0;
        frameClip[6].w=wframe;
        frameClip[6].h=hframe;


    }
}


void ThreatsObject::Show(SDL_Renderer* renderer)
{
    if(come_back_time==0)
    {
        rect.x=x_pos-map_x;
        rect.y=y_pos-map_y;
        frame++;
        if(frame >= 7) frame = 0;
        SDL_Rect* currentClip = &frameClip[frame];
        SDL_Rect renderQuad = {rect.x,rect.y,wframe,hframe};
        SDL_RenderCopy(renderer,newTexture,currentClip,&renderQuad);
    }
}

void ThreatsObject::DoPlayer(Map& map_data)
{
    if(come_back_time == 0)
    {
        x_val = 0.0;
        y_val += THREAT_GRAVITY_SPEED;
        if(y_val >= THREAT_MAX_FALL_SPEED)
        {
            y_val = THREAT_MAX_FALL_SPEED;
        }

        if(input_type.left == 1)
        {
            x_val -= THREAT_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += THREAT_SPEED;
        }

        CheckToMap(map_data);
    }
    else if(come_back_time>0)
    {
        come_back_time--;
        if(come_back_time == 0)
        {
            x_val = 0;
            y_val = 0;
            y_pos = 0;
        }
    }
}

void ThreatsObject::CheckToMap(Map& map_data)
{
    int x1=0,x2=0;
    int y1=0,y2=0;

    //Kiem tra theo chieu ngang
    int height_min = hframe < TILE_SIZE ? hframe : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + wframe - 1)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    if(x1 >=0 && x2 < MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            int val1=map_data.tile[y1][x2];
            int val2=map_data.tile[y2][x2];
            if((val1  != BLANK_TILE && val1  < 10 && val1 != 7   ) || (val2 != BLANK_TILE && val2  < 10 && val2 != 7  ))
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= wframe +1;
                x_val = 0;

            }
            if(val1 == 7 || val2 == 7 || val1==9 || val2==9)
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= wframe +1;x_val=-THREAT_SPEED;
                input_type.right=0;
                input_type.left=1;

            }
        }
        else if(x_val <0)
        {
            int val1=map_data.tile[y1][x1];
            int val2=map_data.tile[y2][x1];
            if((val1 != BLANK_TILE && val1 < 10  && val1 != 7) || (val2 != BLANK_TILE && val2 < 10  && val2 != 7))
            {
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;

            }

            if(val1 == 8 || val2 == 8 || val1==9 || val2==9)
            {
                x_pos = (x1+1)*TILE_SIZE;x_val=THREAT_SPEED;
                input_type.left=0;
                input_type.right=1;

            }

        }
    }

    //kiem tra theo chieu doc
    int width_min = wframe < TILE_SIZE ? wframe : TILE_SIZE;
    x1 = x_pos/TILE_SIZE;
    x2 = (x_pos+width_min)/TILE_SIZE;

    y1=(y_pos + y_val)/TILE_SIZE;
    y2=(y_pos +y_val + hframe -1)/TILE_SIZE;
    if(x1 >=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(y_val > 0)
        {

            if((map_data.tile[y2][x1] != BLANK_TILE && map_data.tile[y2][x1] < 10) || (map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] < 10))
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= hframe +1;
                y_val = 0;

                onGround = true;
            }

        }
        else if(y_val < 0)
        {
            if((map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] < 10) || (map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] < 10))
            {
                y_pos = (y1+1)*TILE_SIZE;
                y_val = 0;

            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;
    if(x_pos < 0) x_pos =0;
    else if(x_pos + wframe > map_data.max_x)
    {
        x_pos = map_data.max_x - wframe - 1;
    }
    if(y_pos > map_data.max_y)
    {
        come_back_time = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* renderer)
{
    if(alive == false) {
        LoadImg("Image/goombas_die.png",renderer);
    }
    else{
    if(type_move == STATIC_THREAT)
    {
        ;//
    }
    else
    {
        if(onGround == true)
        {
            if(x_pos > animationB)
            {
                input_type.left=1;
                input_type.right=0;
                LoadImg("Image/goombas.png",renderer);
            }
            else if(x_pos < animationA)
            {
                input_type.left=0;
                input_type.right=1;
                LoadImg("Image/goombas.png",renderer);
            }
        }
        else
        {
            if(input_type.left == 1)
            {
                LoadImg("Image/goombas.png",renderer);
            }
            if(input_type.right == 1)
            {
                LoadImg("Image/goombas.png",renderer);
            }
        }
    }
    }
}


