#include "CLI.hpp"
using namespace std;

CLI::CLI(DefaultIO* dio)
{
    this->dio = dio;
    this->allCommands.push_back(new Command1(dio));
    this->allCommands.push_back(new Command2(dio));
    this->allCommands.push_back(new Command3(dio));
    this->allCommands.push_back(new Command4(dio));
    this->allCommands.push_back(new Command5(dio));
}

void CLI::start() {
    int choice = 0;
    while (choice != 8) {
        print_menu();
        std::string input_choice = dio->read();
        try {
            if(input_choice.length() != 1){
                input_choice = input_choice.substr(1);
            }
            choice = stoi(input_choice);
            if (choice < 1 || choice > 5) {
            continue;
            }
            allCommands.at(choice - 1)->execute();
        } catch(...){
            this->dio->write("invalid input");
        }
    }
}

void CLI::print_menu() {
    std::string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
    for (int i = 0; i < allCommands.size(); ++i) {
        menu += (to_string(i+1) + ". " + allCommands[i]->getDescription() + "\n");
    }
    menu += "8. exit\n";
    this->dio->write(menu);
}

CLI::~CLI() {
    for (int i = 0; i < allCommands.size(); ++i) {
        delete allCommands[i];
        }
}