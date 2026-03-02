#include<types.hpp>

class Client {

    private:
        int clientFD = -1;
	    sockaddr_in address{};
    public:
        Client(/* args */);
        ~Client();
        void sendToServer();
        void readFromServer();
};