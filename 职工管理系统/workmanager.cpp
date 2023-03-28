#include"workmanager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include"worker.h"
workmanager::workmanager()
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_empnum = 0;
		this->m_fileisempty = true;
		this->m_emparray = NULL;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->m_fileisempty = true;
		this->m_emparray = NULL;
		ifs.close();
		return;
	}
	int num = this->get_empnum();
	cout << "职工个数为:" << num << endl;
	this->m_empnum = num;

	this->m_emparray = new worker * [this->m_empnum];
	init_emp();
	for (int i = 0; i < m_empnum; i++)
	{
		cout << "职工号:" << this->m_emparray[i]->m_id
			<< "\t职工姓名：" << this->m_emparray[i]->m_name
			<< "\t部门编号：" << this->m_emparray[i]->m_deptid << endl;
	}
}
workmanager::~workmanager()
{
	if (this->m_emparray != NULL)
	{
		for (int i = 0; i < this->m_empnum; i++)
		{
			if (this->m_emparray[i] != NULL)
			{
				delete this->m_emparray[i];
			}
		}
		delete[]this->m_emparray;
	}
}
void workmanager::show_menu()
{
	cout << "*****************************************" << endl;
	cout << "**********欢迎使用职工系统！************" << endl;
	cout << "**************0.退出管理系统************" << endl;
	cout << "**************1.增加职工信息************" << endl;
	cout << "**************2.显示职工信息************" << endl;
	cout << "**************3.删除离职职工************" << endl;
	cout << "**************4.修改职工信息************" << endl;
	cout << "**************5.查找职工信息************" << endl;
	cout << "**************6.按照编号排序************" << endl;
	cout << "**************7.清空所有文档************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}
void workmanager::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void workmanager::add_emp()
{
	cout << "请输入增加职工数量:" << endl;

	int addnum = 0;
	cin >> addnum;

	if (addnum > 0)
	{
		int newsize = this->m_empnum + addnum;
		worker** newspace = new worker * [newsize];

		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				newspace[i] = this->m_emparray[i];
			}
		}
	
		for (int i = 0; i < addnum; i++)
		{
			int id;
			string name;
			int dselect;

			cout << "请输入第 " << i + 1 << " 个新职工编号" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;

			worker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new employee(id, name, 1);
				break;
			case 2:
				worker = new manager(id, name, 2);
				break;
			case 3:
				worker = new boss(id, name, 3);
				break;
			default:
				break;

			}
			newspace[this->m_empnum + i] = worker;
		}
		this->save();
		delete[]this->m_emparray;
		this->m_empnum = newsize;
		this->m_fileisempty = false;
		cout << "成功添加" << addnum << "名新职工！" << endl;

		//this->save();
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}
void workmanager::save()
{
	ofstream ofs;
	ofs.open(filename, ios::out);


	for (int i = 0; i < this->m_empnum; i++)
	{
		ofs << this->m_emparray[i]->m_id << " "
			<< this->m_emparray[i]->m_name << " "
			<< this->m_emparray[i]->m_deptid << endl;
	}

	ofs.close();
}
int workmanager::get_empnum()
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	int id;
	string name;
	int did;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	ifs.close();
	return num;
}

void workmanager::init_emp()
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker = NULL;
		if (did == 1)
		{
			worker = new employee(id, name, did);
		}
		else if (did == 2)
		{
			worker = new manager(id, name, did);
		}
		else
		{
			worker = new boss(id, name, did);
		}
		this->m_emparray[index] = worker;
		index++;
	}
}
void workmanager::show_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_empnum; i++)
		{
			this->m_emparray[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}

int workmanager::isexist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_empnum; i++)
	{
		if (this->m_emparray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void workmanager::del_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->isexist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_empnum - 1; i++)
			{
				this->m_emparray[i] = this->m_emparray[i + 1];
			}
			this->m_empnum--;

			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workmanager::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		int ref = this->isexist(id);
		if (ref != -1)
		{
			delete this->m_emparray[ref];

			int newid = 0;
			string newname = " ";
			int dselect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newid;

			cout << "请输入新姓名：" << endl;
			cin >> newname;

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dselect;

			worker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new employee(newid, newname, dselect);
				break;
			case 2:
				worker = new manager(newid, newname, dselect);
				break;
			case 3:
				worker = new boss(newid, newname, dselect);
				break;
			default:
				break;
			}
			this->m_emparray[ref] = worker;

			cout << "修改成功！" << endl;

			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workmanager::find_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ref = isexist(id);
			if (ref != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_emparray[ref]->showinfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < m_empnum; i++)
			{
				if (m_emparray[i]->m_name == name)
				{
					cout << "查找成功，职工编号为："
						<< m_emparray[i]->m_id
						<< "号的信息如下：" << endl;

					flag = true;

					this->m_emparray[i]->showinfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workmanager::sort_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;


		int select = 0;
		cin >> select;


		for (int i = 0; i < m_empnum; i++)
		{
			int minormax = i;

			for (int j = i + 1; j < m_empnum; j++)
			{
				if (select == 1)
				{
					if (m_emparray[minormax]->m_id > m_emparray[j]->m_id)
					{
						minormax = j;
					}
				}
				else if(select==2)
				{
					if (m_emparray[minormax]->m_id < m_emparray[j]->m_id)
					{
						minormax = j;
					}
				}
				if (select != 1 && select != 2)
				{
					cout << "输入选项有误！" << endl;
					return;
				}

			}
			if (i != minormax)
			{
				worker* temp = m_emparray[i];
				m_emparray[i] = m_emparray[minormax];
				m_emparray[minormax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->save();
		this->show_emp();
	}
}
void workmanager::clean_file()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(filename, ios::trunc);
		ofs.close();

		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				if (this->m_emparray[i] != NULL)
				{
					delete this->m_emparray[i];
				}
			}
			this->m_empnum = 0;
			delete[]this->m_emparray;
			this->m_emparray = NULL;
			this->m_fileisempty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}