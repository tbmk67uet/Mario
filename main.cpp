#include <iostream>
#include <SDL.h>
#include "SDL_Utils.h"
#include "BaseObject.h"
#include <SDL_image.h>
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "Coin.h"
#include <vector>

BaseObject gBackground;
TTF_Font* font;


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

    ThreatsObject* dynamicThreats = new ThreatsObject[30];
    for(int i=0;i<30;i++)
    {
        ThreatsObject* pThreats = dynamicThreats + i;
        if(pThreats != NULL)
        {
            pThreats->LoadImg("Image/goombas.png",renderer);
            pThreats->setClip();
            pThreats->setTypeMove(ThreatsObject::MOVE_IN_SPACE_THREAT);
            pThreats->set_x_pos(500+i*500);
            pThreats->set_y_pos(200);

            int pos1=pThreats->get_x_pos()-240;
            int pos2=pThreats->get_x_pos()+240;
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

int i = 0;

int main(int argc,char* argv[]){
    int coin = 0;
    int lives = 3;
    int scores = 0;
    ImpTimer fpsTimer;
    std::vector<Coin> coinList(15);
    std::vector<int> list1(15);
    std::vector<int> list2(15);
    initSDL(window,renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE,font);
    if(LoadBackground() == false) return -1;
    GameMap game_map;
    game_map.LoadMap("map1/map01.dat");
    game_map.LoadTiles(renderer);
    MainObject player;
    player.LoadImg("Image/1.png",renderer);
    player.setclips();
    std::vector<ThreatsObject*> threatsList = MakeThreatList();
    bool quit=false;SDL_Event e;
    TextObject time_game;
    TextObject Coins;
    TextObject Lives;
    TextObject Scores;
    time_game.SetColor(TextObject::WHITE_TEXT);

    while(!quit){
        fpsTimer.start();
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT){
                quit=true;
            }
            player.HandleInput(e,renderer);
        }


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    gBackground.render(renderer,NULL);
    Map map_data = game_map.getMap();

    player.SetMapXY(map_data.start_x,map_data.start_y);
    player.DoPlayer(map_data);
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
    for(int z=0;z<threatsList.size();z++)
    {
        ThreatsObject* pThreat = threatsList.at(z);
        //std::cout << pThreat->get_y_pos() << std::endl;

        if(player.getXpos()  <= pThreat->get_x_pos()+1.7 && player.getXpos() >= pThreat->get_x_pos()-1.7 && player.getYpos() >= pThreat->get_y_pos()-1 && player.getYpos()<=pThreat->get_y_pos()+1)
        {
            lives--;
            continue;
        }

        if(player.getXpos()  <= pThreat->get_x_pos()+1.7 && player.getXpos() >= pThreat->get_x_pos()-1.7 && player.getYpos() <= 222.9 && player.getYpos() >= 191.7 ){
            std::cout << player.getYpos() << std::endl;
            std::cout << "var" << std::endl;
            pThreat->set_x_pos(-20482048.0);
            pThreat->set_y_pos(-20482048.0);
            scores += 100 ;
        }


    }
    player.Show(renderer);
    if(player.CheckToBlocks(map_data) == true)
    {
        i++;
        list1[i-1]=(player.makeX()*TILE_SIZE);
        list2[i-1]=((player.makeY()-1)*TILE_SIZE);
    }

    for(int j=0;j<i;j++)
    {
        coinList[j].LoadImg("Image/Coin.png",renderer);
        coinList[j].setClip();
        coinList[j].Show(renderer,list1[j]-map_data.start_x,list2[j]-map_data.start_y);
    }

    for(int j=0;j<i;j++ )
    {
        if(player.getYpos()  <= list2[j]+10 && player.getYpos() >= list2[j]-10 && player.getXpos() >= list1[j]-10 && player.getXpos()<=list1[j]+10)
        {
           coin++;
           list1[j]=-32;
           list2[j]=-32;
        }
    }

    font = TTF_OpenFont("Font/dlxfont.ttf",15);


    std::string live="Lives: "+std::to_string(lives);
    std::string coinVal="Coin: "+std::to_string(coin);
    std::string scoresVal="Scores: "+std::to_string(scores);

    Coins.SetText(coinVal);
    Coins.LoadFromRenderText(font,renderer);
    Coins.RenderText(renderer,SCREEN_WIDTH-900,15);

    Lives.SetText(live);
    Lives.LoadFromRenderText(font,renderer);
    Lives.RenderText(renderer,SCREEN_WIDTH-700,15);

    Scores.SetText(scoresVal);
    Scores.LoadFromRenderText(font,renderer);
    Scores.RenderText(renderer,SCREEN_WIDTH-400,15);

    std::string time="Time: ";
    uint32_t time_val = SDL_GetTicks()/1000;
    uint32_t val_time = 300-time_val;
    if(val_time <= 0) quit = true;
    else{
        std::string strVal=std::to_string(val_time);
        time += strVal;
        time_game.SetText(time);
        time_game.LoadFromRenderText(font,renderer);
        time_game.RenderText(renderer,SCREEN_WIDTH-200,15);
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
