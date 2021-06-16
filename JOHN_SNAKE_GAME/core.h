//includes core dependencies

#ifndef _CORE_H_
#define _CORE_H_


#include <stdio.h>
#include <cstdlib>
#include <random>
#include <chrono>
#include <conio.h>
#include <vector>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

//types for specifying which direction the snake is heading and in which state (NFA model) the game is in
typedef enum directionT { up = 0, down, left, right };
typedef enum stateT { start = 0, pregame, controls, ingame, stopped, end } stateT;

#endif // !_CORE_H_