#include<iostream>
using namespace std;
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


int main()
{
	//ʵ���������߶���
	workerManager wm;


	int choice=0;
	while (true)
	{
		//����չʾ�˵���Ա����
		wm.showMenu();

		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:  //�˳�ϵͳ
			wm.exitsystem();
			break;
		case 1:  //����ְ��
			wm.addEmp();
			break;
		case 2:  //��ʾְ��
			wm.ShowEmp();
			break;
		case 3:  //ɾ��ְ��
			wm.DelEmp();
			break;
		case 4:  //�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:  //����ְ��
			wm.Find_Emp();
			break;
		case 6:  //����ְ��
			wm.Sort_Emp();
			break;
		case 7:  //����ĵ�
			wm.Clean_File();
			break;
		default:
			system("cls"); //����
			break;
		}
	}

	system("pause");

	return 0;
}