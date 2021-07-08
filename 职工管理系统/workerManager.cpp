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

	//第一种情况：文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//第二种情况：文件存在但是为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件不存在" << endl;

		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//第三种情况：文件存在且不为空
	this->m_FileIsEmpty = false;
	this->m_EmpNum = this->get_EmpNum();
	cout << "职工的人数为：" << this->get_EmpNum() << endl;
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
		cout << "职工编号：" << this->m_EmpArray[i]->m_ID << " "
			<< "姓名：" << this->m_EmpArray[i]->m_Name << " "
			<< "部门编号：" << this->m_EmpArray[i]->m_DeName << endl;
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

//删除职工
void workerManager::DelEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录为空" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工编号：" << endl;
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
			cout << "删除成功" << endl;
		}
		else if (index == this->m_EmpNum - 1)
		{
			delete this->m_EmpArray[index];
			this->m_EmpArray[index] = NULL;
			this->m_EmpNum--;
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该员工" << endl;
		}
	}

	system("pause");
	system("cls");
}

//判断职工是否存在
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//找到职工
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
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号：" << endl;
		int id = 0;

		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newid = 0;
			string newname = "";
			int newdId = 0;

			cout << "查找到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newid;

			cout << "请输入新的姓名：" << endl;
			cin >> newname;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			cout << "修改成功" << endl;
			this->save();
		}
		else
		{
			cout << "该员工不存在" << endl;
		}
	}

	system("pause");
	system("cls");
}

void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1、按找编号查找" << endl;
		cout << "2、按找姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入需要查找的员工编号：" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			
			if (ret != -1)
			{
				cout << "找到员工，信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "未查到此人" << endl;
			}
		}
		else if(select == 2)
		{
			string name;
			cout << "请输入需要查找的员工姓名：" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = true;
					cout << "查到姓名为：" << name << " 的员工，信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					break;
				}
			}
			if (!flag)
			{
				cout << "未找到姓名为：" << name << " 的员工" << endl;
			}
			
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;

		system("pause");
		system("cls");
	}
	else
	{
		int select;
		cout << "请选择排序方式：" << endl;
		cout << "1、升序排列" << endl
			<< "2、降序排列" << endl;
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

	cout << "排序成功，结果为：" << endl;
	this->ShowEmp();
}

void workerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1、是" << endl
		<< "2、否" << endl;
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
			cout << "清空成功" << endl;
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
	cout << "****** 欢迎使用职工管理系统! *****" << endl;
	cout << "********** 0.退出管理程序 ********" << endl;
	cout << "********** 1.增加职工信息 ********" << endl;
	cout << "********** 2.显示职工信息 ********" << endl;
	cout << "********** 3.删除离职职工 ********" << endl;
	cout << "********** 4.修改职工信息 ********" << endl;
	cout << "********** 5.查找职工信息 ********" << endl;
	cout << "********** 6.按找编号排序 ********" << endl;
	cout << "********** 7.清空所有文档 ********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

void workerManager::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


void workerManager::addEmp()
{
	cout << "请输入添加的职工数量" << endl;

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

			cout << "请输入第" << i + 1 << "个职工的编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个职工的姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

		cout << "成功添加" << c_num << "名新员工" << endl;

		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}