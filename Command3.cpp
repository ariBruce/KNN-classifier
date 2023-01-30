#include "Command3.hpp"

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
    }else if(this->dio->k == -1){
        this->dio->write("invalid input");

    } else {
        for (int i = 0; i < this -> dio->recived_testing.size(); i++) {
            Knn Knn_calc = Knn(this->dio->k, this->dio->recived_testing[i].points , this->dio->distance_metric);
            //run the algorithm
            Knn_calc.findKnearest(&this->dio->recived_learning);
            this->dio->recived_testing[i].label = Knn_calc.predict();
        }
    this->dio->write("classifying data complete");
    }
}
