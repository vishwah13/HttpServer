#include "server.hpp"

int main(){

    Server server;
    server.readFromClient();
    server.writeToClient();
    
    return 0;
}