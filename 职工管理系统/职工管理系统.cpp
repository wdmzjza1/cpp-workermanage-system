#include<iostream>
using namespace std;
#include"workmanager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include"worker.h"

int main()
{
	workmanager wm;
	int choice = 0;
	while (true)
	{
		wm.show_menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.exitsystem();//�˳�ϵͳ
			break;
		case 1://���ְ��
			wm.add_emp();
			break;
		case 2://��ʾְ��
			wm.show_emp();
			break;
		case 3://ɾ��ְ��
			wm.del_emp();
			break;
		case 4://�޸�ְ��
			wm.mod_emp();
			break;
		case 5://����ְ��
			wm.find_emp();
			break;
		case 6://����ְ��
			wm.sort_emp();
			break;
		case 7://����ļ�
			wm.clean_file();
			break;
		default:
			system("cls");
			break;
		
		}
	}



	system("pause");
	return 0;
}