/*
*Author:-Pukar Giri
*Created On:-07Th February 2019 at 17:46
*File Name:-player.cpp
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "player.h"



player::player(SDL_Renderer *renderer,bool lt)
    {
        left=lt;
        this->renderer=renderer;
        //loading the spritesheet
        SDL_Surface *temp=SDL_LoadBMP("fighter.bmp");
        this->spritesheet=SDL_CreateTextureFromSurface(renderer,temp);
        SDL_FreeSurface(temp);
        if (left)
        {
            x=0;
            SDL_SetTextureColorMod(spritesheet,0,0,255);
            SDL_SetTextureAlphaMod(spritesheet,255);
            flip=SDL_FLIP_NONE;
        }else
        {
            x=900;
            SDL_SetTextureColorMod(spritesheet,255,0,0);
            SDL_SetTextureAlphaMod(spritesheet,255);
            flip=SDL_FLIP_HORIZONTAL;
        }
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
        //initializing the punch animation frames
        punchframes.push_back({253, 269, 60, 94});
        punchframes.push_back({333, 268, 74, 95});
        punchframes.push_back({432, 268, 108, 94});
        punchframes.push_back({333, 268, 74, 95});
        punchframes.push_back({253, 269, 60, 94});
        //initializing the  kick animation frames
        kickframes.push_back({606, 269, 60, 94});
        kickframes.push_back({689, 267, 66, 92});
        kickframes.push_back({777, 256, 114, 94});
        kickframes.push_back({689, 267, 66, 92});
        kickframes.push_back({606, 269, 60, 94});
        //initializing the  jump animation frames
        jumpframes.push_back({17, 847, 55, 85});
        jumpframes.push_back({100, 823, 56, 104});
        jumpframes.push_back({176, 805, 50, 89});
        jumpframes.push_back({251, 798, 54, 79});
        jumpframes.push_back({327, 813, 48, 70});
        jumpframes.push_back({397, 810, 48, 89});
        jumpframes.push_back({464, 819, 55, 109});
        jumpframes.push_back({17, 847, 55, 85});
    }



void player::_walkf()
    {
        SDL_Rect frame=forwardframes[frame_count];
        SDL_Rect playerrect=getPlayerRect();
            x=x+10;
            render(&frame, &playerrect);
        //SDL_FlushEvent(SDL_KEYDOWN);
    }



SDL_Rect player::getPlayerRect()
    {

        if (x<=0)x=0;
        if (x>900)x=900;
        SDL_Rect playerrect={x,y,100,200};
        if (frame_count==2&&current_action==ckick)
        {
            if (left)
            {
                playerrect.w=int(playerrect.w*2);

            }
            else{
                playerrect.x=playerrect.x-int(playerrect.w);
                playerrect.w=int(playerrect.w*2);
            }
        }
        if (current_action==cjump)
        {
            int hfactor = 0;
            if (frame_count <= 4 )
            {
                hfactor = frame_count;
            }
            else
            {
                hfactor = 8 - frame_count;
            }
            playerrect.y=playerrect.y-(170/4)*(hfactor);
            playerrect.h=playerrect.h-(50/4)*(hfactor);
        }
        if (frame_count==2&&current_action==cpunch)
        {
            if (left)playerrect.w=int(playerrect.w*1.5);
            else{
                playerrect.x=playerrect.x-int(0.5*playerrect.w);
                playerrect.w=int(playerrect.w*1.5);
            }
            SDL_Delay(80);
        }
        return playerrect;
    }



void player::_walkb()
    {
        SDL_Rect frame=backwardframes[frame_count];
        SDL_Rect playerrect=getPlayerRect();
        x=x-10;
        render(&frame, &playerrect);
        //SDL_FlushEvent(SDL_KEYDOWN);
    }



void player::_idle()
    {
        SDL_Rect frame=idleframes[frame_count];
        SDL_Rect playerrect=getPlayerRect();
        SDL_Delay(30);
        render(&frame, &playerrect);
        //SDL_FlushEvent(SDL_KEYDOWN);
    }



void player::_jump()
    {
        SDL_Rect frame=jumpframes[frame_count];
        SDL_Rect playerrect=getPlayerRect();
        SDL_Delay(30);
        render(&frame, &playerrect);
        //SDL_FlushEvent(SDL_KEYDOWN);
    }



void player::_punch()
    {

        SDL_Rect frame=punchframes[frame_count];
        SDL_Rect playerrect=getPlayerRect();
        render(&frame, &playerrect);
        //SDL_FlushEvent(SDL_KEYDOWN);
    }



void player::_kick()
    {
        SDL_Rect frame=kickframes[frame_count];
        SDL_Rect playerrect=getPlayerRect();
        SDL_Delay(60);
        render(&frame, &playerrect);
    }



void player::render(SDL_Rect* source, SDL_Rect* dest)
    {

        SDL_Rect healthrect={x,dest->y-25,100,10};
        if (left) SDL_SetRenderDrawColor(renderer,0,0,255,50);
        else SDL_SetRenderDrawColor(renderer,255,0,0,50);
        SDL_RenderDrawRect(renderer,&healthrect);
        healthrect.w=int(health);
        if (this->health>=0)SDL_RenderFillRect(renderer,&healthrect);
        SDL_RenderCopyEx(renderer, spritesheet,source, dest,0,NULL,flip);
    }



void player::update()
    {

        switch(current_action)
        {
            case cwalkb:
                if (frame_count>=backwardframes.size())idle();
                _walkb();
                break;
            case cwalkf:
                if (frame_count>=forwardframes.size())idle();
                _walkf();
                break;
            case cjump:
                if (frame_count>=jumpframes.size())idle();
                _jump();
                break;
            case ckick:
                if (frame_count>=kickframes.size())idle();
                _kick();
                break;
            case cpunch:
                if (frame_count>=punchframes.size())idle();
                _punch();
                break;
            default:
                if (frame_count>=idleframes.size())idle();
                _idle();
                break;
        }
        if (has_hit()&&!noted)
        {
            noted= true;
            opponent->health-=5*0.01*this->strength;
//            cout<<"HIT"<<frame_count<<endl;
        }
//        if (this->health<100&&health>=20)health+=3*0.001*(100-health);
        frame_count++;
    }



void player::walkf()
    {
        if (current_action==cidle)
        {
            noted=false;
            current_action = cwalkf;
            frame_count = 0;
        }
    }



void player::walkb()
    {
        //opponent->walkf();
        if (current_action==cidle)
        {
            noted=false;
            current_action = cwalkb;
            frame_count = 0;
        }
    }



void player::idle()
    {
            noted=false;
            current_action = cidle;
            frame_count = 0;
    }



void player::jump()
    {
        if (current_action==cidle||current_action==cwalkb||current_action==cwalkf)
        {
            noted=false;
            current_action = cjump;
            frame_count = 0;
        }
    }



void player::kick()
    {
        if (current_action==cidle||current_action==cwalkb||current_action==cwalkf)
        {
            noted=false;
            current_action = ckick;
            frame_count = 0;
        }
    }



void player::punch()
    {
        if (current_action==cidle||current_action==cwalkb||current_action==cwalkf)
        {
            noted=false;
            current_action = cpunch;
            frame_count = 0;
        }
    }



void player::set_opponent(player *opp)
    {
        opponent=opp;
    }



bool player::has_hit()
    {
        if (current_action==ckick||current_action==cpunch)
        {

                SDL_Rect selfrect, opprect, temp;
                selfrect = this->getPlayerRect();
                opprect  = opponent->getPlayerRect();
                bool hit =SDL_IntersectRect(&selfrect, &opprect, &temp);
                if(left)
                {
                    if(this->x>=opponent->x||temp.w>70)return false;
                    else return hit;
                }
                else
                {
                    if(this->x<=opponent->x||temp.w>70)return false;
                    else return hit;
                }
        }
        else return false;
    }





