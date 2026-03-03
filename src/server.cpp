#include "server.hpp"

Server::Server(/* args */)
{
	if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to open socket" << ec.message() << std::endl;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	if(bind(serverFD,(sockaddr*)&address,sizeof(address)) < 0){
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to bind" << ec.message() << std::endl;
	}

	if(listen(serverFD, 3) < 0){
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to listen" << ec.message() << std::endl;
	}

	socklen_t addrLen = sizeof(address);

	if((newSocket = accept(serverFD, (sockaddr*)&address, &addrLen )) < 0){

		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "accept failed" << ec.message() << std::endl;
	}
}

Server::~Server()
{
	close(newSocket);
	close(serverFD);
}

void Server::readFromClient()
{
	std::string buffer(1024, '\0');
	long long valRead = read(newSocket, buffer.data(), buffer.size());
	buffer.resize(valRead > 0 ? valRead : 0);

	if(buffer.empty()){
		std::cout << "No bytes are there to read" << std::endl;
	}
	else{
		std::cout << buffer << std::endl;
	}
}

void Server::writeToClient()
{
	std::string helloMsg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	write(newSocket, helloMsg.data(), helloMsg.size());
	std::cout << "Hello Msg sent" << std::endl;
}
