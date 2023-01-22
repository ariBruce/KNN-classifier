vector<data_struct> CLI::read_data(std::string csv_sent) {
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