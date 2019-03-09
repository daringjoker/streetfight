/*
*Author:-Pukar Giri
*Created On:-09Th March 2019 at 17:22
*File Name:-menu.h
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef STREETFIGHT_MENU_H
#define STREETFIGHT_MENU_H
#include <string>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
using namespace std;
enum level{cmain,cnewgame,cmulti,ccolor,cabout};
struct menu_state
    {
        bool team_red;
        bool single_player;
        bool net;
        bool two_on_one;
        level currentlevel;
    };

class menu
    {
    private:
        vector<menu_state> trace_back;
        SDL_Texture * background;
        bool showing=true;
        vector<SDL_Rect> buttons;
        vector<bool> focus;
        TTF_Font * font;
        SDL_Color color;
        SDL_Color highlight;
        void handle_event();
        void show_button(int x, string text);
        level current_level=cmain;
        SDL_Renderer *renderer;
        void playerselect();
        void back();
        void save_state();
        void clicked(int x, int y);

    public:
        explicit menu(SDL_Renderer *renderer);
        bool team_red;
        bool single_player;
        bool net;
        bool two_on_one;
        void display();


    };




#endif //STREETFIGHT_MENU_H
