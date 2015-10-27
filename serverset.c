#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/*Variables*/ 
	int sock;
	struct sockaddr_in server;
	int mysock;
	char buff[1024];
	int rval;
	
	/*Create socket*/
	sock = socket (AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("Failed to create socket");
		exit(1);
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port =htons(1026);
	
	/*call bind*/
	if(bind(sock, (struct sockaddr *)&server, sizeof(server)))
	{
		perror("bind failed");
		exit(1);
	}
	
	/*listen*/
	 listen(sock, 5);
	 
	int val, len, ret;
	len = sizeof(val);
	
	ret = getsockopt(sock, SOL_SOCKET, SO_DONTROUTE, (void *)&val, &len);
	printf("so_dontroute = %d\n", val);
	
	val = 1;
	ret = setsockopt(sock, SOL_SOCKET, SO_DONTROUTE, (void *)&val, sizeof(int) );
	printf("so_dontroute = %d\n\n", val);
	
	int on;
	len = sizeof(on);
	ret = getsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (void *)&val, &len);
	printf("so_keepalive set =%d\n",on);

	on = 1;
	ret = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,(void *) &on, sizeof(on));
	printf("so_keepalive set =%d\n",on);
	printf("on status = %d\n\n",on);	

	return 0;
}
