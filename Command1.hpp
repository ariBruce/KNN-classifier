#ifndef Command1_H_
#define Command1_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command.hpp"


class Command1 : public Command
{
    int vector_size_total;
    public:
    Command1(DefaultIO*);
    ~Command1();
    vector<data_struct> transfer_data(std::string csv_sent, std::string file_type);
    void execute();
};

#endif