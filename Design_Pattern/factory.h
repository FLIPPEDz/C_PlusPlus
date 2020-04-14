#pragma once

//Test Code
//	BinarySplitterFactory* item;
//SplitterFactory* factory;
//factory = item;
//ISplitter* splitter = factory->CreateSplitter();

class ISplitter;


//工厂基类
class SplitterFactory
{
public:
	virtual ISplitter* CreateSplitter() = 0;
	virtual ~SplitterFactory(){ }
	
};

class BinarySplitter;

//工厂
class BinarySplitterFactory:public SplitterFactory
{
public:
	ISplitter* CreateSplitter() override
	{
		return new BinarySplitter();
	}

};


class ISplitter
{
public:
	virtual void split() = 0;
	virtual ~ISplitter(){  }
};


class BinarySplitter :public ISplitter
{
public:
	void split() override{ }

};
//
