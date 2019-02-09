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


    public:
        explicit player1(SDL_Renderer *renderer);
        void walkf();
        void walkb();
        void idle();
        SDL_Rect getPlayerRect();


    };



#endif //STREETFIGHT_PLAYER1_H
