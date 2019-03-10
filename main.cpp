/*
*Author:-Pukar Giri
*Created On:-07Th February 2019 at 17:45
*File Name:-main.cpp
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include <iostream>
#include <string>
#include<SDL2/SDL.h>
#include "player.h"
#include "AI.h"
#include "network.h"
#include "menu.h"
bool running= true;
using namespace std;

void loose(menu & mainmenu,SDL_Renderer * renderer);
void winner(menu & mainmenu,SDL_Renderer * renderer);
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
                        case SDLK_ESCAPE:
                            exit(0);
                    }
                    break;
                case SDL_QUIT:
                    running= false;
                    SDL_Quit();
                    exit(0);
            }
        }
    }
void banner()
    {
        SDL_Window *window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_ALWAYS_ON_TOP);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Surface *banner1 = SDL_LoadBMP("wel1.bmp");
        SDL_Texture *b1 = SDL_CreateTextureFromSurface(renderer, banner1);
        SDL_FreeSurface(banner1);
        int value=0;
        while(value<100)
        {
            SDL_Rect loadbar={0,380,int(800*(value/100.0)),2};
            SDL_Rect leadbar={int(800*(value/100.0)),379,4,4};
            SDL_RenderCopy(renderer, b1, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,242, 226, 53,255);
            SDL_RenderFillRect(renderer,&loadbar);
            SDL_RenderFillRect(renderer,&leadbar);
            SDL_RenderPresent(renderer);
            SDL_Delay(60);
            value+=rand()%4;
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
int play(SDL_Window *win,SDL_Renderer *Ren);
int main()
    {

        SDL_Init(SDL_INIT_EVERYTHING);
        banner();
        SDL_Window *win=SDL_CreateWindow("Street fight Neo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600,SDL_WINDOW_SHOWN);
        SDL_Renderer *Ren=SDL_CreateRenderer(win,0,1);
        while(running)
        {
            play(win,Ren);
        }
    }

int play(SDL_Window *win,SDL_Renderer *Ren)
    {

        menu mainmenu(Ren);
        mainmenu.display();
        SDL_Surface *temp=SDL_LoadBMP("stage.bmp");
        SDL_Texture *stage=SDL_CreateTextureFromSurface(Ren,temp);
        SDL_FreeSurface(temp);
        player dummy(Ren);
        player self(Ren,!mainmenu.team_red);
        player opponent(Ren,mainmenu.team_red);
        AI computer1(opponent,self);
        opponent.set_opponent(&self);
        self.set_opponent(&opponent);
        network net(opponent, self, mainmenu.team_red);
        if (mainmenu.net)
        {
            net.initialize();
        }
        while (running)
        {
            if (!mainmenu.two_on_one) handle_event(self,dummy);
            if (mainmenu.two_on_one) handle_event(self,opponent);
            if (mainmenu.single_player) computer1.drive();
            if (mainmenu.net) net.send_state();
            SDL_RenderCopy(Ren, stage, nullptr, nullptr);
            self.update();
            opponent.update();
            if (self.health<=0)
            {
                loose(mainmenu,Ren);
                break;
            }

            if (opponent.health<=0)
            {
                winner(mainmenu,Ren);
                break;
            }
            SDL_RenderPresent(Ren);
            SDL_Delay(25);

        }
        return 0;
    }

    void loose(menu & mainmenu,SDL_Renderer * renderer)
        {
            string text;
            if(mainmenu.two_on_one){
                if (mainmenu.team_red) text+="Red Has Won!";
                else text+="Blue has won!";
            }else
            {
                text+="YOU have lost!";
            }
            SDL_Rect current={200,200,800,200};
            TTF_Font *font = TTF_OpenFont("Xanadu.ttf", 60);
            SDL_Color color={0,0,0};
            SDL_Surface * surface = TTF_RenderText_Solid(font,text.c_str(),color);
            SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
            current.x=current.x+(current.w-texW)/2;
            current.y=current.y+(current.h-texH)/2;
            current.w=texW;
            current.h=texH;
            SDL_RenderCopy(renderer, texture, NULL,&current);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

        }
        void winner(menu & mainmenu,SDL_Renderer * renderer)
        {
            string text;
            if(mainmenu.two_on_one){
                if (mainmenu.team_red) text+="Red Has Won";
                else text+="Blue has won";
            }
            else
            {
                text+="YOU Have WON!";
            }
            SDL_Rect current={200,200,800,200};
            TTF_Font *font = TTF_OpenFont("Xanadu.ttf", 60);
            SDL_Color color={0,0,0};
            SDL_Surface * surface = TTF_RenderText_Solid(font,text.c_str(),color);
            SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
            current.x=current.x+(current.w-texW)/2;
            current.y=current.y+(current.h-texH)/2;
            current.w=texW;
            current.h=texH;
            SDL_RenderCopy(renderer, texture, NULL,&current);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

        }