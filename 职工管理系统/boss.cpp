#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeName = dId;
}

void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeName()
		<< "\t��λְ�𣺹���˾��������" << endl;
}

string Boss::getDeName()
{
	return"�ϰ�";
}