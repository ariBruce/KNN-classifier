
#include "Command2.hpp"

using namespace std;


Command2::Command2(DefaultIO* dio) : Command(dio){
    this ->dio = dio;
    this->Description = "algorithem settings";
}

Command2::~Command2()
{
}

std::string Command2::Validate_algorithem_settings(std::string input) {
    stringstream ss(input);
    std::string word;
    int input_members = 0;
    //when there are still data in the row
    while (getline(ss,word,' ')) {
        input_members += 1;
        if(input_members > 2) {
            return("invalid input in command2");
        } else if (input_members == 1){
            word = word.substr(1);
        }
        //check if we get K value
        if (this->is_int(word)) {
            int new_k;
            new_k = stoi(word);
            if(new_k > 0) {
                this->dio->k = new_k;
            } 
        } else if (word == "AUC" || word == "MAN" || word == "CHB" || word == "CAN" || word == "MIN" ) {
            this->dio->distance_metric = word;
        } else {
            return("invalid input");
        }
    }
    return ("The current KNN parameters are: K = " + to_string(this->dio->k) + ", distance_metric = " + this->dio->distance_metric);
} 
    
void Command2::execute(){
    std::string k = to_string(this->dio->k);
    this->dio->write("The current KNN parameters are: K = " + k + ", distance_metric = " + this->dio->distance_metric);
    std::string user_input = this->dio->read();
    this->dio->write(Validate_algorithem_settings(user_input));
}