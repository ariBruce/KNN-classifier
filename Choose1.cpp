#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <regex>
#include "Choose1.hpp"
#include "Command.hpp"
#include "Receiver.hpp"
#include "client.hpp"
using namespace std;


Choose1::Choose1(Receiver* receiver, int sockID){
    receiver1 = receiver;
    this->receiver1->sock = sockID;
    path = " ";

}

Choose1::~Choose1()
{
}


void Choose1::execute(){
    this->receiver1->Action1();
};
