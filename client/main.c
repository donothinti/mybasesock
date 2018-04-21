/*************************************************************************
    > File Name: main.c
    > Author: yaoxiuwen
    > Mail: xiuwen.yao@ingenic.com
    > Created Time: Sat 21 Apr 2018 10:46:38 AM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <pthread.h>

#define MYPORT 8001
int main(int argc, char **argv)
{
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("193.169.4.179");
	addr.sin_port = htons(MYPORT);

	connect(sock, (struct sockaddr *)&addr, sizeof(addr));
	
	printf("accept success!(%s:%d)\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	
	return 0;
}
