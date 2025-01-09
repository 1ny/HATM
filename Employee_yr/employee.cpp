#include "employee.h"

void printMenu() {
	cout << "Employee Database" << endl;
	cout << "------------------" << endl;
	cout << "1) Hire a new employee" << endl;
	cout << "2) Fire an employee" << endl;
	cout << "3) Promote an employee" << endl;
	cout << "4) List all employees" << endl;
	cout << "5) List all current employees" << endl;
	cout << "6) List all former employees" << endl;
	cout << "0) Quit" << endl;
	cout << endl;
}

void addEmployee(Manage* pList) {
	string pFst_name;
	string pLst_name;

	cout << "First name? ";
	cin >> pFst_name;
	cout << "Last name? ";
	cin >> pLst_name;

	pList->p[pList->count].setInfo(pFst_name, pLst_name, pList->count + 1000);

	pList->count++;
}

void delEmployee(Manage* pList) {
	int num;
	
	cout << "Employee number? ";
	cin >> num;
	
	pList->p[num - 1000].setStat(STAT_FORMER);

	cout << "Employee " << num << " terminated." << endl;
}

void promoteEmployee(Manage* pList) {
	int promote;
	int num;

	cout << "Employee number? ";
	cin >> num;

	cout << "How much of a raise? ";
	cin >> promote;

	pList->p[num - 1000].addSalary(promote);
}

void printAllList(Manage* pList) {
	for (int i = 0; i < pList->count; i++) {
		pList->p[i].displayInfo();
		cout << endl;
	}
}

/* current employee list */
void printCurrList(Manage* pList) {
	for (int i = 0; i < pList->count; i++) {
		if (pList->p[i].getStat() == STAT_CURRENT) {
			pList->p[i].displayInfo();
			cout << endl;
		}
	}
}

/* former employee list */
void printFormList(Manage* pList) {
	for (int i = 0; i < pList->count; i++) {
		if (pList->p[i].getStat() == STAT_FORMER) {
			pList->p[i].displayInfo();
			cout << endl;
		}
	}
}