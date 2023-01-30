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
    while (getline(ss,word,' ')) {
        input_members += 1;
        if(input_members > 2) {
            return("invalid input");
        }
        //check if we get K value
        if (this->is_int(word)) {
            int new_k;
            new_k = stoi(word);
            if(new_k > 0) {
                this->dio->k = new_k;
            } 
        } else if ((word == "AUC" || word == "MAN" || word == "CHB" || word == "CAN" || word == "MIN") && (input_members == 2)) {
            this->dio->distance_metric = word;
        } else{
            return("invalid input");
        }
    }
    return("");

    //return ("The current KNN parameters are: K = " + to_string(this->dio->k) + ", distance_metric = " + this->dio->distance_metric);
} 
    
void Command2::execute(){
    std::string k = to_string(this->dio->k);
    this->dio->write("The current KNN parameters are: K = " + k + ", distance_metric = " + this->dio->distance_metric);
    std::string user_input = this->dio->read();
    user_input = user_input.substr(1);
    if(user_input.empty()){
        return;
    }
    std::string output= this->Validate_algorithem_settings(user_input);
    this->dio->write(output);
}