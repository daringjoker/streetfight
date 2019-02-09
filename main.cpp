/*
*Author:-Pukar Giri
*Created On:-07Th February 2019 at 17:45
*File Name:-main.cpp
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include <iostream>
#include<SDL2/SDL.h>
#include "player1.h"
bool running= true;
using namespace std;
void handle_event(SDL_Window *window,player1 &p1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            p1.walkf();
                            break;
                        case SDLK_LEFT:
                            p1.walkb();
                            break;
                    }
                    break;
                case SDL_QUIT:
                    running= false;
                    SDL_Quit();
            }
        }
    }



int main()
    {


        //        std::cout << SDL_INIT_EVERYTHING << std::endl;
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *win=SDL_CreateWindow("Street fight Neo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600,SDL_WINDOW_SHOWN);
        SDL_Renderer *Ren=SDL_CreateRenderer(win,0,1);
        player1 ryu(Ren);
        while (running)
        {
            handle_event(win,ryu);
            SDL_SetRenderDrawColor(Ren,255,255,255,1);
            SDL_RenderClear(Ren);
            ryu.idle();
            SDL_RenderPresent(Ren);
//            SDL_Delay(25);
        }




        return 0;
    }