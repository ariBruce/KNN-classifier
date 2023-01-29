
#include "Command1.hpp"
using namespace std;


Command1::Command1(DefaultIO* dio) : Command(dio){
    this->dio = dio;
    this->Description = "upload an unclassified csv data file";
    this->vector_size_total = 0;
}

Command1::~Command1()
{
}
  
  /*it should be read libe by line and the client should follow the following format
  std::ifstream file(csv_file_path);
  std::string line;
  while (std::getline(file, line)) {
    send(sockfd, line.c_str(), line.length(), 0);
  }
  */

vector<data_struct> Command1::transfer_data(std::string csv_sent, std::string file_type) {
  //the struct we will return with the data
  vector<data_struct> data;
  //the classify
  string labels = "";
  string line, word;
  vector<double> tmp;
  int vector_size = 0;
  int data_size = 0;
  //put the data from the csv into vector
  stringstream ss(csv_sent);
  //when there are still data in the row
  while(getline(ss,word,','))
  {
    data_size = sizeof(ss);
    std::cout<<"\nword: "<<word <<"size: ", data_size;
      if (this->is_double(word) && file_type == "train")
      {
          tmp.push_back(stod(word));
          vector_size++;
      } else if(this->is_double(word) && file_type == "test" && vector_size < this->vector_size_total){
          tmp.push_back(stod(word));
          vector_size++;
      } else if(!(this->is_double(word)) && file_type == "train"){ //will only occur for the training and not the testing file
            labels = word;
            if (this->vector_size_total == 0)
            {
                this->vector_size_total = vector_size;
            }
      } else if(this->vector_size_total == vector_size && file_type == "test") {
          labels = "Needs testing";
      } else{
          throw invalid_argument( "Invalid CSV data!1" );
      }
      if(!(labels== "" || tmp.empty())){
        data_struct temp_struct;
        temp_struct.label = labels;
        temp_struct.points = tmp;
        data.push_back(temp_struct);
        tmp.clear();
        labels = "";
        vector_size = 0;
      }
  }
  if(!data.empty()){
    this->dio->write("Upload complete.\n");
    return data;
  }
  return data;
  //std::cout<<"\nsize data: " << data_size << " word: "<<word;
  //return data;
};

void Command1::execute(){
  this->dio->write("Please upload your local train CSV file.\n");
  std::string the_content = this->dio->read();
  std::cout<< "\npath train: " << the_content;
  this->dio->recived_learning = transfer_data(the_content, "train");
  //this->dio->write("Upload complete.\n");
  if(!(this->dio->recived_learning.empty())) {
    this->dio->write("Please upload your local test CSV file.\n");
    the_content = this->dio->read();
    this->dio->recived_testing = transfer_data(the_content, "test");
    //this->dio->write("Upload complete.\n");
  }

};