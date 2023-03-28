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
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.exitsystem();//退出系统
			break;
		case 1://添加职工
			wm.add_emp();
			break;
		case 2://显示职工
			wm.show_emp();
			break;
		case 3://删除职工
			wm.del_emp();
			break;
		case 4://修改职工
			wm.mod_emp();
			break;
		case 5://查找职工
			wm.find_emp();
			break;
		case 6://排序职工
			wm.sort_emp();
			break;
		case 7://清空文件
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