
#include "Command4.hpp"
using namespace std;


  Command4::Command4(DefaultIO* dio) : Command(dio){
      this ->dio = dio;
      this->Description = "display resualts";
  }

  Command4::~Command4()
  {
  }

  void Command4::execute(){
    std::cout << "8";
    if(this->dio->recived_testing.empty()) {
      this->dio->write("please upload data");
    } else if (this->dio->recived_testing[0].label == "Needs testing") {
      this->dio->write("please classify the data");
    } else {
      std::string classify_string = "";
      for (int i = 0; i <= this -> dio->recived_testing.size(); i++) {
        if (i == this-> dio->recived_testing.size()) {
          std::cout<<"classsss";
          this->dio->write(classify_string);
          this->dio->write("Done.");
        } else {
          std::string new_classify = to_string(i) + " " + this->dio->recived_testing[i].label;
          classify_string = classify_string + "\n" + new_classify;
        }
      }
    }
  }
    