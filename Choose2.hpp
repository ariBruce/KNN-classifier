#ifndef Choose2_H_
#define Choose2_H_

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Command.hpp"
#include "Receiver.hpp"
#include "client.hpp"
using namespace std;

class Choose2 : Command
{
    public:
    Receiver* receiver2;

    Choose2(Receiver* receiver, int sockID);
    ~Choose2();
    void execute() override;
};


#endif