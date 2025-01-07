#include "employee.h"

void printMenu() {
	cout << "Employee Database" << endl;
	cout << "------------------" << endl;
	cout << "1) Hire a new employee" << endl;
	cout << "2) Fire an employee" << endl;
	cout << "4) List all employees" << endl;
	cout << "5) List all current employees" << endl;
	cout << "6) List all former employees" << endl;
	cout << "0) Quit" << endl;
	cout << endl;
}

void addEmployee(Manage* List) {
	string pFst_name;
	string pLst_name;

	cout << "First name? ";
	cin >> pFst_name;
	cout << "Last name? ";
	cin >> pLst_name;

	List->p[List->count].setInfo(pFst_name, pLst_name, List->count + 1000);

	List->count++;
}

void printList(Manage* List) {
	for (int i = 0; i < List->count; i++) {
		List->p[i].getInfo();
		cout << endl;
	}
}