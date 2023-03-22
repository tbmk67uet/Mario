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



const char WINDOW_TITLE[] = "An Implementation of Code.org Painter";

SDL_Window *window;

SDL_Renderer *renderer;

bool LoadBackground(){
    bool ret=gBackground.LoadImg("bk1.png",renderer);
    if(ret == false) return false;
    return true;
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> listThreats;
    ThreatsObject* threats_objs = new ThreatsObject[20];
    for(int i=0;i<20;i++)
    {
        ThreatsObject* pThreat = (threats_objs+i);
        if(pThreat != NULL)
        {
            pThreat->LoadImg("Image/threat_level.png",renderer);
            pThreat->setClip();
            pThreat->set_x_pos(10+i*3);
            pThreat->set_y_pos(8*64);
            listThreats.push_back(pThreat);
        }
    }
    return listThreats;
}

int main(int argc,char* argv[]){
    ImpTimer fpsTimer;
    initSDL(window,renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    if(LoadBackground() == false) return -1;
    GameMap game_map;
    game_map.LoadMap("map/map01.txt");
    game_map.LoadTiles(renderer);
    MainObject player;
    player.LoadImg("Image/mario_right.png",renderer);
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
    //gBackground.render(renderer,NULL);
    Map map_data = game_map.getMap();

    player.SetMapXY(map_data.start_x,map_data.start_y);
    player.DoPlayer(map_data);
    player.Show(renderer);
    game_map.SetMap(map_data);
    game_map.DrawMap(renderer);
    for(int i=0;i<threatsList.size();i++)
    {
        ThreatsObject* pThreat = threatsList.at(i);
        if(pThreat != NULL)
        {
            pThreat->SetMapXY(map_data.start_x,map_data.start_y);
            pThreat->DoPlayer(map_data);
            pThreat->Show(renderer);
        }
    }
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



















