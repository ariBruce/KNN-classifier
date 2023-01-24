
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command2.hpp"
#include "Command.hpp"
using namespace std;


Command2::Command2(DefaultIO* dio) : Command(dio){
    this ->dio = dio;
    this->Description = "algorithem settings";
}

Command2::~Command2()
{
}

void Command2::Validate_algorithem_settings(std::string input) {
    stringstream s(input);
    std::string word;
    int input_members = 0;
    //when there are still data in the row
    while (getline(s,word,' ')) {
        input_members += 1;
        if(input_members > 2) {
            this->dio->k = NULL;
            this->dio->distance_metric = "null";
            this->dio->write('invalid input');
        }
        //check if we get K value
        if (this->is_int(word)) {
            if(stoi(word) > 0){
                this->dio->k = stoi(word);
            }else {
                this->dio->write('invalid value for K');
            }
        //check the type of calculation
        } else if (word == "AUC" || word == "MAN" || word == "CHB" || word == "CAN" || word == "MIN") {
            this->dio->distance_metric = word;
        } else if (!this->is_int(word)){
            this->dio->write('invalid value for K');
        } else {
            this->dio->write('invalid value for metric');
        }
    }
}

void Command2::execute(){
    std::string k = to_string(this->dio->k);
    this->dio->write("The current KNN parameters are: K = " + k + ", distance_metric = " + this->dio->distance_metric);
    Validate_algorithem_settings(this->dio->read());
}