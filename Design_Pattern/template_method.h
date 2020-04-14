#pragma once

class Library
{
public:
	void Run()
	{
		step1();
		if (step2())
		{
			step3();
		}
		for (int i=0;i<4;++i)
		{
			step4();
		}

		step5();

	}

	virtual ~Library()
	{
		cout << "~Library()" << endl;
	}

protected:
	void step1()
	{
		cout << "Library" << endl;
	}
	void step3()
	{
		cout << "Library" << endl;
	}
	void step5()
	{
		cout << "Library" << endl;
	}
	virtual bool step2() = 0;
	virtual bool step4() = 0;
};

class Application:public Library
{
public:
	bool step2() override
	{
		cout << "Application" << endl;
		return true;
	}
	bool step4() override
	{
		cout << "Application" << endl;
		return true;
	}
};
