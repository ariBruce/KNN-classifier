#include "CLI.hpp"
/*#include "Command.hpp"
#include "DefaultIO.hpp"
#include "Command1.hpp"
#include "Command2.hpp"
#include "Command3.hpp"
#include "Command4.hpp"*/
using namespace std;

CLI::CLI(DefaultIO* dio)
{
    this->dio = dio;
    this->allCommands.push_back(new Command1(dio));
    this->allCommands.push_back(new Command2(dio));
    this->allCommands.push_back(new Command3(dio));
    this->allCommands.push_back(new Command4(dio));
}

void CLI::start() {
    int choice = 0;
    while (choice != 8) {
        print_menu();
        try {
        std::string input_choice = dio->read();
        std::cout << input_choice;
        int choice = stoi(input_choice);
        std::cout << choice;
        } catch(...){
            std::cout << "choice\n";
            this->dio->write("invalid input");
        }
        if (choice < 1 || choice > 5) {
            continue;
        }
        std::cout << choice + "\n";
        allCommands[choice - 1]->execute();
    }
}

void CLI::print_menu() {
    std::string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
    for (int i = 0; i < allCommands.size(); ++i) {
        menu = menu + (to_string(i+1) + ". " + allCommands[i]->getDescription() + "\n");
    }
    this->dio->write(menu);
}

CLI::~CLI() {
    for (int i = 0; i < allCommands.size(); ++i) {
        delete allCommands[i];
        }
}