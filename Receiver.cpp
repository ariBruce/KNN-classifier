
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

#include <string>
#include <stdlib.h>


#include "Command.hpp"
#include "client.hpp"
#include "Receiver.hpp"
using namespace std;

Receiver::Receiver(int sockID = -1){
    sock = sockID;
};
Receiver::~Receiver(){};

void Receiver::Action1(){
    this->get_train(); //get the path and send it to the server as train data
    this->get_test(); //get the path and send it to the server as test data
};
void Receiver::Action2(){
    this->serverData();
}
void Receiver::Action3(){
    this->classifyCsv();
}
void Receiver::Action4(){

}


void Receiver::readCsv(string csv_location) {
    //open the file of csv type and throw exception if not
    ifstream file(csv_location);
    if(!file)
    {
        throw invalid_argument( "Invalid file location" );
    }
    string labels = "";
    string line, word, s;
    vector<double> tmp;
    int vector_size = 0;

    //put the data from the csv into vector
    //when there are still rows in the csv
    while (file >> line)
    {
        labels = "";
        vector_size = 0;
        stringstream s(line);
        int sent_bytes = 0;
        //when there are still data in the row
        while (getline(s,word,','))
        {
            sent_bytes = send(this->sock, word.c_str(), word.size() + 1,  0);
            if(sent_bytes < 0){
                perror("error sending bytes");
                break;
            }
            if(sent_bytes == 0){
                std::cout<<"Upload complete.";
            };
        };
    };
    file.close();
};

bool Receiver::is_int(const std::string& s) {
  std::regex int_regex("(0|[1-9][0-9]*)");
  return std::regex_match(s, int_regex);
}

bool Receiver::is_metType(const std::string& s){
    if(s=="AUC" || s== "MAN" || s== "CHB" || s== "CAN" || s =="MIN"){
        return true;
    }
    else{
        //do something
    }

}

void Receiver::get_train() {
    std::cout<<"Please upload your local train CSV file.\n";
    string train_file;
    getline(cin, train_file);
    if (train_file == "-1"){
        //return to menu
    }
    this->readCsv(train_file);
};

void Receiver::get_test(){
    std::cout<<"Please upload yo ur local test CSV file.\n";
    string test_file;
    getline(cin, test_file);
    if (test_file == "-1"){
        //return to menu
    }
    this->readCsv(test_file);
};

//for action 2
void Receiver::serverData(){
    char bufferK[4096] = {0};
    char bufferD[4096] = {0};
    //receive the K
    int kRead = read(sock , bufferK, 4096);
    //receive the type of the metric
    int dMetric = read(sock , bufferD, 4096);
    printf("The current KNN parameters are: k =  %s, distance metric = %s\n", bufferK, bufferD);
    string input;
    getline(cin, input);
    if (input.empty()) {
        //return to menu
    } else {
        istringstream iss(input);
        string kVal, metType;
        iss >> kVal >> metType;
        bool kVal_is_int = this->is_int(kVal);
        if (this->is_int(kVal) && this->is_metType(metType))
        {
            send(this->sock , &kVal , sizeof(kVal) , 0 );
            send(this->sock , &metType , sizeof(metType) , 0 );
            //return to menue
        } else {
            if (!this->is_int(kVal) && !this->is_metType(metType))
            {
                printf("invalid value for metric\ninvalid value for K");
                //return to menu
            } else {
                if(!this->is_int(kVal)){
                    printf("invalid value for metric");
                    //return to menue
                } else {
                    printf("invalid value for K");
                    //return to menue
                }
            }            
        }
    }
};

void Receiver::classifyCsv(){
    //check if there are files in the server
    if(true){
        //run the algorithm on the server
        printf("complete data classifying ");
    } else {
        printf("please upload data");
    }
    //return to menu
}
void Receiver::printClassify(){
    //check the situation in the server
    //if there are files and they were classify
    
}
