/*
*Author:-Pukar Giri
*Created On:-09Th March 2019 at 10:36
*File Name:-ipgrab.h
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef STREETFIGHT_IPGRAB_H
#define STREETFIGHT_IPGRAB_H


#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <regex.h>


struct ip
    {
        char local[16];
        char broadcast[16];
    };
char *match(char *pattern, char *text);
struct ip getip();


#endif //STREETFIGHT_IPGRAB_H
