#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include"worker.h"
#define FILENAME "empFile.txt"


class workerManager
{
public:

	//构造函数
	workerManager();

	//展示菜单
	void showMenu();

	//退出功能
	void exitsystem();

	//析构函数
	~workerManager();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	worker** m_EmpArray;

	//标志文件是否为空
	bool m_FileIsEmpty;

	//统计文件中的人数
	int get_EmpNum();

	//初始化文件中的数据
	void init_Emp();

	//添加职工
	void addEmp();

	//显示职工
	void ShowEmp();

	//删除职工
	void DelEmp();

	//判断职工是否存在
	int IsExist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();

	//清空文件
	void Clean_File();

	void save();
};