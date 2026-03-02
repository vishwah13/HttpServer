#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<system_error>
#include<string>
#include<unistd.h>

int main(){
	
	int serverFD = -1;
	int newSocket = -1;
	sockaddr_in address{};
	const int PORT = 8080;

	if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to open socket" << ec.message() << std::endl;
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	if(bind(serverFD,(sockaddr*)&address,sizeof(address)) < 0){
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to bind" << ec.message() << std::endl;
		return 1;
	}

	if(listen(serverFD, 3) < 0){
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to listen" << ec.message() << std::endl;
		return 1;
	}

	socklen_t addrLen = sizeof(address);

	if((newSocket = accept(serverFD, (sockaddr*)&address, &addrLen )) < 0){

		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "accept failed" << ec.message() << std::endl;
		return 1;
	}

	std::string buffer(1024, '\0');
	long long valRead = read(newSocket, buffer.data(), buffer.size());
	buffer.resize(valRead > 0 ? valRead : 0);

	if(buffer.size() == 0){
		std::cout << "No bytes are there to read" << std::endl;
	}

	std::string helloMsg = "Hello from Server";
	write(newSocket, helloMsg.data(), helloMsg.size());

	close(newSocket);

	return 0;

};
