#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "cdT.h"

typedef enum directionT { up=0, down, left, right } directionT;
typedef enum stateT { start=0, pregame, controls, ingame, stopped, end } stateT;

class Snake
{
private:
public:
    Snake(int);
    directionT direction;
    cdT head;
    std::vector<cdT*>* snake_body_vector;
    cdT apple;
    bool CollidedIntoWall();
    bool AteApple();
    void createApple();
    void grow();
    void move();
    void changeDirection(directionT);
    void print();
    int getScore();
    void gotoxy(int, int);
};

#endif