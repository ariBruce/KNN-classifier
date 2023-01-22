#ifndef Choose4_H_
#define Choose4_H_

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

class Choose4 : Command
{
    public:
    Receiver* receiver4;

    Choose4(Receiver* receiver, int sockID);
    ~Choose4();
    void execute() override;
};


#endif