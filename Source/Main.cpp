#include <SDL.h>
#include<iostream>
#include "GameHandler.h"
#undef main //For Visual Studio 2015 Users (I am one of them)

//For SDL, you should have the following main method:
int main(int argc, char** args)
{
    GameHandler main;

    main.GameLoop();

    return 0;
}