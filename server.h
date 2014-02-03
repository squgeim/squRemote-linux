/*
 * server.h
 * 
 * Copyright 2014 Shreya Dahal <squgeim@outlook.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

void error(const char *msg) {
	std::cout<<msg<<std::endl;
	exit(1);
}

class server {
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
  
	public:
		server(int);
		~server();
		void on_receive(const char*,int);
		void serve();
};

server::server(int port) {
	int sockoptval=1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(int));
	bzero((char*)&serv_addr, sizeof(serv_addr));
	portno = port;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
}

server::~server() {
	close(newsockfd);
	close(sockfd);
}

void server::serve() {
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	for(;;) {
		while((newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen))<0){}
		bzero(buffer,256);
		int n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		else {
			buffer[n-1]='\0';
			on_receive(buffer,n);
		}
	}
}
