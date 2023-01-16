#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "client.hpp"
using namespace std;


Client::Client(string ip, string port)
{
    this->ip = ip;
    this->port = port;
}

Client::~Client()
{
}

void Client::run() {
    //check ip and port recived
    //create socket and define variables
    /*const char* this->ip = "127.0.0.1";*/
    /*const int this->port = 54000;*/
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("error creating socket");
    }
    //bind socket to ip address
    sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    inet_pton(AF_INET,this->ip.c_str(), &sin.sin_addr); //input binding information
    sin.sin_port = htons(stoi(this->port));
    if(connect(sock,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting server");
    }
    do {
    //enter line of text
    string userInput;
    getline(cin, userInput);
    //check if client needs to be closed
    if (userInput == "-1"){
        close(sock);
        break;
    }
    //send to server
    int sent_bytes = send(sock, userInput.c_str(), userInput.size() + 1,  0);
    if(sent_bytes < 0){
        perror("error sending bytes");
    }
    //recive input back from server
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    memset(buffer, 0, 4096);
    int read_bytes = recv(sock, buffer, expected_data_len,0);
    if(read_bytes == 0) {
        //conection is closed
    }
    else if(read_bytes < 0) {
        perror("error read bytes");
    }
    else {
       cout << buffer << endl;
    }
    } while(true);  
}