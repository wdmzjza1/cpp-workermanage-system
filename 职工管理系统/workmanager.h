#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include<fstream>
#define filename "empfile.txt"

class workmanager
{
public:
	workmanager();
	void show_menu();
	void exitsystem();
	void add_emp();
	void save();
	int get_empnum();
	void init_emp();
	void show_emp();
	void del_emp();
	int isexist(int id);
	void mod_emp();
	void find_emp();
	void sort_emp();
	void clean_file();

public:
	int m_empnum;
	worker ** m_emparray;
	bool m_fileisempty;
	
	~workmanager();

};
