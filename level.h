#ifndef MAP_H
#define MAP_H


class Level
{
public:
    Level();
    void generate();
private:
    int height,width;
};

class Terrain{
public:
    Terrain();
private:
    int pos_x,pos_y;
    bool block_movement = true;
    bool block_shoots = true;
};

#endif // MAP_H
