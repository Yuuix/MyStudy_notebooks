#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeName = dId;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeName()
		<< "\t岗位职责：完成老板交给的任务，并且下发任务给普通员工" << endl;
}

string Manager::getDeName()
{
	return"经理";
}