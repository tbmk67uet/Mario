#include "MainObject.h"
#include "SDL_Utils.h"
#include "ImpTimer.h"
#include "Coin.h"
#include <vector>

MainObject::MainObject()
{
    pos1=0;
    pos2=0;
    frame = 0;
    x_pos=0;
    y_pos=0;
    x_val=0;
    y_val=0;
    wframe=0;
    hframe=0;
    status=WALK_NONE;
    input_type.left=0;
    input_type.right=0;
    input_type.jump=0;
    input_type.up=0;
    input_type.down=0;
    map_x=0;
    map_y=0;
    come_back_time = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path,SDL_Renderer* renderer)
{
   bool ret = BaseObject::LoadImg(path,renderer);
   if(ret == true)
   {
       wframe = rect.w/7;
       hframe = rect.h;
   }

   return ret;
}

void MainObject::setclips()
{
    if(wframe > 0 && hframe > 0)
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

void MainObject::Show(SDL_Renderer* renderer)
{
    updateImagePlayer(renderer);

    if(input_type.left == 1 || input_type.right==1) frame++;
    else frame=0;
    if(frame >= 7) frame = 0;
    if(come_back_time==0)
    {
    rect.x=x_pos - map_x;
    rect.y=y_pos - map_y;

    SDL_Rect* currentClip = &frameClip[frame];
    SDL_Rect renderQuad = {rect.x,rect.y,wframe,hframe};
    SDL_RenderCopy(renderer,newTexture,currentClip,&renderQuad);
    }

}

void MainObject::HandleInput(SDL_Event e,SDL_Renderer* renderer)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {
                status = WALK_RIGHT;
                input_type.right=1;
                input_type.left=0;
                updateImagePlayer(renderer);
            }
                break;
            case SDLK_LEFT:
            {
                status = WALK_LEFT;
                input_type.left=1;
                input_type.right=0;
                updateImagePlayer(renderer);
            }
                break;

        }
    }
    else if(e.type == SDL_KEYUP){
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {

                input_type.right=0;
            }
                break;
            case SDLK_LEFT:
            {

                input_type.left=0;
            }
                break;

        }
    }

    if(e.type == SDL_KEYDOWN)
    {

        if(e.key.keysym.sym == SDLK_UP)
        {
            input_type.jump=1;}

        }
    }

void MainObject::DoPlayer(Map& map_data)
{
    if(come_back_time == 0)
    {
    x_val=0;
    y_val += 3.9;
    if(y_val >= MAX_FALL_SPEED) y_val=MAX_FALL_SPEED;
    if(input_type.left==1)
    {
        x_val -= PLAYER_SPEED;
    }
    if(input_type.right==1)
    {
        x_val += PLAYER_SPEED;
    }
    if(input_type.jump == 1)
    {
        if(onGround == true){
            y_val = - PLAYER_JUMP_VAL;
        }

        onGround = false;
        input_type.jump=0;

    }
    CheckToMap(map_data);
    CenterEntityOnMap(map_data);
    }
    if(come_back_time > 0){
            come_back_time--;
    if(come_back_time == 0){

        onGround = false;
        x_val = 0;
        y_pos = 0;
        y_val =0;
    }
    }
}

void MainObject::CheckToMap(Map& map_data)
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

            if((map_data.tile[y1][x2]  != BLANK_TILE && map_data.tile[y1][x2]  < 10 || map_data.tile[y1][x2] == 26) || (map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2]  < 10 || map_data.tile[y2][x2] == 26   ))
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= wframe +1;
                x_val = 0;

            }
        }
        else if(x_val <0)
        {

            if((map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] < 10 || map_data.tile[y1][x1] == 26) || (map_data.tile[y2][x1] != BLANK_TILE && map_data.tile[y2][x1] < 10 || map_data.tile[y2][x1] == 26))
            {
                x_pos = (x1 + 1)*TILE_SIZE;
                x_val = 0;

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
            if((map_data.tile[y2][x1] != BLANK_TILE && map_data.tile[y2][x1] < 10 || map_data.tile[y2][x1] == 26) || (map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] < 10 || map_data.tile[y2][x2] == 26))
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= hframe +1;
                y_val = 0;
                if(status == WALK_NONE )
                {
                    status = WALK_RIGHT;
                }
                onGround = true;
            }
        }

        else if(y_val < 0)
        {
            if((map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] < 10 || map_data.tile[y1][x1] == 26) || (map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] < 10 || map_data.tile[y1][x2] == 26))
            {
                y_pos = (y1+1)*TILE_SIZE;
                y_val = 0;

            }

            if(map_data.tile[y1][x1] == 3){

                map_data.tile[y1][x1] = 26;

            }
        }
    x_pos += x_val;
    y_pos += y_val;
    if(x_pos < 0) x_pos =0;
    else if(x_pos + wframe > map_data.max_x)
    {
        x_pos = map_data.max_x - wframe -1;
    }
    if(y_pos > map_data.max_y)
    {
        come_back_time = 60;
    }
}

}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH/2);
    if(map_data.start_x < 0)
    {
        map_data.start_x=0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }
    map_data.start_y = y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y < 0)
    {
        map_data.start_y=0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y=map_data.max_y - SCREEN_HEIGHT;
    }
}

bool MainObject::CheckToBlocks(Map& map_data)
{
    bool check=false;
    int x1=0,x2=0;
    int y1=0,y2=0;
    int width_min = wframe < TILE_SIZE ? wframe : TILE_SIZE;
    x1 = x_pos/TILE_SIZE;
    x2 = (x_pos+width_min)/TILE_SIZE;

    y1=(y_pos + y_val)/TILE_SIZE;
    y2=(y_pos +y_val + hframe -1)/TILE_SIZE;
    if(x1 >=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(y_val < 0)
        {
            if(map_data.tile[y1][x1] == 3){
                check=true;
                pos1=x1;
                pos2=y1;
            }
        }
}
        return check;
}

void MainObject::updateImagePlayer(SDL_Renderer* renderer)
{
    if(onGround==true)
    {
        if(status == WALK_LEFT)
        {
            LoadImg("Image/mario_left.png",renderer);
        }
        else if(status == WALK_RIGHT)
        {
            LoadImg("Image/mario_right.png",renderer);
        }
    }
    if(onGround == false){
        if(status == WALK_LEFT)
        {
            LoadImg("Image/mariojump_left.png",renderer);
        }
        else{
            LoadImg("Image/mariojump_right.png",renderer);
        }

    }
}
