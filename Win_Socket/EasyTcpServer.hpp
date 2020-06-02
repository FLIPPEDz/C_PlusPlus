#ifndef _EasyTcpServer_hpp_
#define _EasyTcpServer_hpp_

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
#include "MessageHeader.hpp"

class EasyTcpServer
{
	std::vector<SOCKET> g_clients;
	SOCKET _sock;
public:
	EasyTcpServer ():_sock(INVALID_SOCKET)
	{


	}

	~EasyTcpServer()
	{
		Close();
	}

	//初始化socket
	SOCKET InitSocket()
	{
#ifdef _WIN32  
		WORD var = MAKEWORD(2, 2);
		WSADATA data;
		WSAStartup(var, &data);
#endif

		_sock = socket(AF_INET, SOCK_STREAM, 0);

		if (INVALID_SOCKET == _sock)
		{
			printf("server create fault!\n");
		}
		else
		{
			printf("server create success!\n");
		}
		return _sock;
	}

	//绑定ip和端口号
	int Bind(const char* ip,unsigned short port)
	{
		sockaddr_in _sin = {};
		_sin.sin_family = AF_INET;
		_sin.sin_port = htons(port);

#ifdef _WIN32
		if (ip)
		{
			_sin.sin_addr.S_un.S_addr = inet_addr(ip);
		}
		else
		{
			_sin.sin_addr.S_un.S_addr = INADDR_ANY;
		}	
#else
		if (ip)
		{
			_sin.sin_addr.s_addr = inet_addr(ip);
		}
		else
		{
			_sin.sin_addr.s_addr = INADDR_ANY;
		}	
#endif
		int ret = bind(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));

		if (SOCKET_ERROR == ret)
		{
			printf("bind socket<%d> fault!\n",port);
		}
		else
		{
			printf("bind socket<%d> succes!\n",port);
		}

		return ret;
	}

	//监听端口号
	int Listen(int nums)
	{
		int ret = listen(_sock, nums);
		if (SOCKET_ERROR == ret)
		{
			printf("listen socket<%d> fault!\n",_sock);
		}
		else
		{
			printf("listen socket<%d> succes!\n", _sock);
		}

		return ret;
	}

	//接收客户端连接

	SOCKET Accept()
	{
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
			printf("socket<%d>accept _client fault!\n", _client);
		}
		else
		{

			NewUserJoin userjion;
			SendDataToAll(&userjion);

			g_clients.push_back(_client);

			printf("new client socket=%d ip=%s\n", (int)_client, inet_ntoa(clientAddr.sin_addr));
		}

		return _client;
	}


	//关闭socket
	void Close()
	{
		if (_sock!=INVALID_SOCKET)
		{
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
		}
	}

	
	bool IsRun()
	{
		return _sock != INVALID_SOCKET;
	}


	//处理消息
	bool OnRun()
	{

		if (IsRun())
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
				Close();
				return false;
			}

			if (FD_ISSET(_sock, &fd_read))
			{
				FD_CLR(_sock, &fd_read);
				Accept();
			}

			for (int i = (int)g_clients.size() - 1;i >= 0;i--)
			{
				if (FD_ISSET(g_clients[i], &fd_read))
				{
					if (RecveData(g_clients[i]) == -1)
					{
						auto itr = g_clients.begin() + i;
						if (itr != g_clients.end())
						{
							g_clients.erase(itr);
						}
					}

				}

			}

			return true;
		}

		return false;
	}

	//查询数据 处理粘包 拆分包
	int RecveData(SOCKET _client)
	{
		char recbuffer[1024] = {};


		int len = (int)recv(_client, recbuffer, sizeof(Header), 0);

		Header* head = (Header*)recbuffer;


		if (len <= 0)
		{
			printf("<client:%d> quit task!\n", _client);
			return -1;
		}

		recv(_client, recbuffer + sizeof(Header), head->lendata - sizeof(Header), 0);
		OnNetMsg(_client, head);

		return 0;
	}

	//响应网络消息
	virtual void OnNetMsg(SOCKET _client,Header* head)
	{

		switch (head->cmd)
		{
		case CMD_LOGIN:
		{

			Login* login = (Login*)head;
			printf("recv <client:%d> cmd:CMD_LOGIN datalen:%d username:%s ,userpsw:%s \n", _client, login->lendata
				, login->usrname, login->password);
			//忽略判断用户密码是否正确

			LoginResult loginres;
			send(_client, (char*)&loginres, sizeof(loginres), 0);
		}
		break;
		case CMD_LOGINOUT:
		{

			LoginOut* loginout = (LoginOut*)head;
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
	}


	//发送给指定SOCKET
	int SendData(SOCKET _client,Header* head)
	{
		if (IsRun() && head)
		{
			return send(_client, (const char*)head, head->lendata, 0);
		}

		return SOCKET_ERROR;
	}




	void SendDataToAll(Header* head)
	{

		if (IsRun() && head)
		{
			for (int i = (int)g_clients.size() - 1;i >= 0;i--)
			{
				SendData(g_clients[i], head);
			}
			
		}
	}

};








#endif
