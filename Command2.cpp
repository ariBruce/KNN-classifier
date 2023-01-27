
#include "Command2.hpp"

using namespace std;


Command2::Command2(DefaultIO* dio) : Command(dio){
    this ->dio = dio;
    this->Description = "algorithem settings";
}

Command2::~Command2()
{
}

void Command2::Validate_algorithem_settings(std::string input) {
    stringstream ss(input);
    std::string word;
    int input_members = 0;
    std::regex int_regex("^[0-9]?$");
    //when there are still data in the row
    while (getline(ss,word,' ')) {
        std::cout << word + "\n";
        input_members += 1;
        if(input_members > 2) {
            this->dio->write("invalid input");
            return;
        }
        //check if we get K value
        if (std::regex_match(word, int_regex)) {
            int new_k;
            if(this->is_int(word)){
                new_k = stoi(word);
                std::cout <<"this is the new k: " <<new_k;
            }
            if(new_k > 0) {
                this->dio->k = new_k;
                std::cout << "is_int good\n";
            } else {
                std::cout << "is_int problem\n";
                this->dio->write("invalid value for K");
                return;
            }
        //check the type of calculation
        } else if (word == "AUC" || word == "MAN" || word == "CHB" || word == "CAN" || word == "MIN" ) {
            this->dio->distance_metric = word;
        } else if (!std::regex_match(word, int_regex)){
            std::cout << "is_int is false\n";
            this->dio->write("invalid value for K");
            return;
        } else {
            std::cout << "is_int problem\n";
            this->dio->write("invalid value for metric");
            return;
        }
    }
    this->dio->write("The current KNN parameters are: K = " + to_string(this->dio->k) + ", distance_metric = " + this->dio->distance_metric + "\n");
}

void Command2::execute(){
    std::string k = to_string(this->dio->k);
    this->dio->write("The current KNN parameters are: K = " + k + ", distance_metric = " + this->dio->distance_metric + "\n");
    std::string user_input = this->dio->read();
    Validate_algorithem_settings(user_input);
}