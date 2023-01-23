#include <iostream>
#include <string.h>
#include "CLI.hpp"
#include "DefaultIO.hpp"

using namespace std;


class Client{
    public:
    string ip;
    string port;
    Client(string ip, string port);
    ~Client();
    void run();

};