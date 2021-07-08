#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//��һ��������ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ڶ���������ļ����ڵ���Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�������" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//������������ļ������Ҳ�Ϊ��
	this->m_FileIsEmpty = false;
	this->m_EmpNum = this->get_EmpNum();
	cout << "ְ��������Ϊ��" << this->get_EmpNum() << endl;
	this->m_EmpArray = new worker* [this->m_EmpNum];
	this->init_Emp();

	ifs.close();
}

int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();
	return num;
}

void workerManager::ShowEmp()
{
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_ID << " "
			<< "������" << this->m_EmpArray[i]->m_Name << " "
			<< "���ű�ţ�" << this->m_EmpArray[i]->m_DeName << endl;
	}
	system("pause");
	system("cls");
}

void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		worker* wor = NULL;
		if (dId == 1)
		{
			wor = new Employee(id,name,dId);
		}
		else if (dId == 2)
		{
			wor = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			wor = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = wor;
		index++;
	}
	//ifs.close();
}

void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeName << endl;
	}

	ofs.close();
}

//ɾ��ְ��
void workerManager::DelEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1&&index!=this->m_EmpNum-1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			delete this->m_EmpArray[this->m_EmpNum-1];
			this->m_EmpArray[this->m_EmpNum - 1] = NULL;
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else if (index == this->m_EmpNum - 1)
		{
			delete this->m_EmpArray[index];
			this->m_EmpArray[index] = NULL;
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա��" << endl;
		}
	}

	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//�ҵ�ְ��
			index = i;

			break;
		}
	}
	return index;
}

void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id = 0;

		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newid = 0;
			string newname = "";
			int newdId = 0;

			cout << "���ҵ���" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newid;

			cout << "�������µ�������" << endl;
			cin >> newname;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin>> newdId;

			worker* wor = NULL;
			switch (newdId)
			{
			case 1:
				wor = new Employee(newid, newname, newdId);
				break;
			case 2:
				wor = new Manager(newid, newname, newdId);
				break;
			case 3:
				wor = new Boss(newid, newname, newdId);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = wor;
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else
		{
			cout << "��Ա��������" << endl;
		}
	}

	system("pause");
	system("cls");
}

void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1�����ұ�Ų���" << endl;
		cout << "2��������������" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "��������Ҫ���ҵ�Ա����ţ�" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			
			if (ret != -1)
			{
				cout << "�ҵ�Ա������Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "δ�鵽����" << endl;
			}
		}
		else if(select == 2)
		{
			string name;
			cout << "��������Ҫ���ҵ�Ա��������" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = true;
					cout << "�鵽����Ϊ��" << name << " ��Ա������Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
					break;
				}
			}
			if (!flag)
			{
				cout << "δ�ҵ�����Ϊ��" << name << " ��Ա��" << endl;
			}
			
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;

		system("pause");
		system("cls");
	}
	else
	{
		int select;
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����������" << endl
			<< "2����������" << endl;
		cin >> select;
		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int MinorMax = i;

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[i]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						MinorMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[i]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						MinorMax = j;
					}
				}
			}
			if (i != MinorMax)
			{
				worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[MinorMax];
				this->m_EmpArray[MinorMax] = temp;
			}
		}
	}

	cout << "����ɹ������Ϊ��" << endl;
	this->ShowEmp();
}

void workerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1����" << endl
		<< "2����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
			cout << "��ճɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}

void workerManager::showMenu()
{
	cout << "**********************************" << endl;
	cout << "****** ��ӭʹ��ְ������ϵͳ! *****" << endl;
	cout << "********** 0.�˳�������� ********" << endl;
	cout << "********** 1.����ְ����Ϣ ********" << endl;
	cout << "********** 2.��ʾְ����Ϣ ********" << endl;
	cout << "********** 3.ɾ����ְְ�� ********" << endl;
	cout << "********** 4.�޸�ְ����Ϣ ********" << endl;
	cout << "********** 5.����ְ����Ϣ ********" << endl;
	cout << "********** 6.���ұ������ ********" << endl;
	cout << "********** 7.��������ĵ� ********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

void workerManager::exitsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


void workerManager::addEmp()
{
	cout << "��������ӵ�ְ������" << endl;

	int c_num = 0;
	cin >> c_num;

	if (c_num > 0)
	{
		int newSize = this->m_EmpNum + c_num;
		worker** newSpace = new worker * [newSize];

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		for (int i = 0; i < c_num; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "��ְ���ı�ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "��ְ����������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			worker* wor = NULL;
			switch (dSelect)
			{
			case 1:
				wor = new Employee(id, name, dSelect);
				break;
			case 2:
				wor = new Manager(id, name, dSelect);
				break;
			case 3:
				wor = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = wor;
		}
		delete[] this->m_EmpArray;

		this->m_EmpArray = newSpace;

		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;

		cout << "�ɹ����" << c_num << "����Ա��" << endl;

		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}