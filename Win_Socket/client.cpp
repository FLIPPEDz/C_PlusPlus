#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <thread>

using std::thread;
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
		cmd = CMD_NEW_USER_JOIN;
		sock = 0;
	}
	int sock;
};

int process(SOCKET _client)
{
	char recbuffer[1024] = {};


	int len = recv(_client, recbuffer, sizeof(Header), 0);

	Header* head = (Header*)recbuffer;


	if (len <= 0)
	{
		printf("socket:%d与服务器断开连接,任务结束\n",_client);
		return -1;
	}

	switch (head->cmd)
	{
		case CMD_LOGIN_RESULT:
		{

			recv(_client, recbuffer + sizeof(head), head->lendata - sizeof(head), 0);

			LoginResult* login = (LoginResult*)recbuffer;
			printf("收到服务端消息CMD_LOGIN_RESULT:%d,数据长度:%d\n",login->result
				, login->lendata);
		}
		break;
		case CMD_LOGINOUT_RESULT:
		{

			recv(_client, recbuffer + sizeof(head), head->lendata - sizeof(head), 0);
			LoginOutResult* loginout = (LoginOutResult*)recbuffer;
			printf("收到服务端消息CMD_LOGINOUT_RESULT:%d,数据长度:%d\n", loginout->result
				, loginout->lendata);
		}
		break;
		case CMD_NEW_USER_JOIN:
		{

			recv(_client, recbuffer + sizeof(head), head->lendata - sizeof(head), 0);
			NewUserJoin* usr = (NewUserJoin*)recbuffer;
			printf("收到服务端消息CMD_NEW_USER_JOIN:%d,数据长度:%d\n", usr->sock
				, usr->lendata);
		}
		break;
	}

	return 0;
}

bool flag = true;

void cmdThread(SOCKET client)
{
	
	while (true)
	{
		char cmdbuf[50] = {};

		scanf("%s", cmdbuf);

		if (0 == strcmp(cmdbuf, "exit"))
		{
			flag = false;
			printf("cmdThread退出\n");
			break;;
		}
		else if (0 == strcmp(cmdbuf, "login"))
		{
			Login login;
			strcpy(login.usrname, "zb");
			strcpy(login.password, "zb");
			send(client, (const char*)&login, sizeof(login), 0);
		}
		else if (0 == strcmp(cmdbuf, "logout"))
		{
			LoginOut loginout;
			strcpy(loginout.usrname, "zb");
			send(client, (const char*)&loginout, sizeof(loginout), 0);
		}
		else
		{
			printf("不支持的命令\n");
		}
	}
	return;
}


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


	if (SOCKET_ERROR == ret)
	{
		printf("connect fault!\n");
	}
	else
	{
		printf("connect success!\n");
	}

	thread t1(cmdThread,client);
	
	if (t1.joinable())
	{
		t1.detach();
	}

	while (flag)
	{
		fd_set fd_read;
		FD_ZERO(&fd_read);
		FD_SET(client, &fd_read);

		timeval t{ 1,0 };

		int ret=select(client, &fd_read, 0, 0, &t);

		if (ret<0)
		{
			printf("select finish\n");
			break;
		}

		if (FD_ISSET(client,&fd_read))
		{
			FD_CLR(client, &fd_read);
			if (-1 == process(client))
			{
				printf("select finish2\n");
				break;
			}
		}
		//thread
		//if (t1.joinable())
		//{
		//	t1.join();
		//}

		//printf("空闲处理其他任务\n");
	}

	closesocket(client);

	WSACleanup();
	printf("已退出\n");


	system("pause");
	return 0;
}