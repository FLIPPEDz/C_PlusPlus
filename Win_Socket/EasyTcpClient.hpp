# ifndef _EasyTcpClient_hpp_
# define _EasyTcpClient_hpp_

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
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
#include "MessageHeader.hpp"


class EasyTcpClient
{
public:
	EasyTcpClient():_sock(INVALID_SOCKET)
	{

	}

	virtual	~EasyTcpClient()
	{
		Close();
	}

	void InitSocket()
	{
#ifdef _WIN32    
		WORD ver = MAKEWORD(2, 2);
		WSADATA data;
		WSAStartup(ver, &data);
#endif 
		if (INVALID_SOCKET!=_sock)
		{
			printf("<socket=%d>关闭旧连接\n", _sock);
			Close();
		}

		_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET == _sock)
		{
			printf("client create fault!\n");
		}
		else
		{
			printf("socket create success!\n");
		}

		return;
	}

	int Connect(const char* ip,unsigned short port)
	{
		if (INVALID_SOCKET == _sock)
		{
			InitSocket();
		}

		sockaddr_in _sin = {};
		_sin.sin_family = AF_INET;
		_sin.sin_port = htons(port);

#ifdef _WIN32
		_sin.sin_addr.S_un.S_addr = inet_addr(ip);
#else
		_sin.sin_addr.s_addr = inet_addr("192.168.10.1");
#endif

		int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));

		if (SOCKET_ERROR == ret)
		{
			printf("connect fault!\n");
		}
		else
		{
			printf("connect success!\n");
		}

		return ret;
	}

	
	void Close()		//关闭套字节
	{
		if (_sock!=INVALID_SOCKET)
		{
#ifdef _WIN32
			closesocket(_sock);
			WSACleanup();   //清除Win socket环境
#else
			close(client);
#endif
			_sock = INVALID_SOCKET;
		}
	}

	//处理消息
	bool OnRun()
	{
		if (isRun())
		{
			fd_set fd_read;
			FD_ZERO(&fd_read);
			FD_SET(_sock, &fd_read);

			timeval t{ 1,0 };

			int ret = select(_sock + 1, &fd_read, 0, 0, &t);

			if (ret < 0)
			{
				printf("<socket=%d>select finish\n", _sock);
				Close();
				return false;
			}

			if (FD_ISSET(_sock, &fd_read))
			{
				FD_CLR(_sock, &fd_read);
				if (-1 == RecvData(_sock))
				{
					printf("select finish2\n");
					Close();
					return false;
				}
			}
			return true;
		}

		return false;
	}

	bool isRun()
	{
		return _sock != INVALID_SOCKET;
	}


	//查询数据 处理粘包 拆分包
	int RecvData(SOCKET _client)
	{
		char recbuffer[4096] = {};


		int len = recv(_client, recbuffer, sizeof(Header), 0);

		Header* head = (Header*)recbuffer;


		if (len <= 0)
		{
			printf("socket:%d与服务器断开连接,任务结束\n", _client);
			return -1;
		}

		recv(_client, recbuffer + sizeof(head), head->lendata - sizeof(head), 0);
		
		OnNetMsg(head);


		return 0;
	}

	//响应网络消息
	void OnNetMsg(Header* head)
	{

		switch (head->cmd)
		{
		case CMD_LOGIN_RESULT:
		{
			LoginResult* login = (LoginResult*)head;
			printf("收到服务端消息CMD_LOGIN_RESULT:%d,数据长度:%d\n", login->result
				, login->lendata);
		}
		break;
		case CMD_LOGINOUT_RESULT:
		{
			LoginOutResult* loginout = (LoginOutResult*)head;
			printf("收到服务端消息CMD_LOGINOUT_RESULT:%d,数据长度:%d\n", loginout->result
				, loginout->lendata);
		}
		break;
		case CMD_NEW_USER_JOIN:
		{

			NewUserJoin* usr = (NewUserJoin*)head;
			printf("收到服务端消息CMD_NEW_USER_JOIN:%d,数据长度:%d\n", usr->sock
				, usr->lendata);
		}
		break;
		}
	}

	//
	int SendData(Header* head)
	{
		if (isRun() && head)
		{
			return send(_sock, (const char*)head, head->lendata, 0);
		}

		return SOCKET_ERROR;
	}

private:
	SOCKET _sock;
};






#endif
