#include<types.hpp>

class Server
{
private:
    int serverFD = -1;
	int newSocket = -1;
	sockaddr_in address{};

public:
    Server(/* args */);
    ~Server();
    void readFromClient();
    void writeToClient();
};