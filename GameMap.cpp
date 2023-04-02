#include "BaseObject.h"
#include "GameMap.h"
#include "SDL_Utils.h"


void GameMap::LoadMap(char* name)
{
    FILE* fp=fopen(name,"r");

    game_map.max_x=0;
    game_map.max_y=0;
    for(int i=0;i<MAX_MAP_Y;i++){
        for(int j=0;j<MAX_MAP_X;j++){
            fscanf(fp,"%d",&game_map.tile[i][j]);
            int val = game_map.tile[i][j];

            if(val>0){
                if(j>game_map.max_x) game_map.max_x=j;
                if(i>game_map.max_y) game_map.max_y=i;
            }
        }
    }
    //2 vi tri xuong cuoi ban do
    game_map.max_x = (game_map.max_x+1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y+1)*TILE_SIZE;

    game_map.start_x=0;
    game_map.start_y=0;

    game_map.file_name = name;
    fclose(fp);

}

void GameMap::LoadTiles(SDL_Renderer* renderer){
    char file_img[30];
    FILE* fp=NULL;
    for(int i=1;i<26;i++){
        sprintf(file_img,"map1/%d.png",i);
        fp=fopen(file_img,"r");
        fclose(fp);
        tilemat[i].LoadImg(file_img,renderer);
    }
}


void GameMap::DrawMap(SDL_Renderer* renderer){
    int x1=0;int x2=0;
    int y1=0;int y2=0;
    int map_x=0;int map_y=0;


    //khi man hinh di chuyen ve cac o ko bi khuyet
    x1 = (game_map.start_x%TILE_SIZE)*(-1);
    x2 = x1 + SCREEN_WIDTH + (x1==0 ? 0 : TILE_SIZE);

    map_y=game_map.start_y/TILE_SIZE;
    y1 = (game_map.start_y%TILE_SIZE)*(-1);
    y2 = y1 + SCREEN_HEIGHT + (y1==0 ? 0 : TILE_SIZE);
    for(int i=y1;i<y2;i+=TILE_SIZE){
        map_x = game_map.start_x/TILE_SIZE;
        for(int j=x1;j<x2;j+=TILE_SIZE){
            int val = game_map.tile[map_y][map_x];

            if(val > 0){
                tilemat[val].SetRect(j,i);
                tilemat[val].render(renderer);
            }
            if(map_x<= MAX_MAP_X-2) map_x++;
            else break;
        }
        if(map_y<=MAX_MAP_Y-2) map_y++;
        else break;
    }

}
