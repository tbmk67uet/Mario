#include <iostream>
#include <SDL.h>
#include "SDL_Utils.h"
#include "BaseObject.h"
#include <SDL_image.h>
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include <vector>

BaseObject gBackground;



const char WINDOW_TITLE[] = "Super Mario";

SDL_Window *window;

SDL_Renderer *renderer;

bool LoadBackground(){
    bool ret=gBackground.LoadImg("Image/bg.png",renderer);
    if(ret == false) return false;
    return true;
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> listThreats;

    ThreatsObject* dynamicThreats = new ThreatsObject[20];
    for(int i=0;i<20;i++)
    {
        ThreatsObject* pThreats = dynamicThreats + i;
        if(pThreats != NULL)
        {
            pThreats->LoadImg("Image/goombas.png",renderer);
            pThreats->setClip();
            pThreats->setTypeMove(ThreatsObject::MOVE_IN_SPACE_THREAT);
            pThreats->set_x_pos(500+i*500);
            pThreats->set_y_pos(200);

            int pos1=pThreats->get_x_pos()-120;
            int pos2=pThreats->get_x_pos()+120;
            pThreats->SetAnimationPos(pos1,pos2);
            listThreats.push_back(pThreats);
        }
    }

    /*
    ThreatsObject* threats_objs = new ThreatsObject[20];
    for(int i=0;i<20;i++)
    {
        ThreatsObject* pThreat = (threats_objs+i);
        if(pThreat != NULL)
        {
            pThreat->LoadImg("Image/threat_level.png",renderer);
            pThreat->setClip();
            pThreat->set_x_pos(700+i*1200);
            pThreat->set_y_pos(250);
            pThreat->setTypeMove(ThreatsObject::STATIC_THREAT);
            pThreat->set_input_left(0);
            listThreats.push_back(pThreat);
        }
    }
    */
    return listThreats;
}

int main(int argc,char* argv[]){
    ImpTimer fpsTimer;
    initSDL(window,renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    if(LoadBackground() == false) return -1;
    GameMap game_map;
    game_map.LoadMap("map1/map01.dat");
    game_map.LoadTiles(renderer);
    MainObject player;
    player.LoadImg("Image/1.png",renderer);
    player.setclips();
    std::vector<ThreatsObject*> threatsList = MakeThreatList();
    bool quit=false;SDL_Event e;
    while(!quit){
        fpsTimer.start();
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT){
                quit=true;
            }
            player.HandleInput(e,renderer);
        }

    player.HandleInput(e,renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    gBackground.render(renderer,NULL);
    Map map_data = game_map.getMap();

    player.SetMapXY(map_data.start_x,map_data.start_y);
    player.DoPlayer(map_data);
    //player.Show(renderer);
    game_map.SetMap(map_data);
    game_map.DrawMap(renderer);
    for(int i=0;i<threatsList.size();i++)
    {
        ThreatsObject* pThreat = threatsList.at(i);
        if(pThreat != NULL)
        {
            pThreat->SetMapXY(map_data.start_x,map_data.start_y);
            pThreat->ImpMoveType(renderer);
            pThreat->DoPlayer(map_data);
            pThreat->Show(renderer);
        }
    }
    player.Show(renderer);
    SDL_RenderPresent(renderer);
    int real_imp_time = fpsTimer.get_ticks();
    int time_one_frame = 1000/FRAME_PER_SECOND;

    if(real_imp_time < time_one_frame)
    {
        int delay_time = time_one_frame - real_imp_time;
        if(delay_time>=0){
        SDL_Delay(delay_time);}
    }

    }

    quitSDL(window,renderer);
    return 0;
}



















