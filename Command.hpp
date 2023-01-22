#ifndef Command_H_
#define Command_H_

class Command {
  protected:
    DefaultIO *dio;
    string Description = "empty";  //description of the command in the menu.
    string down = "\n";
  public:
    Command(DefaultIO* dio):dio(dio){}

    virtual void execute() = 0;

    string getDescription() {
      return this->commandDescrip;
    }

    virtual ~Command() {}
};

class Command1 : public Command {
  Command1(DefaultIO* dio){
      this ->dio = dio;
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

  void execute(){
      this->dio.write("Please upload your local train CSV file.");
      this->dio.csv_recived_learning = this->dio.read();
      this->dio.write("Upload complete.");
      this->dio.write("Please upload your local test CSV file.");
      this->dio.csv_recived_learning = this->dio.read();
      this->dio.write("Upload complete.");
  }

};

#endif