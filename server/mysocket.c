/*************************************************************************
    > File Name: mysocket.c
    > Author: yaoxiuwen
    > Mail: xiuwen.yao@ingenic.com
    > Created Time: Sat 21 Apr 2018 10:57:15 AM CST
 ************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <string.h>
#include "mysocket.h"

int socket_tcp(char *ip, int port, int listencnt, char *msg)
{
	sprintf(msg, "init...");
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock != 0)
	{
		sprintf(msg, "socket failed!");
		return -1;
	}
	
	struct sockaddr_in addr;
	if(ip == NULL)
	{
		memset(&addr, 0, sizeof(addr));
	}
	else
	{
		addr.sin_addr.s_addr = inet_addr(ip);
	}
	addr.sin_port = htons(port);
	if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		sprintf(msg, "bind failed!");
		return -1;
	}
	
	if(listen(sock, listencnt) != 0)
	{
		sprintf(msg, "listen failed!");
		return -1;
	}
	sprintf(msg, "%s:%d\tlisting...", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	return sock;
}
