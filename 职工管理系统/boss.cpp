#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeName = dId;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeName()
		<< "\t岗位职责：管理公司所有事物" << endl;
}

string Boss::getDeName()
{
	return"老板";
}