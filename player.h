/*
*Author:-Pukar Giri
*Created On:-07Th February 2019 at 17:46
*File Name:-player.h
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
enum action{cwalkf,cwalkb,cjump,ckick,cpunch,cidle};
class player
    {
    public:
        player *opponent;
        float strength=60;
        bool left;
        SDL_RendererFlip flip;
        SDL_Renderer *renderer;
        SDL_Texture * spritesheet;
        vector <SDL_Rect> idleframes;
        vector <SDL_Rect> forwardframes;
        vector <SDL_Rect> backwardframes;
        vector <SDL_Rect> kickframes;
        vector <SDL_Rect> punchframes;
        vector <SDL_Rect> jumpframes;
        bool  has_hit();
        void _walkf();
        void _walkb();
        void _idle();
        void _jump();
        void _kick();
        void _punch();
        SDL_Rect getPlayerRect();
        void render(SDL_Rect* source, SDL_Rect* dest);

    public:
        int frame_count=0;
        int x=0;
        float health=100;
        int y=350;
        bool noted=false;
        action current_action=cidle;
        explicit player(SDL_Renderer *renderer,bool left=true);
        void set_opponent(player* opp);
        void update();
        void walkf();
        void walkb();
        void idle();
        void jump();
        void kick();
        void punch();
    };



#endif //STREETFIGHT_PLAYER1_H
