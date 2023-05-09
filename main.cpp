#include <iostream>
#include <SDL.h>
#include "SDL_Utils.h"
#include "BaseObject.h"
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "MenuObject.h"
#include "SDL_mixer.h"
#include "Coin.h"
#include <vector>

BaseObject gBackground;
TTF_Font* font;
TTF_Font* gfont;
TTF_Font* mfont;

const char WINDOW_TITLE[] = "Super Mario";

SDL_Window *window=NULL;

SDL_Renderer *renderer=NULL;

bool LoadBackground()
{
    bool ret=gBackground.LoadImg("Image/bg.png",renderer);
    if(ret == false) return false;
    return true;
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> listThreats;

    ThreatsObject* dynamicThreats = new ThreatsObject[19];
    for(int i=0; i<19; i++)
    {
        ThreatsObject* pThreats = dynamicThreats + i;
        if(pThreats != NULL)
        {
            pThreats->LoadImg("Image/goombas.png",renderer);
            pThreats->setClip();
            pThreats->set_x_pos(200+i*300);
            pThreats->set_y_pos(400);

            int pos1=pThreats->get_x_pos()-120;
            int pos2=pThreats->get_x_pos()+120;
            pThreats->SetAnimationPos(pos1,pos2);
            listThreats.push_back(pThreats);
        }
    }
    return listThreats;
}

int i = 0;
int checkMap=1;

int main(int argc,char* argv[])
{
    int coin = 0;
    int lives = 3;
    int scores = 0;

    int mscores;
    int mcoin;

    Mix_Music* gMusic;
    Mix_Chunk* gCoin;
    Mix_Chunk* gJump;
    Mix_Chunk* gStomp;
    Mix_Chunk* gDeath;

    ImpTimer fpsTimer;

    std::vector<Coin> coinList1(15);
    std::vector<int> list1(15);
    std::vector<int> list2(15);

    std::vector<Coin> coinList2(12);
    std::vector<int> List1= {1408,1440,1504,1536,1600,1632,2048,2080,2112,2144,2368,2400};
    std::vector<int> List2= {256,256,192,192,256,256,256,256,256,256,256,256};

    initSDL(window,renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE,font);

    gMusic = Mix_LoadMUS("Music/Mario.mp3");
    gCoin = Mix_LoadWAV("Music/Coin.mp3");
    gJump = Mix_LoadWAV("Music/Jump.wav");
    gStomp = Mix_LoadWAV("Music/Stomp.wav");
    gDeath = Mix_LoadWAV("Music/Death.wav");

    mfont = TTF_OpenFont("Font/dlxfont.ttf",20);
    if(LoadBackground() == false) return -1;
    GameMap game_map;
    game_map.LoadMap("map1/map01.dat");
    game_map.LoadTiles1(renderer);
    std::vector<ThreatsObject*> threatsList = MakeThreatList();
    bool quit = false;
    SDL_Event e;

    TextObject time_game;
    TextObject Coins;
    TextObject Lives;
    TextObject Scores;
    TextObject insGame[2];

    time_game.SetColor(TextObject::WHITE_TEXT);

    std::string s1="Arrow keys move";
    std::string s2="M to mute";
    uint32_t x_time;
    uint32_t time_val;
    while(true)
    {
        game_map.LoadMap("map1/map01.dat");
        Mix_PauseMusic();
        for(int i=0; i<15; i++)
        {
            list1[i]=-32;
            list2[i]=-32;
        }
        MainObject player;
        player.LoadImg("Image/mario_right.png",renderer);
        player.setclips();
        quit=false;
        lives=3;
        coin=0;
        int check = MenuObject::ShowMenu(renderer,mfont,gBackground);
        if(check == 1) return 0;
        if(LoadBackground() == false) return -1;
        if(Mix_PausedMusic() == 1 && check == 0)
        {
            Mix_PlayMusic(gMusic,-1);
        }

        while(!quit)
        {
            time_val = SDL_GetTicks()/1000;
            uint32_t val_time = 200-time_val+x_time;
            if(Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(gMusic,-1);
            }
            font = TTF_OpenFont("Font/dlxfont.ttf",15);

            gfont = TTF_OpenFont("Font/dlxfont.ttf",25);

            fpsTimer.start();
            int m=0;
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
                if(e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_m)
                    {
                        if(Mix_PlayingMusic() == 1)
                        {
                            Mix_PauseMusic();
                            Mix_VolumeChunk(gJump,0);
                            Mix_VolumeChunk(gStomp,0);
                            Mix_VolumeChunk(gCoin,0);
                        }
                    }
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
            if(map_data.start_x<=512)
            {
                insGame[0].SetText(s1);
                insGame[0].LoadFromRenderText(mfont,renderer);
                insGame[0].RenderText(renderer,64-map_data.start_x,200);

                insGame[1].SetText(s2);
                insGame[1].LoadFromRenderText(mfont,renderer);
                insGame[1].RenderText(renderer,64-map_data.start_x,230);
            }

            for(int i=0; i<threatsList.size(); i++)
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
            for(int z=0; z<threatsList.size(); z++)
            {
                ThreatsObject* pThreat = threatsList.at(z);
                //Xử lí khi bị quái gi**
                if(player.getXpos()  <= pThreat->get_x_pos()+8 && player.getXpos() >= pThreat->get_x_pos()-8 && player.getYpos() >= pThreat->get_y_pos()-5 && player.getYpos()<=pThreat->get_y_pos()+5)
                {
                    SDL_Delay(2000);
                    player.setXpos(0);
                    player.setYpos(0);
                    lives--;
                    if(lives!=0) scores=0;
                    if(checkMap == 1) game_map.LoadMap("map1/map01.dat");
                    if(checkMap == 2){
                        game_map.LoadMap("map2/map02.dat");
                        List1= {1408,1440,1504,1536,1600,1632,2048,2080,2112,2144,2368,2400};
                        List2= {256,256,192,192,256,256,256,256,256,256,256,256};
                    }
                    threatsList.clear();
                    threatsList = MakeThreatList();
                }
                //Gi** quái
                if(player.getYval() >=0 && player.getXpos()  <= pThreat->get_x_pos()+15 && player.getXpos() >= pThreat->get_x_pos()-15 && player.getYpos() <= 338 && player.getYpos() >= 319.7 )
                {
                    player.setYval(-25.0);
                    pThreat->set_x_pos(-1000000);
                    pThreat->set_y_pos(-1000000);
                    pThreat->set_x_val(0);
                    pThreat->set_y_val(0);
                    pThreat = NULL;
                    Mix_PlayChannel(-1,gStomp,0);
                    scores += 200 ;
                }
                //Rơi xuống vực
                if(player.getYpos()>OUT_OF_MAP)
                {
                    lives-- ;
                    scores = 0;
                    player.setXpos(0);
                    player.setYpos(0);
                    if(checkMap == 1) game_map.LoadMap("map1/map01.dat");
                    if(checkMap == 2){
                        game_map.LoadMap("map2/map02.dat");
                    }
                    SDL_Delay(2000);
                }

            }
            player.Show(renderer);
            //Chạm vào các ô ?
            if(player.CheckToBlocks(map_data) == true)
            {
                i++;
                list1[i-1]=player.makeX()*TILE_SIZE;
                list2[i-1]=(player.makeY()-1)*TILE_SIZE;
            }
            //Hiện coin,ăn coin
            for(int j=0; j<i; j++)
            {
                coinList1[j].LoadImg("Image/Coin.png",renderer);
                coinList1[j].setClip();
                coinList1[j].Show(renderer,list1[j]-map_data.start_x,list2[j]-map_data.start_y);
                if(player.getYpos()  <= list2[j]+20 && player.getYpos() >= list2[j]-20 && player.getXpos() >= list1[j]-15 && player.getXpos()<=list1[j]+15)
                {
                    coin++;
                    list1[j]=-32;
                    list2[j]=-32;
                    Mix_PlayChannel(-1,gCoin,0);
                }
            }
            if(player.getYval() == -30)
            {
                Mix_PlayChannel(-1,gJump,0);
            }
            //Hiện coin
            if(checkMap == 2)
            {
                for(int j=0; j<coinList2.size(); j++)
                {
                    coinList2[j].LoadImg("Image/Coin.png",renderer);
                    coinList2[j].setClip();
                    coinList2[j].Show(renderer,List1[j]-map_data.start_x,List2[j]);
                    if(player.getYpos()  <= List2[j]+10 && player.getYpos() >= List2[j]-10 && player.getXpos() >= List1[j]-10 && player.getXpos()<=List1[j]+10)
                    {
                        coin++;
                        List1[j]=-32;
                        List2[j]=-32;
                        Mix_PlayChannel(-1,gCoin,0);
                    }
                }
            }

            std::string live="Lives: "+std::to_string(lives);
            std::string coinVal="Coin: "+std::to_string(coin);
            std::string scoresVal="Scores: "+std::to_string(scores);

            mscores=scores;
            mcoin=coin;

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

            if(val_time <= 0) quit = true;
            else
            {
                std::string strVal=std::to_string(val_time);
                time += strVal;
                time_game.SetText(time);
                time_game.LoadFromRenderText(font,renderer);
                time_game.RenderText(renderer,SCREEN_WIDTH-200,15);
            }
            if(lives <= 0)
            {
                Mix_PlayChannel(-1,gDeath,0);
                Mix_PauseMusic();
                gBackground.free();
                bool ret = gBackground.LoadImg("Image/gameover.png",renderer);
                SDL_RenderCopy(renderer,gBackground.getTexture(),NULL,NULL);
                quit=true;
            }
            //Về đích map1
            if(player.getXpos()>=MAX_MAP_1 && checkMap == 1)
            {
                SDL_Delay(2000);
                player.setXpos(0);
                player.setYpos(0);
                checkMap = 2;
                gBackground.free();
                bool ret = gBackground.LoadImg("Image/bg3.png",renderer);
                gBackground.render(renderer,NULL);
                game_map.LoadMap("map2/map02.dat");
                game_map.LoadTiles2(renderer);
                threatsList.clear();
                threatsList = MakeThreatList();
            }
            //Về đích map2
            if(player.getXpos()>=MAX_MAP_2 && checkMap == 2)
            {
                quit=true;
            }

            SDL_RenderPresent(renderer);
            int real_imp_time = fpsTimer.get_ticks();
            int time_one_frame = 1000/FRAME_PER_SECOND;

            if(real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time>=0)
                {
                    SDL_Delay(delay_time);
                }
            }
        }


        if(quit == true)
        {
            x_time = time_val+8;
            SDL_Delay(2000);
            gBackground.free();
            bool ret = gBackground.LoadImg("Image/bg1.png",renderer);
            SDL_RenderCopy(renderer,gBackground.getTexture(),NULL,NULL);

            std::string scoreVal = "Scores: "+std::to_string(mscores);
            std::string coinVal = "Coin: "+std::to_string(mcoin);

            Scores.SetText(scoreVal);
            Scores.LoadFromRenderText(gfont,renderer);
            Scores.RenderText(renderer,SCREEN_WIDTH/2+100,SCREEN_HEIGHT/2);

            Coins.SetText(coinVal);
            Coins.LoadFromRenderText(gfont,renderer);
            Coins.RenderText(renderer,SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2);

            SDL_RenderPresent(renderer);
            SDL_Delay(2000);

            continue;
        }
    }
    quitSDL(window,renderer);
    return 0;
}
