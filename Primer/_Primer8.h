#pragma once
#include "Header.h"
//8-1,2
//istream& in(istream& is)
//{
//	string buffer;
//	auto old_state = is.rdstate();
//	while (is>> buffer)
//	{		
//		if (is.eof())
//		{
//			break;
//		}
//		cout << buffer << endl;
//	}
//	is.setstate(old_state);
//	return is;
//}

//8-3
//putting cin in an error state cause to terminate. such as eofbit, failbit and badbit.

//8-4
//vector<string> val;
//fstream fs;
//string buffer;
//fs.open("g:\\1.txt");
//while (getline(fs, buffer))
//{
//	val.push_back(buffer);
//}
//
//for (const auto &i : val)
//{
//	cout << i << endl;
//}

//8-5
//vector<string> val;
//fstream fs;
//fs.open("g:\\1.txt");
//if (fs)
//{
//	string buffer;
//	while (fs >> buffer)
//	{
//		val.push_back(buffer);
//	}
//
//}
//for (const auto &i : val)
//{
//	cout << i << endl;
//}


//8-10
//vector<string> line;
//
//fstream fs("g:\\1.txt", fstream::in);
//
//if (fs)
//{
//	string buffer;
//	while (getline(fs, buffer))
//	{
//		line.push_back(buffer);
//	}
//	fs.close();
//}
//
//if (!line.empty())
//{
//
//	for (const auto& i : line)
//	{
//		istringstream val(i);
//		string word;
//		while (val >> word)
//		{
//			cout << word << endl;
//		}
//	}
//
//}


//8-11
//istringstream val;
//for (const auto& i : line)
//{
//	val.clear();
//	val.str(i);
//	string word;
//	while (val >> word)
//	{
//		cout << word << endl;
//	}
//}

//8-12
//Cause we need a aggregate(聚合) class here. so it should have no in-class initializers.

//8-13
//vector<PersonInfo> people;
//fstream fs("g:\\1.txt");
//if (!fs)
//{
//	cout << "open fail!" << endl;
//}
//string buffer;
//while (getline(fs, buffer))
//{
//	PersonInfo info;
//	string numbers;
//	istringstream record(buffer);
//	record >> info.name;
//	while (record >> numbers)
//	{
//		info.phones.push_back(numbers);
//	}
//	people.push_back(info);
//}


//8-14
//cause they are all class type, not the built-in type. so reference more effective.
//output shouldn't change their values. so we added the const.
//防止数据被修改，传引用更快
