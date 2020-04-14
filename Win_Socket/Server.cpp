#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using std::cin;
#pragma comment (lib,"ws2_32.lib")

enum CMD
{
	CMD_LOGIN,
	CMD_LOGIN_RESULT,
	CMD_LOGINOUT,
	CMD_LOGINOUT_RESULT,
	CMD_NEW_USER_JOIN,
	CMD_ERROR
};


//head
struct Header
{
	short lendata;
	short cmd;
};

//login
struct Login :public Header
{
	Login()
	{
		lendata = sizeof(Login);
		cmd = CMD_LOGIN;
	}
	char usrname[20];
	char password[20];
};

//login result
struct LoginResult :public Header
{
	LoginResult()
	{
		lendata = sizeof(LoginResult);
		cmd = CMD_LOGIN_RESULT;
		result = 0;
	}
	int result;
};

//login out
struct LoginOut :public Header
{
	LoginOut()
	{
		lendata = sizeof(LoginOut);
		cmd = CMD_LOGINOUT;
	}
	char usrname[20];
};

//login out result
struct LoginOutResult :public Header
{
	LoginOutResult()
	{
		lendata = sizeof(LoginOutResult);
		cmd = CMD_LOGINOUT_RESULT;
		result = 0;
	}
	int result;
};

struct NewUserJoin :public Header
{
	NewUserJoin()
	{
		lendata = sizeof(NewUserJoin);
		cmd = CMD_LOGINOUT_RESULT;
		result = 0;
	}
	int result;
};


int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(ver, &data);

	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (INVALID_SOCKET == client)
	{
		printf("client create fault!\n");
	}

	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(40000);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int ret=connect(client, (sockaddr*)&_sin, sizeof(_sin));


	if (SOCKET_ERROR == client)
	{
		printf("connect fault!\n");
	}
	else
	{
		printf("connect success!\n");
	}

	char recvbuffer[128] = {};
	while (true)
	{
		fd_set fd_read;
		FD_ZERO(&fd_read);
		FD_SET(client, &fd_read);


		int ret=select(client, &fd_read, 0, 0, 0);

		if (ret<0)
		{
			printf("select finish\n");
			break;
		}

		if (FD_ISSET(client,&fd_read))
		{
			FD_CLR(client, &fd_read);
		}
		
		if (0==strcmp(cmdbuffer,"exit"))
		{
			break;
		}
		else if(0 == strcmp(cmdbuffer, "login"))
		{
			//发送数据
			Login login;
			strcpy(login.usrname, "admin");
			strcpy(login.password, "admin");
			send(client, (char*)&login, sizeof(login), 0);
			//接收返回数据
			LoginResult res = {};
			recv(client, (char*)&res, sizeof(res), 0);
			printf("res:%d\n", res.result);
		}
		else if (0 == strcmp(cmdbuffer, "logout"))
		{
			//发送数据
			LoginOut loginout;
			strcpy(loginout.usrname, "admin");
			send(client, (char*)&loginout, sizeof(loginout), 0);
			//接收返回数据
			LoginOutResult res = {};
			recv(client, (char*)&res, sizeof(res), 0);
			printf("res:%d\n", res.result);

		}
		else 
		{
			printf("不支持命令,请重新输入\n");
		}
		
	}

	closesocket(client);

	WSACleanup();

	system("pause");
	return 0;
}
