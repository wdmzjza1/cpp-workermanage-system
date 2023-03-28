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
		cout << "�ļ�������" << endl;
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
		cout << "�ļ�Ϊ�գ�" << endl;
		this->m_fileisempty = true;
		this->m_emparray = NULL;
		ifs.close();
		return;
	}
	int num = this->get_empnum();
	cout << "ְ������Ϊ:" << num << endl;
	this->m_empnum = num;

	this->m_emparray = new worker * [this->m_empnum];
	init_emp();
	for (int i = 0; i < m_empnum; i++)
	{
		cout << "ְ����:" << this->m_emparray[i]->m_id
			<< "\tְ��������" << this->m_emparray[i]->m_name
			<< "\t���ű�ţ�" << this->m_emparray[i]->m_deptid << endl;
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
	cout << "**********��ӭʹ��ְ��ϵͳ��************" << endl;
	cout << "**************0.�˳�����ϵͳ************" << endl;
	cout << "**************1.����ְ����Ϣ************" << endl;
	cout << "**************2.��ʾְ����Ϣ************" << endl;
	cout << "**************3.ɾ����ְְ��************" << endl;
	cout << "**************4.�޸�ְ����Ϣ************" << endl;
	cout << "**************5.����ְ����Ϣ************" << endl;
	cout << "**************6.���ձ������************" << endl;
	cout << "**************7.��������ĵ�************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}
void workmanager::exitsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void workmanager::add_emp()
{
	cout << "����������ְ������:" << endl;

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

			cout << "������� " << i + 1 << " ����ְ�����" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
		cout << "�ɹ����" << addnum << "����ְ����" << endl;

		//this->save();
	}
	else
	{
		cout << "��������" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
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
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workmanager::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;

		int ref = this->isexist(id);
		if (ref != -1)
		{
			delete this->m_emparray[ref];

			int newid = 0;
			string newname = " ";
			int dselect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newid;

			cout << "��������������" << endl;
			cin >> newname;

			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			cout << "�޸ĳɹ���" << endl;

			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workmanager::find_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ref = isexist(id);
			if (ref != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_emparray[ref]->showinfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < m_empnum; i++)
			{
				if (m_emparray[i]->m_name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<< m_emparray[i]->m_id
						<< "�ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_emparray[i]->showinfo();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workmanager::sort_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;


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
					cout << "����ѡ������" << endl;
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
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->show_emp();
	}
}
void workmanager::clean_file()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

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
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}