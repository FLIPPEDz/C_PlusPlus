#ifdef _WIN32
	#define  WIN32_LEAN_AND_MEAN
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <windows.h>
	#include <WinSock2.h>
	#pragma comment(lib,"ws2_32.lib")

#else
	#include <unistd.h>  //unix std
	#include <string.h>
	#include <arpa/inet.h>

	#define SOCKET unsigned int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif

#include <stdio.h>
#include <vector>




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

std::vector<SOCKET> g_clients;

int process(SOCKET _client)
{
	char recbuffer[1024] = {};


	int len = (int)recv(_client, recbuffer, sizeof(Header), 0);

	Header* head = (Header*)recbuffer;


	if (len <= 0)
	{
		printf("<client:%d> quit task!\n", _client);
		return -1;
	}

	switch (head->cmd)
	{
	case CMD_LOGIN:
	{

		recv(_client, recbuffer + sizeof(Header), head->lendata - sizeof(Header), 0);

		Login* login = (Login*)recbuffer;
		printf("recv <client:%d> cmd:CMD_LOGIN datalen:%d username:%s ,userpsw:%s \n", _client, login->lendata
			, login->usrname, login->password);
		//忽略判断用户密码是否正确

		LoginResult loginres;
		send(_client, (char*)&loginres, sizeof(loginres), 0);
	}
	break;
	case CMD_LOGINOUT:
	{

		recv(_client, recbuffer + sizeof(Header), head->lendata - sizeof(Header), 0);
		LoginOut* loginout = (LoginOut*)recbuffer;
		printf("recv <client:%d> cmd:CMD_LOGINOUT datalen:%d username:%s \n", _client, loginout->lendata
			, loginout->usrname);

		//忽略判断用户密码是否正确


		LoginOutResult loginoutres;
		send(_client, (char*)&loginoutres, sizeof(loginoutres), 0);
	}
	break;
	default:
	{
		Header head = { 0,CMD_ERROR };
		send(_client, (char*)&head, sizeof(head), 0);
	}
	break;
	}

	return 0;
}

int main()
{
#ifdef _WIN32  
	WORD var = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(var, &data);
#endif
	SOCKET _sock;
	_sock = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in _sin = {};

	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(40000);
#ifdef _WIN32
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
#else
	_sin.sin_addr.s_addr = INADDR_ANY;
#endif

	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in)))
	{
		printf("bind fault!\n");
	}
	else
	{
		printf("bind succes!\n");
	}

	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("listen fault!\n");
	}
	else
	{
		printf("listen succes!\n");
	}



	while (true)
	{
		//伯克利 socket 描述符
		fd_set fd_read;
		fd_set fd_write;
		fd_set fd_exp;

		FD_ZERO(&fd_read);
		FD_ZERO(&fd_write);
		FD_ZERO(&fd_exp);

		//放到集合中
		FD_SET(_sock, &fd_read);
		FD_SET(_sock, &fd_write);
		FD_SET(_sock, &fd_exp);

		SOCKET maxsock = _sock;

		for (int i = (int)g_clients.size() - 1;i >= 0;i--)
		{
			FD_SET(g_clients[i], &fd_read);
			if (maxsock < g_clients[i])
			{
				/* code */
				maxsock = g_clients[i];
			}
		}

		timeval ti_me{ 1,0 };


		//nfds 整数值 指集合中所有描述符(socket)的范围，而不是数量
		//windows中可以写零
		int ret = select(maxsock + 1, &fd_read, &fd_write, &fd_exp, &ti_me);

		if (ret < 0)
		{
			printf("select quit task!\n");
			break;
		}

		if (FD_ISSET(_sock, &fd_read))
		{
			FD_CLR(_sock, &fd_read);
			sockaddr_in clientAddr = {};

			SOCKET _client = INVALID_SOCKET;

			int len = sizeof(clientAddr);
#ifdef _WIN32
			_client = accept(_sock, (sockaddr*)&clientAddr, &len);
#else            
			_client = accept(_sock, (sockaddr*)&clientAddr, (socklen_t *)&len);
#endif
			if (INVALID_SOCKET == _client)
			{
				printf("accept _client fault!\n");
			}
			else
			{
				for (int i = (int)g_clients.size() - 1;i >= 0;i--)
				{
					NewUserJoin userjion;
					send(g_clients[i], (const char*)&userjion, sizeof(NewUserJoin), 0);
				}

				g_clients.push_back(_client);

				printf("new client socket=%d ip=%s\n", (int)_client, inet_ntoa(clientAddr.sin_addr));
			}

		}

		for (int i = (int)g_clients.size() - 1;i >= 0;i--)
		{
			if (FD_ISSET(g_clients[i], &fd_read))
			{
				if (process(g_clients[i]) == -1)
				{
					auto itr = g_clients.begin()+i;
					if (itr != g_clients.end())
					{
						g_clients.erase(itr);
					}
				}

			}

		}

		//printf("空闲处理其他任务\n");
	}

#ifdef _WIN32
	for (size_t n = 0;n < g_clients.size();++n)
	{
		closesocket(g_clients[n]);
	}
	closesocket(_sock);
	WSACleanup();

#else
	for (size_t n = 0;n < g_clients.size();++n)
	{
		close(g_clients[n]);
	}
	close(_sock);

#endif

	g_clients.clear();
	printf("finish task quit!\n");

	getchar();

	return 0;
}
