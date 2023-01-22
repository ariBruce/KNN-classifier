#ifndef Command_H_
#define Command_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include "Knn.hpp"

class Command {
  protected:
    DefaultIO *dio;
    std::string Description = "empty";  //description of the command in the menu.
    std::string down = "\n";
  public:
    Command(DefaultIO* dio){
      this ->dio = dio;
    }

    virtual void execute() = 0;

    string getDescription() {
      return this->Description;
    }

    virtual ~Command() {}
};

class Command1 : public Command {
  Command1(DefaultIO* dio){
      this->dio = dio;
      this->Description = "upload an unclassified csv data file";
  }

  ~Command1()
  {
  }
    
    /*it should be read libe by line and the client should follow the following format
    std::ifstream file(csv_file_path);
    std::string line;
    while (std::getline(file, line)) {
      send(sockfd, line.c_str(), line.length(), 0);
    }
    */

  vector<data_struct> transfer_data(std::string csv_sent) {
    //the struct we will return with the data
    vector<data_struct> data;
    //the classify
    string labels = "";
    string line, word, s;
    vector<double> tmp;
    int vector_size = 0;
    //put the data from the csv into vector
    stringstream s(csv_sent);
    //when there are still data in the row
    while (getline(s,word,','))
    {
        if (is_double(word))
        {
            tmp.push_back(stod(word));
            vector_size++;
            if (this->vector_size_total != 0 && vector_size == this->vector_size_total)
            {
                lables = "Needs testing";
            }
        }
        else { //will only occur for the training and not the testing file
            labels = word;
            if (this->vector_size_total == 0)
            {
                this->vector_size_total = vector_size;
            }
            //put the label and the pasrameters in the vector
            if ((labels == "") || (vector_size != this->vector_size_total))
            {
                throw invalid_argument( "Invalid CSV data!" );
            } 
        }
            data_struct temp_struct;
            temp_struct.label = labels;
            temp_struct.points = tmp;
            data.push_back(temp_struct);
            tmp.clear();
            labels = "";
            vector_size = 0;
    }
    return data;
  }

  void execute(){
    this->dio.write("Please upload your local train CSV file.");
    this->dio.recived_learning = transfer_data(this->dio.read());
    this->dio.write("Upload complete.");
    this->dio.write("Please upload your local test CSV file.");
    this->dio.recived_testing = transfer_data(this->dio.read());
    this->dio.write("Upload complete.");
  }

};

class Command2 : public Command {
  Command2(DefaultIO* dio){
      this ->dio = dio;
      this->Description = "algorithem settings";
  }

  ~Command2()
  {
  }

  void Validate_algorithem_settings(std::string input) {
    stringstream s(input);
    //when there are still data in the row
    while (getline(s,word,' ')) {
      if (is_int(word)) {
        this -> dio.k = stoi(word);
      } else if (word == "AUC" || word == "MAN" || word == "CHB" || word == "CAN" || word == "MIN") {
        this->dio.distance_metric = word;
      } else if (!is_int(word) || stoi(word) < 0){
          std::string error_message = 'invalid value for K';
          int n = send(this->dio.userID, error_message.c_str(), error_message.size() + 1, 0);
          if (n < 0) {
            std::cerr << "ERROR: writing to socket" << std::endl;
            exit(1);
          }
      } else {
          std::string error_message = 'invalid value for metric';
          int n = send(this->dio.userID, error_message.c_str(), error_message.size() + 1, 0);
          if (n < 0) {
            std::cerr << "ERROR: writing to socket" << std::endl;
            exit(1);
          }
        }
    }
  }

  void execute(){
    std::string k = to_string(this->dio.k);
    this->dio.write("The current KNN parameters are: K = " + k + ", distance_metric = " + this->dio.distance_metric);
    Validate_algorithem_settings(this->dio.read());
  }

};

class Command3 : public Command {
  Command3(DefaultIO* dio){
      this ->dio = dio;
      this->Description = "classify data";
  }

  ~Command3()
  {
  }

  void execute(){
    if (this->dio.recived_testing.empty() || this->dio.recived_learning.empty()) {
      this->dio.write("please upload data");
    } else {
        for (int i = 0; i < this -> recived_testing.size(); i++) {
        Knn Knn_calc = Knn(this -> k, this -> recived_testing.points , this -> calculation_method);
        //run the algorithm
        Knn_calc.findKnearest(&classified_data);
        this -> recived_testing[i].label = Knn_calc.predict();
        }
        this->dio.write("classifying data complete");
    }
  }

};

class Command4 : public Command {
  Command4(DefaultIO* dio){
      this ->dio = dio;
      this->Description = "classify data";
  }

  ~Command4()
  {
  }

  void execute(){
    if(this -> dio.recived_testing.empty()) {
      this->dio.write("please upload data");
    } else if (this -> recived_testing[0].label == "Needs testing") {
      this->dio.write("please classify the data");
    } else {
      for (int i = 0; i =< this -> recived_testing.size(); i++) {
        if (i == this -> recived_testing.size()) {
          to_print.append("Done.", 7)
        } else {
          this->dio.write(to_string(i) + " " + recived_testing[i].label);
        }
      }
    }
  }
  
};
#endif