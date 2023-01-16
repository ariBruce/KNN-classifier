#ifndef Choose1_H_
#define Choose1_H_

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Command.hpp"
#include "Receiver.hpp"


class Choose1 : Command
{
    public:
        Receiver receiver1;
        int sock1;
        string path;
    Choose1(Receiver*, int);
    ~Choose1();
    void execute() override;
    void read_csv(string csv_location);

}

#endif