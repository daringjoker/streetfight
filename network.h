/*
*Author:-Pukar Giri
*Created On:-08Th March 2019 at 20:04
*File Name:-network.h
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#ifndef STREETFIGHT_NETWORK_H
#define STREETFIGHT_NETWORK_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string>
#include "player.h"
#include "ipgrab.h"
#include <thread>
#include <sstream>
using namespace std;

class network
    {
    public:
        thread th1 ;
        string opponent_ip;
        player &self;
        player & opponent;
        bool host;
        bool scanning= true;
        network(player &self,player &opponent,bool host=false);
        void respond();
        void scan();
        void handshake();
        void send_state();
        void initialize();


    };

void server(network * self);

#endif //STREETFIGHT_NETWORK_H
