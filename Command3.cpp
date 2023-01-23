
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>
#include "DefaultIO.hpp"
#include "Knn.hpp"
#include "Command3.hpp"
#include "Command.hpp"
using namespace std;



Command3::Command3(DefaultIO* dio) : Command(dio){
    this ->dio = dio;
    this->Description = "classify data";
}

Command3::~Command3()
{
}

void Command3::execute(){
if (this->dio->recived_testing.empty() || this->dio->recived_learning.empty() || this->dio->distance_metric == "null") {
    this->dio->write("please upload data");
} else {
    for (int i = 0; i < this -> dio->recived_testing.size(); i++) {
        Knn Knn_calc = Knn(this->dio->k, this->dio->recived_testing[i].points , this->dio->distance_metric);
        //run the algorithm
        Knn_calc.findKnearest(&this->dio->recived_learning);
        this->dio->recived_testing[i].label = Knn_calc.predict();
    }
    this->dio->write("classifying data complete");
}