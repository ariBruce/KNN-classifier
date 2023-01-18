
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

bool Receiver::is_double(const std::string& s) {
  std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
  return std::regex_match(s, double_regex);
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
void Receiver::serverData(){
    char buffer[1024];
    int bytes_received = recv(this->sock, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        // Handle error
    }
    // Parse the request from the client
    string request(buffer, bytes_received);
    if (request == "get_arg_value") {
        // Lookup the value of the argument
        string value = lookup_arg_value();

        // Send the value back to the client
        send(this->sock, value.c_str(), value.size(), 0);
    }

};