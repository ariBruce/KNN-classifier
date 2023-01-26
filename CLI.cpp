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

    /*
    this->Com1 = Command1(this->dio);
    this->Com2 = Command2(this->dio);
    this->Com3 = Command3(this->dio);
    this->Com4 = Command4(this->dio);
    //this->Com5 = new Command5(dio);
    Command *comPush = &Com1;
    this->allCommands.push_back(comPush);
    comPush = &Com2;
    this->allCommands.push_back(comPush);
    comPush = &Com3;
    this->allCommands.push_back(comPush);
    comPush = &Com4;
    this->allCommands.push_back(comPush);
    //this->allCommands.push_back(Com5);
    */
}

void CLI::start() {
    int choice = 0;
    while (choice != 8) {
        this->dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
        for (int i = 0; i < allCommands.size(); ++i) {
            dio->write(to_string(i) + ". " + allCommands[i]->getDescription());
        }
        choice = atoi(dio->read().c_str());
        if (choice < 1 || choice > 5) {
            continue;
        }
        allCommands.at(choice - 1)->execute();
    }
}

CLI::~CLI() {
}