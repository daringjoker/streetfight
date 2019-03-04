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
#include "player.h"
#include "AI.h"
bool running= true;
using namespace std;
void handle_event(player &p1,player &p2)
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
                        case SDLK_UP:
                            p1.jump();
                            break;
                        case SDLK_LEFT:
                            p1.walkb();
                            break;
                        case SDLK_SLASH:
                            p1.kick();
                            break;
                        case SDLK_KP_0:
                            p1.punch();
                            break;
                        case SDLK_d:
                            p2.walkf();
                            break;
                        case SDLK_w:
                            p2.jump();
                            break;
                        case SDLK_a:
                            p2.walkb();
                            break;
                        case SDLK_q:
                            p2.kick();
                            break;
                        case SDLK_e:
                            p2.punch();
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
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *win=SDL_CreateWindow("Street fight Neo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600,SDL_WINDOW_SHOWN);
        SDL_Renderer *Ren=SDL_CreateRenderer(win,0,1);
        SDL_Surface *temp=SDL_LoadBMP("stage.bmp");
        SDL_Texture *stage=SDL_CreateTextureFromSurface(Ren,temp);
        SDL_FreeSurface(temp);
        player dummy(Ren);
        player opponent(Ren);
        player self(Ren,false);
        AI computer1(opponent,self);
        opponent.set_opponent(&self);
        self.set_opponent(&opponent);
        while (running)
        {
            handle_event(self,dummy);
            computer1.drive();
            SDL_RenderCopy(Ren, stage, nullptr, nullptr);
            self.update();
            opponent.update();
            SDL_RenderPresent(Ren);
            SDL_Delay(25);
        }
        return 0;
    }