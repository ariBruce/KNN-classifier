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
        this->dio->write("please upload data\n");
    }else if(this->dio->k == -1){
        std::cout<<"the k = -1";
        this->dio->write("invalid value for K\n");

    } else {
        auto it = this->dio->recived_testing.end();
        std::cout<<"\nthe k is fine ";

        for (int i = 0; i < this->dio->recived_testing.size(); i++) {
            Knn Knn_calc = Knn(this->dio->k, this->dio->recived_testing[i].points , this->dio->distance_metric);
            //run the algorithm
            Knn_calc.findKnearest(&this->dio->recived_learning);
            this->dio->recived_testing[i].label = Knn_calc.predict();
            data_struct temp_struct;
            auto it = std::find_if(this->dio->recived_testing.begin(), this->dio->recived_testing.end(),
                [](const data_struct& ds) { return ds.label == "Needs testing"; });            
        }
        if (it == this->dio->recived_testing.end())
        {
            this->dio->write("classifying data complete\n");
        } else {
            this->dio->write("classifying data failed\n");

        }

    }
}
