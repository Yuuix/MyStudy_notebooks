#include<iostream>
using namespace std;
#include"employee.h"

void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeName()
		<< "\t��λְ����ɾ�����������" << endl;
}

string Employee::getDeName()
{
	return"Ա��";
}

Employee::Employee(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeName = dId;
}