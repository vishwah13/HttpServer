#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
	
	int serverFD;
	struct sockaddr_in address;
	const int PORT = 8000;

	if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		
		perror("cannot create socket");
		return 0;
	}

	return 0;

};
