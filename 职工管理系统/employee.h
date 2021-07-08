#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Employee :public worker
{
public:

	void showInfo();

	string getDeName();

	Employee(int id,string name,int dId);
};