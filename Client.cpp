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
    std::string option;
    while (true)
    {
        //recive menu
        std::cout << this->sodio->read();
        //send option
        option = this->stadio->read();
        this->sodio->write(option);
        //The options:
        if(option == "1") {
            std::string output_1 = this->sodio->read();
            this->stadio->write(output_1);
            //this->sodio->read(); //request to upload train file path
            std::string path_train = this->stadio->read();
            this->sodio->write("\n"); //send the path
            ifstream file_train(path_train);
            std::string line;
            std::cout<< "check good: " <<file_train.good()<<"\n";
            if (file_train.is_open())
            {
                std::string fileContent((std::istreambuf_iterator<char>(file_train)),
                            std::istreambuf_iterator<char>());
                this->stadio->write(fileContent);
                                /*while(file_train >> line) {
                    std::cout<<"\nline: "<<line;
                    this->stadio->write(line);
                }*/
                file_train.close();
                std::string message = this->sodio->read();//compleation message
                this->stadio->write(message);
                //this->sodio->read();//request to upload test file path
                output_1 = this->sodio->read();
                this->stadio->write(output_1);
                std::string path_test = this->stadio->read();
                this->sodio->write("\n"); //send the path
                ifstream file_test(path_test);
                std::string line2;
                if (file_test.is_open())
                {
                    std::string fileContent((std::istreambuf_iterator<char>(file_train)),
                            std::istreambuf_iterator<char>());
                    this->stadio->write(fileContent);
                } else {
                    std::cout<<"\nfile test didn't open";
                }
                
                /*while(file_train >> line2) {
                    this->sodio->write(line2);
                }*/
                file_test.close();
                message = this->sodio->read();//compleation message
                this->stadio->write(message);
            } else {
                std::cout<<"\nfile train didn't open";
            }

        } else if(option == "2") {
            std::string output_2 = this->sodio->read(); //print the params values of K and calculate type
            this->stadio ->write(output_2); //write the output
            std::string new_params = this->stadio->read();//takes new params values of K and calculate type
            this->sodio->write(new_params); //send paramaters
            this->sodio->read(); //recive the new params values of K and calculate type
        } else if(option == "3") {
            std::string output_3_upload = this->sodio->read(); //read that the files were classificate or a problen messeage
            this->stadio->write(output_3_upload); //write the output
        }else if(option == "4") {
            this->sodio->read(); //print the classification
        } else{
            throw invalid_argument("invalid argument");
        }
    }  
}