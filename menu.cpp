/*
*Author:-Pukar Giri
*Created On:-09Th March 2019 at 17:22
*File Name:-menu.cpp
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "menu.h"



void menu::handle_event()
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                            showing= false;
                    }
                case SDL_MOUSEMOTION:
                    for(int index=0;index<buttons.size();index++)
                    {
                        SDL_Point point ={event.motion.x,event.motion.y};
                        if (SDL_PointInRect(&point,&buttons[index]))
                            focus[index]= true;
                        else
                            focus[index]= false;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    clicked(event.button.x,event.button.y);
                    break;
                case SDL_QUIT:
                    showing= false;
                    exit(0);


            }
        }
    }



void menu::display()
    {
        while (showing)
        {
//            cout<<"display called"<<endl;
            handle_event();
            SDL_RenderCopy(renderer, background, nullptr, nullptr);
            switch (current_level)
            {
                case cmain:
                    show_button(1, "New Game");
                    show_button(2, "About authors");
                    show_button(3, "exit");
                    break;
                case cnewgame:
                    show_button(0,"Back");
                    show_button(1, "Multiplayer");
                    show_button(2, "Single Player");
                    break;
                case cmulti:
                    show_button(0,"Back");
                    show_button(1, "Over Lan");
                    show_button(2, "On Single Computer");
                    break;
                case ccolor:
                    show_button(0,"Back");
                    show_button(1, "RED on Right");
                    show_button(2, "BLUE on Left");
                    playerselect();
                    break;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(150);
        }
        return;
    }



menu::menu(SDL_Renderer *renderer)
    {
        this->renderer=renderer;
        buttons.push_back({50,20,100,40});
        buttons.push_back({600,200,300,40});
        buttons.push_back({600,260,300,40});
        buttons.push_back({600,320,300,40});
        buttons.push_back({600,380,300,40});
        buttons.push_back({600,440,300,40});
        focus.push_back(false);
        focus.push_back(false);
        focus.push_back(false);
        focus.push_back(false);
        focus.push_back(false);
        if (TTF_Init()<0) cout<<"to hell with init"<<endl;
        font = TTF_OpenFont("Xanadu.ttf", 25);
        if (font== nullptr)cout<<"Hell  "<< TTF_GetError()<<endl;
        color = { 242, 226, 53 };
        highlight={48, 209, 48};
        SDL_Surface *temp=SDL_LoadBMP("ryu.bmp");
        background=SDL_CreateTextureFromSurface(renderer,temp);
        SDL_FreeSurface(temp);
    }



void menu::show_button(int x, string text)
    {
        SDL_Rect current=buttons[x];
        SDL_Surface * surface = TTF_RenderText_Solid(font,text.c_str(),((focus[x])?highlight:color));
//        cout<<"show button called with text= '"<<text << "' and rect is "<<current.y<<endl;
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        current.x=current.x+(current.w-texW)/2;
        current.y=current.y+(current.h-texH)/2;
        current.w=texW;
        current.h=texH;
        SDL_RenderCopy(renderer, texture, NULL,&current);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }



void menu::playerselect()
    {

    }



void menu::back()
    {
        two_on_one=trace_back.back().two_on_one;
        net=trace_back.back().net;
        single_player=trace_back.back().single_player;
        team_red=trace_back.back().team_red;
        current_level=trace_back.back().currentlevel;
        trace_back.pop_back();
    }



void menu::clicked(int x, int y)
    {
        int inrect=555;
        for(int index=0;index<buttons.size();index++)
        {
            SDL_Point point ={x,y};
            if (SDL_PointInRect(&point,&buttons[index]))
                inrect=index;
        }
        switch (current_level)
        {
            case cmain:
                switch(inrect)
                {
                    case 1 :
                        save_state();
                        current_level=cnewgame;
                        break;
                    case 2:
                        save_state();
                        current_level=cabout;
                        break;
                    case 3:
                        save_state();
                        SDL_Quit();
                        exit(0);
                }
                break;
            case cnewgame:
                switch(inrect)
                {
                    case 0:
                        back();
                        break;
                    case 1 :
                        save_state();
                        single_player= false;
                        current_level=cmulti;
                        break;
                    case 2:
                        save_state();
                        single_player= true;
                        current_level=ccolor;
                        break;
                }
                break;
            case cmulti:
                switch(inrect)
                {
                    case 0:
                        back();
                        break;
                    case 1 :
                        save_state();
                        net= true;
                        two_on_one= false;
                        current_level=ccolor;
                        break;
                    case 2:
                        save_state();
                        net= false;
                        two_on_one= true;
                        current_level=ccolor;
                        break;
                }
                break;
            case ccolor:
                switch(inrect)
                {
                    case 0:
                        back();
                        break;
                    case 1 :
                        team_red= true;
                        showing= false;
//                        save_state();
                        break;
                    case 2:
                        team_red= false;
                        showing= false;
//                        save_state();
                        break;
                }
                break;
        }
    }



void menu::save_state()
    {
        trace_back.push_back({team_red,single_player,net,two_on_one,current_level});
    }
