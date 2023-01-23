#ifndef SERVER_H_
#define SERVER_H_

#include <pthread.h>
#include <thread>
#include "CLI.hpp"
#include "DefaultIO.hpp"
#include "SocketIO.hpp"


class ClientHandler {
public:
    void *handle(void *arg) {
        int* p = (int*)arg;
        int clientID = *p;
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};

class Server {
    thread *t; // the thread to run the start() method in
    bool stopRun;
    int sockfd;
    int port;
    sockaddr_in serv_addr;
    sockaddr_in client;
    std::vector<std::thread> thread_vector;

public:
    Server(std::string port);

    virtual ~Server();

    void Start(ClientHandler ch);

    void Stop();

    bool is_int(const std::string& s);

    void Bind();

    void Listen();
};

#endif /*SERVER_H_ */