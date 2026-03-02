#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<system_error>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
	
	int clientFD = -1;
	sockaddr_in address{};
	const int PORT = 8080;

	if((clientFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to open socket" << ec.message() << std::endl;
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	if(inet_pton(AF_INET,"127.0.0.1", &address.sin_addr) <= 0){

		std::cerr << "Invalid address, Address not supported" << std::endl;
		return 1;
	}
	
	socklen_t addrLen = sizeof(address);
	if(connect(clientFD, (sockaddr*)&address, addrLen) < 0){
		
		std::cerr << "Connection Failed !!!!" << std::endl;
		return 1;
	}
	
	std::string helloMsg = "Hello from Client";
	send(clientFD, helloMsg.data(), helloMsg.size(), 0);

	std::cout << "Hello Msg sent" << std::endl;

	std::string buffer(1024,'\0');
	long valRead = read(clientFD, buffer.data(), buffer.size());
	buffer.resize(valRead > 0 ? valRead : 0);

	if(buffer.empty()){
		std::cout << "Nothing to read" << std::endl;
	}

	std::cout << buffer << std::endl;

	return 0;

};
