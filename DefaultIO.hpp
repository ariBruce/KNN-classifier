class DefaultIO {
protected:
    ofstream out;
    ifstream in;
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

};

class StandardIO : public DefaultIO {

public:
    StandardIO(string inputFile, string outputFile) {
        in.open(inputFile);
        out.open(outputFile);
    }

    string read() {
        string str;
        in >> str;
        return str;
    }

    void write(string text) {
        out << text;
    }

    void write(float f) {
        out << f;
    }

    void read(float *f) {
        in >> *f;
    }
};

class SocketIO : public DefaultIO {
    int userID;
public:
    SocketIO(int userID) {
        this->userID = userID;
    }

    virtual string read() {
        string serverInput = "";
        char c = 0;
        int n = recv(userID, &c, sizeof(char), 0);
        if (n < 0) {
        std::cerr << "ERROR reading from socket" << std::endl;
        exit(1);
        }
        while (c != '\n') {
            serverInput += c;
            n = recv(userID, &c, sizeof(char), 0);
            if (n < 0) {
                std::cerr << "ERROR reading from socket" << std::endl;
                exit(1);
            }
        }
        return serverInput;
    }

    virtual void write(string text) {
    //send data to client
    int n = send(userID, text.c_str(), text.size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
    }

    virtual void write(float f) {
    //send data to client
    int n = send(userID, to_string(f).c_str(), to_string(f).size() + 1, 0);
    if (n < 0) {
      std::cerr << "ERROR: writing to socket" << std::endl;
      exit(1);
    }
    }

    virtual void read(float *f) {
    }
};