/*
*Author:-Pukar Giri
*Created On:-07Th February 2019 at 17:46
*File Name:-player1.h
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef STREETFIGHT_PLAYER1_H
#define STREETFIGHT_PLAYER1_H
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
using namespace std;
class player1
    {
    private:
        int x=0;
        int y=350;
        int z;
        int health=100;
        int strength=60;
        SDL_Renderer *renderer;
        SDL_Texture * spritesheet;
        SDL_Texture * stage;
        vector <SDL_Rect> idleframes;
        vector <SDL_Rect> forwardframes;
        vector <SDL_Rect> backwardframes;
        vector <SDL_Rect> kickframes;
        vector <SDL_Rect> punchframes;
        vector <SDL_Rect> jumpframes;


    public:
        explicit player1(SDL_Renderer *renderer);
        void walkf();
        void walkb();
        void idle();
        void jump();
        void kick();
        void punch();
        SDL_Rect getPlayerRect();


    };



#endif //STREETFIGHT_PLAYER1_H
