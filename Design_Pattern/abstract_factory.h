#pragma once

class IDBConnection
{

};

class IDBConnectionFactory
{
public:
	virtual IDBConnection* CreateDBConnection() = 0;

};


class IDBCommand
{

};

class IDBCommandFactory
{
public:
	virtual IDBCommand* CreateDBCommand() = 0;

};

class IDataReader
{

};

class IDataReaderFactory
{
public:
	virtual IDataReader* CreateDataReader() = 0;

};

//支持SqlServer
class SqlConnection :public IDBConnection
{

};

class SqlConnectionFactory :public IDBConnectionFactory
{

};


class SqlCommand :public IDBCommand
{

};

class SqlCommandFactory :public IDBCommandFactory
{

};

class SqlDataReader :public IDataReader
{

};

class SqlDataReaderFactory :public IDataReaderFactory
{

};

class IDBFactory
{
public:
	virtual IDBConnection* CreateDBConnection() = 0;
	virtual IDBCommand* CreateDBCommand() = 0;
	virtual IDataReader* CreateDataReader() = 0;
};

class SqlDBFactory :public IDBFactory
{


};

//
