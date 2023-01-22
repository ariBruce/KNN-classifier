#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "client.hpp"
#include "Choose4.hpp"
using namespace std;

Choose4::Choose4(Receiver* receiver, int sockID){
    receiver4 = receiver;
    this->receiver4->sock = sockID;
};
Choose4::~Choose4(){};
void Choose4::execute(){
    this->receiver4->Action4();
};
