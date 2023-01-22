
#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    this->Com1 = new Command1(dio);
    this->Com2 = new Command2(dio);
    this->Com3 = new Command3(dio);
    this->Com4 = new Command4(dio);
    //this->Com5 = new Command5(dio);
    this->allCommands.push_back(Com1);
    this->allCommands.push_back(Com2);
    this->allCommands.push_back(Com3);
    this->allCommands.push_back(Com4);
    //this->allCommands.push_back(Com5);
}

void CLI::start() {
    int choice = 0;
    while (choice != 8) {
        dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
        for (int i = 0; i < allCommands.size(); ++i) {
            dio->write(allCommands[i]->getDescription());
        }
        choice = atoi(dio->read().c_str());
        if (choice < 1 || choice > 5) {
            continue;
        }
        allCommands.at(choice - 1)->execute();
    }
}

CLI::~CLI() {
    delete Com1;
    delete Com2;
    delete Com3;
    delete Com4;
    //delete Com5;
}