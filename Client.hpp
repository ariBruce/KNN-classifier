#include <iostream>
#include <string.h>
#include "CLI.hpp"
#include "SocketIO.hpp"
#include "StandardIO.hpp"

using namespace std;


class Client{
    public:
    string ip;
    string port;
    SocketIO *sodio;
    StandardIO *stadio;
    Client(string ip, string port);
    ~Client();
    void run();
    void Download(string file_path, string classification);

};