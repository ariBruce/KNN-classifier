#ifndef Choose5_H_
#define Choose5_H_

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

class Choose5 : Command
{
    public:
    Receiver* receiver4;

    Choose5(Receiver* receiver, int sockID);
    ~Choose5();
    void execute() override;
};


#endif