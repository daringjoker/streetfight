/*
*Author:-Pukar Giri
*Created On:-07Th February 2019 at 17:46
*File Name:-player1.cpp
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "player1.h"



player1::player1(SDL_Renderer *renderer)
    {
        this->renderer=renderer;
        //loading the spritesheet
        SDL_Surface *temp=SDL_LoadBMP("fighter.bmp");
        this->spritesheet=SDL_CreateTextureFromSurface(renderer,temp);
        SDL_FreeSurface(temp);
        //loading the stage
        temp=SDL_LoadBMP("stage.bmp");
        this->stage=SDL_CreateTextureFromSurface(renderer,temp);
        SDL_FreeSurface(temp);
        //initializing the idle animation frames
        idleframes.push_back({7, 14, 60, 90});
        idleframes.push_back({95, 15, 60, 89});
        idleframes.push_back({184, 14, 60, 90});
        idleframes.push_back({276, 11, 60, 93});
        idleframes.push_back({366, 12, 60, 92});
        //initializing the forward walk animation frames
        forwardframes.push_back({ 0, 127, 68, 93 });
        forwardframes.push_back({ 78, 127, 68, 93 });
        forwardframes.push_back({ 161, 127, 68, 93 });
        forwardframes.push_back({ 251, 127, 73, 93 });
        forwardframes.push_back({ 341, 127, 68, 93 });
        forwardframes.push_back({ 419, 127, 68, 93 });
        //initializing the backward walk animation frames
        backwardframes.push_back({542, 131, 61, 87});
        backwardframes.push_back({628, 129, 59, 90});
        backwardframes.push_back({713, 128, 57, 90});
        backwardframes.push_back({797, 127, 57, 90});
        backwardframes.push_back({883, 128, 58, 91});
        backwardframes.push_back({974, 129, 57, 89});
    }



void player1::walkf()
    {
        for (auto frame:forwardframes)
        {
            SDL_Rect playerrect=getPlayerRect();
            SDL_Delay(75);
            x=x+10;
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }

    }



SDL_Rect player1::getPlayerRect()
    {
        return SDL_Rect({x,y,100,200});
    }



void player1::walkb()
    {
        for (auto frame:backwardframes)
        {
            SDL_Rect playerrect=getPlayerRect();
            SDL_Delay(75);
            x=x-10;
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
    }



void player1::idle()
    {
        for (auto frame:idleframes)
        {
            SDL_Rect playerrect=getPlayerRect();
            SDL_Delay(100);
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
    }
