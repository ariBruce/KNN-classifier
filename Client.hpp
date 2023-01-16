#include <iostream>
#include <string.h>

using namespace std;


class Client{
    public:
    string ip;
    string port;
    Client(string ip, string port);
    ~Client();
    void run();

};