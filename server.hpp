#ifndef SERVER_H_
#define SERVER_H_

#include <pthread.h>
#include <thread>
#include "CLI.hpp"
#include "DefaultIO.hpp"


class ClientHandler {
public:
    void handle(int clientID) {
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};

class Server {
    thread *t; // the thread to run the start() method in
    bool stopRun;
    int fd;
    sockaddr_in server;
    sockaddr_in client;

public:
    Server(int port);

    virtual ~Server();

    void start();

    void stop();
};

#endif /*SERVER_H_ */