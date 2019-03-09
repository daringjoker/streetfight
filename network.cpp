/*
*Author:-Pukar Giri
*Created On:-08Th March 2019 at 20:04
*File Name:-network.cpp
*Project Name:-streetfight
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "network.h"


 void server(network* self)
    {
        int                response_socket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family              = AF_INET;
        serverAddr.sin_addr.s_addr         = INADDR_ANY;
         if (self->host) serverAddr.sin_port                = htons(2075);
         else serverAddr.sin_port                = htons(2076);
        socklen_t addrlen = sizeof(struct sockaddr_in);
        if (bind(response_socket, (struct sockaddr *) &serverAddr, addrlen) < 0)
        {
            printf("could not bind to the given port.... due to %s\n", strerror(errno));
            //            close(response_socket);
            //            return -1;
        }
        listen(response_socket, 3);
        int  clientsock;
        char msg[1024];
        memset(msg, 0, 1023);
        struct sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        while (true)
        {
            //SDL_Delay(200);
            clientsock = accept(response_socket, (struct sockaddr *) &clientaddr, (socklen_t *) &addrlen);
            if (clientsock < 0)
            {
                printf("receiving socket failed due to %s ... %d \n ", strerror(errno), errno);
                break;
                //                close(response_socket);
                //                return -1;
            }
            ssize_t len;
            if ((len = read(clientsock ,msg, 1000)) > 0)
            {
                //send(clientsock, msg, 1024, 0);
                msg[len]='\0';
                //puts(msg);
                string handshake="handshake initialized";
                string message=string(msg);
                if (message==handshake&&self->scanning)
                {
                    self->scanning= false;
                    self->opponent_ip=string(inet_ntoa(clientaddr.sin_addr));
                    send(clientsock,handshake.c_str(),handshake.length(), 0 );
                    cout<<"handshake complete from client"<<endl;

                }
                else
                {
                    stringstream messagestream(message);
                    messagestream>>self->self.x;
                    messagestream>>self->self.frame_count;
                    int actn;
                    messagestream>>actn;
                    self->self.current_action=action(actn);
                    messagestream>>self->self.health;
                    int notd;
                    messagestream>>notd;
                    self->self.noted=(notd==1);
//                    cout<<self->self.x<<endl;
//                    cout<<self->self.frame_count<<endl;
//                    cout<<self->self.current_action<<endl;
//                    cout<<self->self.health<<endl;
//                    cout<<self->self.noted<<endl;
                }
            }
            else
            {
                printf("could not receive due to ...%s \n", strerror(errno));
                break;
            }
        }
    }



network::network(player& self, player& opponent, bool host):
self{self},opponent{opponent},host{host}
    {
        th1=std::thread(server,this);
        if (host)
        {
            respond();
        }
        else
        {
            scan();
        }
        cout<<"opponents ip is "<<opponent_ip<<endl;
        cout<<"i am standing towards "<<(opponent.left?"left":"right")<<endl;
    }



void network::scan()
    {
        struct ip ipaddr          = getip();
        int       sock            = socket(AF_INET, SOCK_DGRAM, 0);
        int       enableBroadcast = 1;
        setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &enableBroadcast, sizeof(enableBroadcast));
        struct sockaddr_in saddr;
        memset(&saddr, 0, sizeof(saddr));
        //cout<<"socket address created"<<endl;
        saddr.sin_family = AF_INET;
        inet_pton(AF_INET, ipaddr.broadcast, &saddr.sin_addr.s_addr);
        saddr.sin_port = htons(2070);
        while (scanning)
        {
            sendto(sock, ipaddr.local, sizeof(ipaddr.local), 0, (struct sockaddr *) &saddr, sizeof(saddr));
            sleep(1);
        }
        cout<<"client has completed the scan processs"<<endl;
        close(sock);
    }



void network::send_state()
    {
        int                response_socket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family              = AF_INET;
        inet_pton(AF_INET,opponent_ip.c_str(), &serverAddr.sin_addr.s_addr);
        //inet_aton(opponent_ip.c_str(),&(serverAddr.sin_addr));
        if (host) serverAddr.sin_port                = htons(2076);
        else serverAddr.sin_port                = htons(2075);
        socklen_t addrlen = sizeof(struct sockaddr_in);
        if (connect(response_socket, (struct sockaddr *)&serverAddr,addrlen) < 0)
        {
            printf("\nConnection Failed \n");
        }
        stringstream messagestream;
        system("clear");
        messagestream<<opponent.x<<endl;
        messagestream<<opponent.frame_count<<endl;
        messagestream<<opponent.current_action<<endl;
        messagestream<<opponent.health<<endl;
        messagestream<<((opponent.noted)?1:0)<<endl;
        string message(messagestream.str());
        send(response_socket,message.c_str(),message.length(), 0 );
        close(response_socket);
    }



void network::receive()
    {

    }



void network::drive()
    {

    }



void network::respond()
    {
        int                response_socket = socket(AF_INET, SOCK_DGRAM, 0);
        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family              = AF_INET;
        serverAddr.sin_addr.s_addr         = INADDR_ANY;
        serverAddr.sin_port                = htons(2070);
        socklen_t addrlen = sizeof(struct sockaddr_in);
        if (bind(response_socket, (struct sockaddr *) &serverAddr, addrlen) < 0)
        {
            printf("could not bind to the given port.... due to %s\n", strerror(errno));
            //            close(response_socket);
            //            return -1;
        }
        listen(response_socket, 3);
        int  clientsock;
        char msg[1024];
        memset(msg, 0, 1000);
        struct sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        while (scanning)
        {
            ssize_t numbytes;
            if ((numbytes = recvfrom(response_socket, msg, 1023 , 0,
                                     (struct sockaddr *)&clientaddr, &addrlen)) == -1) {
                perror("recvfrom");
                exit(1);
            }
            opponent_ip=string(inet_ntoa(clientaddr.sin_addr));
            cout<<"got packet from "<<opponent_ip<<endl;
            printf("packet is %d bytes long\n",numbytes);
            msg[numbytes] = '\0';
            printf("packet contains \"%s\"\n",msg);
            handshake();
        }
        close(response_socket);
        cout <<"host has responded well and completely"<<endl;
    }



void network::handshake()
    {
        int                response_socket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family              = AF_INET;
        inet_pton(AF_INET,opponent_ip.c_str(), &serverAddr.sin_addr.s_addr);
        //inet_aton(opponent_ip.c_str(),&(serverAddr.sin_addr));
        if (host) serverAddr.sin_port                = htons(2076);
        else serverAddr.sin_port                = htons(2075);
        socklen_t addrlen = sizeof(struct sockaddr_in);
        if (connect(response_socket, (struct sockaddr *)&serverAddr,addrlen) < 0)
        {
            printf("\nConnection Failed \n");
        }
        string handshake="handshake initialized";
        send(response_socket,handshake.c_str(),handshake.length(), 0 );
        char msg[1024];
        ssize_t len=read( response_socket ,msg, 1000);
        cout<<"handshake len: "<<len<<endl;
        msg[len]='\0';
        if (string(msg)==handshake)
        {
            scanning= false;
        }
        cout<<"handshake complete from host"<<endl;
        close(response_socket);
    }
