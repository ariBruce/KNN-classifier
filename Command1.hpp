#ifndef Command1_H_
#define Command1_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command.hpp"


class Command1 : public Command
{
    public:
    Command1(DefaultIO*);
    ~Command1();
    int vector_size_total;
    vector<data_struct> transfer_data(std::string csv_sent);
    void execute();


};

#endif