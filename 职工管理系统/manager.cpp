#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeName = dId;
}

void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeName()
		<< "\t��λְ������ϰ彻�������񣬲����·��������ͨԱ��" << endl;
}

string Manager::getDeName()
{
	return"����";
}