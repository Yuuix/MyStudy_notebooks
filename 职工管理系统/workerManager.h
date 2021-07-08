#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include"worker.h"
#define FILENAME "empFile.txt"


class workerManager
{
public:

	//���캯��
	workerManager();

	//չʾ�˵�
	void showMenu();

	//�˳�����
	void exitsystem();

	//��������
	~workerManager();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	worker** m_EmpArray;

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ��е�����
	int get_EmpNum();

	//��ʼ���ļ��е�����
	void init_Emp();

	//���ְ��
	void addEmp();

	//��ʾְ��
	void ShowEmp();

	//ɾ��ְ��
	void DelEmp();

	//�ж�ְ���Ƿ����
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	void save();
};