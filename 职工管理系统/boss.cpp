#include"boss.h"
boss::boss(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}
void boss::showinfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getdeptname()
		<< "\t岗位职责：管理公司所有事务" << endl;
}
string boss::getdeptname()
{
	return string("总裁");
}