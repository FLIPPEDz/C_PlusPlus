#ifndef _MessageHeader_hpp
#define _MessageHeader_hpp

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
	char data[1024];
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



#endif

