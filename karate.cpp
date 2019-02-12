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
        idleframes.push_back({276, 11, 60, 93});
        idleframes.push_back({184, 14, 60, 90});
        idleframes.push_back({95, 15, 60, 89});
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
        //initializing the backward punch animation frames
        punchframes.push_back({253, 269, 60, 94});
        punchframes.push_back({333, 268, 74, 95});
        punchframes.push_back({432, 268, 108, 94});
        punchframes.push_back({333, 268, 74, 95});
        punchframes.push_back({253, 269, 60, 94});
        //initializing the backward punch animation frames
        kickframes.push_back({606, 269, 60, 94});
        kickframes.push_back({689, 267, 66, 92});
        kickframes.push_back({777, 256, 114, 94});
        kickframes.push_back({689, 267, 66, 92});
        kickframes.push_back({606, 269, 60, 94});
        //initializing the backward jump animation frames
        jumpframes.push_back({17, 847, 55, 85});
        jumpframes.push_back({100, 823, 56, 104});
        jumpframes.push_back({176, 805, 50, 89});
        jumpframes.push_back({251, 798, 54, 79});
        jumpframes.push_back({327, 813, 48, 70});
        jumpframes.push_back({397, 810, 48, 89});
        jumpframes.push_back({464, 819, 55, 109});
        jumpframes.push_back({17, 847, 55, 85});
    }



void player1::walkf()
    {
        for (auto frame:forwardframes)
        {
            SDL_Rect playerrect=getPlayerRect();
            SDL_Delay(45);
            x=x+10;
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
        SDL_FlushEvent(SDL_KEYDOWN);
    }



SDL_Rect player1::getPlayerRect()
    {
        if (x<=0)x=0;
        if (x>900)x=900;
        return SDL_Rect({x,y,100,200});
    }



void player1::walkb()
    {
        for (auto frame:backwardframes)
        {
            SDL_Rect playerrect=getPlayerRect();
            SDL_Delay(45);
            x=x-10;
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
        SDL_FlushEvent(SDL_KEYDOWN);
    }



void player1::idle()
    {
        for (auto frame:idleframes)
        {
            SDL_Rect playerrect=getPlayerRect();
            SDL_Delay(75);
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
        SDL_FlushEvent(SDL_KEYDOWN);
    }



void player1::jump()
    {
        int count=0;
        int hfactor=0;
        for (auto frame:jumpframes)
        {
            if (count<=4)
            {
                hfactor=count;
            }else
            {
                hfactor=8-count;
            }
            SDL_Rect playerrect=getPlayerRect();
            playerrect.y=playerrect.y-(150/4)*(hfactor);
            SDL_Delay(75);
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
            count++;
        }
        SDL_FlushEvent(SDL_KEYDOWN);
    }



void player1::punch()
    {
        int count=0;
        for (auto frame:punchframes)
        {
            count++;
            SDL_Rect playerrect=getPlayerRect();
            if (count==3)
            {
                playerrect.w=int(playerrect.w*1.5);
            }
            SDL_Delay(80);
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
        SDL_FlushEvent(SDL_KEYDOWN);
    }



void player1::kick()
    {
        int count=0;
        for (auto frame:kickframes)
        {
            count++;
            SDL_Rect playerrect=getPlayerRect();
            if (count==3)
            {
                playerrect.w=int(playerrect.w*2);
            }
            SDL_Delay(75);
            SDL_RenderCopy(renderer, stage, nullptr, nullptr);
            SDL_RenderCopy(renderer, spritesheet,&frame, &playerrect);
            SDL_RenderPresent(renderer);
        }
        SDL_FlushEvent(SDL_KEYDOWN);
    }
