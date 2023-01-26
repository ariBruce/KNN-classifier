#include "ClientHandler.hpp"

void ClientHandler::handle(void *arg){
            int* p = (int*)arg;
        int clientID = *p;
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
}