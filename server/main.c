/*************************************************************************
    > File Name: main.c
    > Author: yaoxiuwen
    > Mail: xiuwen.yao@ingenic.com
    > Created Time: Sat 21 Apr 2018 10:46:38 AM CST
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <pthread.h>

#define MYPORT 8001
int sock;
/*
void *__event_recv(void *arg)
{
	pthread_detach(pthread_self());
	char rbuf[1024];
	struct sockaddr_in addr = *(struct sockaddr_in *)arg;
	int addrlen = sizeof(*arg);
	while(1)
	{
		int len = recvfrom(sock, rbuf, sizeof(rbuf), 0, (struct sockaddr*)arg, addrlen);
		if(len > 0)
		{
			printf("message from (%s:%d):%s\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), rbuf);
		}
	}
	
}
void *__event_send(void *arg)
{

}*/
int main(int argc, char **argv)
{

	sock = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(MYPORT);
	if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		perror("bind failed!");
		return -1;
	}
	
	printf("socket(%s:%d) listing...\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	if(listen(sock, 1) != 0)
	{
		perror("listen failed!");
		return -2;
	}
	
	struct sockaddr_in addr1;
	int addrlen = sizeof(addr1);
	int csock = accept(sock, (struct sockaddr*)&addr1, (socklen_t*)&addrlen);
	if(csock < 0)
	{
		perror("accept failed!");
		return -3;
	}

	printf("accept success!(%s:%d)\n", inet_ntoa(addr1.sin_addr), ntohs(addr1.sin_port));

	char rbuf[1024];
	while(1)
	{
		memset(rbuf, 0, sizeof(rbuf));
		int len = recvfrom(csock, rbuf, sizeof(rbuf), 0, (struct sockaddr*)&addr1, (socklen_t*)&addrlen);
		if(len > 0)
		{
			printf("message from (%s:%d):%s\n", inet_ntoa(addr1.sin_addr), ntohs(addr1.sin_port), rbuf);
		}
		else
		{
			perror("recvfrom failed!");
			return -1;
		}
		len = sendto(csock, rbuf, strlen(rbuf), 0, (struct sockaddr*)&addr1, (socklen_t)addrlen);
		if(len > 0)
		{
			;
		}
		else
		{
			perror("sendto failed!");
			return -1;
		}
	}
	


	/*
	pthread_t pid1, pid2;
	pthread_create(&pid1, NULL, __event_recv, (void *)&addr1);
	pthread_create(&pid2, NULL, __event_send, (void *)&addr1);

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
*/

	close(sock);
	close(csock);
	return 0;
}
