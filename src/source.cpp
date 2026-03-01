#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<system_error>

int main(){
	
	int serverFD;
	struct sockaddr_in address;
	const int PORT = 8000;

	if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		auto ec = std::error_code(errno, std::system_category());
		std::cerr << "failed to open socket" << ec.message() << std::endl;
		return 1;
	}

	return 0;

};
