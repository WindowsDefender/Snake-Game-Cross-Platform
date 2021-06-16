#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "cdT.h"

class Snake
{
private:
public:
    Snake(const int&);
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
    void testprint();
    void gotoxy(const int&, const int&);
};

#endif