#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include "SDL_Utils.h"
#include "BaseObject.h"

#define MAX_TILES 30

class TileMat : public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}
    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* renderer);
    void DrawMap(SDL_Renderer* renderer);
    Map getMap()  {return game_map;}
    void SetMap(Map& map_data) {game_map=map_data;}
private:
    Map game_map;
    TileMat tilemat[MAX_TILES];
};

#endif // GAMEMAP_H_INCLUDED
