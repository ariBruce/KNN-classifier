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
#include <thread>

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
            ifstream file_train(path_train);
            //std::string line;
            if (file_train.is_open())
            {
                std::string fileContent((std::istreambuf_iterator<char>(file_train)),
                            std::istreambuf_iterator<char>());
                replace(fileContent.begin(), fileContent.end(), '\n', ',');
                fileContent.insert(0, ",");
                this->sodio->write(fileContent);
            } else {
                std::cout<<"\nfile train didn't open";
                continue;
            }
            file_train.close();
            std::string message = this->sodio->read();//compleation message
            this->stadio->write(message);
            output_1 = this->sodio->read(); //request to upload test file path
            this->stadio->write(output_1);
            std::string path_test = this->stadio->read();
            ifstream file_test(path_test);
            if (file_test.is_open())
            {
                std::string fileContent2((std::istreambuf_iterator<char>(file_test)),
                        std::istreambuf_iterator<char>());
                replace(fileContent2.begin(), fileContent2.end(), '\r', ',');
                fileContent2.erase(std::remove(fileContent2.begin(), fileContent2.end(), '\n'), fileContent2.end());
                fileContent2.insert(0, ",");
                this->sodio->write(fileContent2);
            } else {
                std::cout<<"\nfile test didn't open";
                continue;
            }
            file_test.close();
            message = this->sodio->read();//compleation message
            this->stadio->write(message);
        } else if(option == "2") {
            std::string output_2 = this->sodio->read(); //print the params values of K and calculate type
            this->stadio->write(output_2); //write the output
            std::string new_params = this->stadio->read();//takes new params values of K and calculate type
            this->sodio->write(new_params); //send paramaters  
            if(new_params.empty()){
                continue;
            } else {
            output_2 = this->sodio->read();
            this->stadio->write(output_2);
            }
        } else if(option == "3") {
            std::string output_3_upload = this->sodio->read(); //read that the files were classificate or a problen messeage
            this->stadio->write(output_3_upload); //write the output
        }else if(option == "4") {
            std::string output_4 = this->sodio->read(); //print the classification
            this->stadio->write(output_4);
        } else if(option == "5"){
            Download();
        }else{
            throw invalid_argument("invalid argument");
        }
    }  
}

void Client::Download() {
    std::string classification = this->sodio->read(); //print the classification
    classification = classification.substr(1);
    if(classification == "please upload data" || classification == "please classify the data") {
        this->stadio->write(classification);
        return;
    }
    this->stadio->write("please upload a valid file path");
    std::string file_path = this->stadio->read();
    std::ifstream file(file_path);
    if(file.good()) {
        std::thread downloadThread([&] {
            std::stringstream classification_stream(classification);
            std::string cell;
            int order_number = 1;

            std::ofstream output_file(file_path, std::ios::out);
            if (!output_file.is_open()) {
                this->stadio->write("Failed to open file for writing");
                return;
            }
            
            while (std::getline(classification_stream, cell, ',')) {
                output_file << order_number << " " << cell << "\n";
                order_number++;
            }
            output_file.close();
        });
        downloadThread.detach();
    } else {
        this->stadio->write("invalid input");
    }
}