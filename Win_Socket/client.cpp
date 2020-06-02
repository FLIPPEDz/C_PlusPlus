#include "EasyTcpClient.hpp"
#include <thread>

using std::thread;


void cmdThread(EasyTcpClient* client)
{

	while (true)
	{
		char cmdbuf[50] = {};

		scanf("%s", cmdbuf);

		if (0 == strcmp(cmdbuf, "exit"))
		{
			client->Close();
			printf("cmdThread退出\n");
			break;
		}
		else if (0 == strcmp(cmdbuf, "login"))
		{
			Login login;
			strcpy(login.usrname, "zb");
			strcpy(login.password, "zbmms");
			client->SendData(&login);
		}
		else if (0 == strcmp(cmdbuf, "logout"))
		{
			LoginOut loginout;
			strcpy(loginout.usrname, "zb");
			client->SendData(&loginout);
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

	EasyTcpClient client1;


	client1.Connect("10.10.10.135", 40000);


	//thread t1(cmdThread, &client1);

	//if (t1.joinable())
	//{
	//	t1.detach();
	//}

	Login login;
	strcpy(login.usrname, "zb");
	strcpy(login.password, "zbzb");
	while (client1.isRun())
	{
		client1.OnRun();
		client1.SendData(&login);
	}
	
	client1.Close();

	printf("已退出\n");

	getchar();
	return 0;

}
