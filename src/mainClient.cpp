#include "client.hpp"

int main(){

    Client client;
    client.sendToServer();
    client.readFromServer();

    return 0;
}