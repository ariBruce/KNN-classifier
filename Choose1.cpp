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

using namespace std;


Choose1::Choose1(Receiver* receiver, int sock){
    receiver1 = receiver;
    sock1 = sock;
    path = "";

}

Choose1::~Choose1(){
    //
};

void Choose1::execute(){
    receiver1->Action1();
};
void Choose1::read_csv(string csv_location){
    //open the file of csv type and throw exception if not
    this->path = csv_location;
    ifstream file(this->path);
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
        //when there are still data in the row
        while (getline(s,word,','))
        {
            if (is_double(word))
            {
                int sent_bytes = send(this->sock1, word.c_str(), word.size() + 1,  0);
                    if(sent_bytes < 0){
                        perror("error sending bytes");
                    }
            }
            else labels = word;
        }
    }
    file.close();
};

bool Choose1::is_double(const std::string& s) {
  std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
  return std::regex_match(s, double_regex);
}
