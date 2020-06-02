#include "EasyTcpServer.hpp"


int main()
{
	EasyTcpServer server;

	server.InitSocket();

	server.Bind(nullptr, 40000);

	server.Listen(5);


	while (server.IsRun())
	{
	

		server.OnRun();

		//printf("空闲处理其他任务\n");
	}

	server.Close();
	printf("finish task quit!\n");

	getchar();

	return 0;
}
