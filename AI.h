/*
*Author:-Pukar Giri
*Created On:-21Th December 2018 at 20:49
*File Name:-AI.h
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef DLIBPRAC_AI_H
#define DLIBPRAC_AI_H
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <SDL2/SDL.h>
#include "player.h"

typedef struct{
    action      my_action;
    action      opp_action;
    int         distance;
}state;
//enum action{left,right,up,down,none};
typedef struct{
    state state1;
    action action1;
}state_action_pair;
typedef struct{
   state_action_pair pair;
   float value;
}key_value;
////typedef state_action_pair;

class AI
    {
    public:
        player &self;
        player &opponent;
        std::vector<key_value>q;
        unsigned long long gencount=0;
        unsigned long long no_of_left_choosen=0;
        unsigned long long no_of_right_choosen=0;
        unsigned long long no_of_jump_choosen=0;
        unsigned long long no_of_kick_choosen=0;
        unsigned long long no_of_punch_choosen=0;
        unsigned long long no_of_idle_choosen=0;
        state laststate;
        action lastaction;
        int lastdistance;
        float epsilion;
        float alpha;
        float gamma;
        void setq(state_action_pair pair,float value);
        void dump();
        void load();
        inline state_action_pair  get_state_action_pair(state &state1,action & action1);
    public:
        AI(player &self,player &opp, float epsilion=5, float alpha=0.6, float gamma=0.9);
        inline float getq(state_action_pair pair);
        void learnq(state state1,action action1,float reward,float value);
        action chooseaction(state);
        void learn(state state1,action action1, float reward,state state2);
        state calc_state();
        float calc_reward();
        void drive();

    };




#endif //DLIBPRAC_AI_H
