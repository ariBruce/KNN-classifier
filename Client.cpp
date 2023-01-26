#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Client.hpp"
#include "SocketIO.hpp"
#include "StandardIO.hpp"

using namespace std;


Client::Client(string ip, string port)
{
    this->ip = ip;
    this->port = port;
}

Client::~Client()
{
    delete this->sodio;
    delete this->stadio;
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
    this->sodio = new SocketIO(sock);
    this->stadio = new StandardIO();
    //recive menu
    std::cout << this->sodio->read();
    //send option
    std::string option = this->stadio->read();
    this->sodio->write(option);
    //The options:
    if(option == "1") {
        this->sodio->read(); //request to upload train file path
        std::string path_train = this->stadio->read();
        ifstream file_train(path_train);
        std::string line;
        while(file_train >> line) {
            this->sodio->write(line);
        }
        file_train.close();
        this->sodio->read();//compleation message
        this->sodio->read();//request to upload test file path
        std::string path_test = this->stadio->read();
        ifstream file_test(path_test);
        std::string line2;
        while(file_train >> line2) {
            this->sodio->write(line2);
        }
        file_test.close();
        this->sodio->read(); //compleation message
    }
    if(option == "2") {
        this->sodio->read(); //print the params values of K and calculate type
        this->stadio->read();//takes new params values of K and calculate type
    }
    if(option == "3") {
        this->sodio->read(); //print that the files were classificate or a problen messeage
    }
    if(option == "4") {
        this->sodio->read(); //print the classification
    }      
}