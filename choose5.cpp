#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "client.hpp"
#include "Choose5.hpp"
using namespace std;

Choose5::Choose5(Receiver* receiver, int sockID){
    receiver5 = receiver;
    this->receiver5->sock = sockID;
};
Choose5::~Choose5(){};
void Choose5::execute(){
    this->receiver5->Action5();
};
