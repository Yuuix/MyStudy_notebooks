#pragma once
#include<iostream>
#include<string>
using namespace std;

class worker
{
public:

	virtual void showInfo() = 0;

	virtual string getDeName() = 0;

	int m_ID;
	string m_Name;
	int m_DeName;
};