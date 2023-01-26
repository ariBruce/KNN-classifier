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
    std::cout << "we are sending a menu\n";
    while (choice != 8) {
        this->dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
        for (int i = 0; i < allCommands.size(); ++i) {
            std::cout << "in the loop\n";
            this->dio->write(to_string(i+1) + ". " + allCommands[i]->getDescription() + "\n");
        }
        try {
        int choice = atoi(this->dio->read().c_str());
        } catch(...){
            this->dio->write("invalid input");
        }
        if (choice < 1 || choice > 5) {
            continue;
        }
        allCommands.at(choice - 1)->execute();
    }
}

CLI::~CLI() {
    for (int i = 0; i < allCommands.size(); ++i) {
        delete allCommands[i];
        }
}