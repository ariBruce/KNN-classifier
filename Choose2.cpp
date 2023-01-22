

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "client.hpp"
#include "Choose2.hpp"
using namespace std;

Choose2::Choose2(Receiver* receiver, int sockID){
    receiver2 = receiver;
    this->receiver2->sock = sockID;
};
Choose2::~Choose2(){};
void Choose2::execute(){
    this->receiver2->Action2();
};
