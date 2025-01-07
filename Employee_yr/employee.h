#ifndef __employee__
#define __employee__

/*************************************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

/*************************************************************************************************************/

#define CMD_HIRE_EMPLOYEE		(1)
#define CMD_FIRE_EMPLOYEE		(2)
#define CMD_PROMOTE_EMPLOYEE	(3)
#define CMD_LIST_ALL			(4)
#define CMD_LIST_ALL_CURR		(5)
#define CMD_LIST_ALL_FORMER		(6)
#define CMD_QUIT				(0)

class Employee {
private:
	string fstName;
	string lstName;
	int status;	// 1: Current, 0: Former
	int num;
	int salary;

public:
	Employee() {
		status = 1;	// 생성했다는 건 hiring 했다는 것~
		salary = 30000;
	}
	void setInfo(string pFirstName, string pLastName, int pNum) {
		this->fstName = pFirstName;
		this->lstName = pLastName;
		num = pNum;
	}
	void getInfo() {
		cout << "Employee: " << lstName << ", " << fstName << endl;
		cout << "-------------------------" << endl;

		if (status == 1) cout << "Current Employee" << endl;
		else cout << "Former Employee" << endl;

		cout << "Employee Number: " << num << endl;
		cout << "Salary: &" << salary << endl;
	}
};

class Manage {
public:
	Employee p[100];
	int count;

	Manage() {
		count = 0;
	}
};

/* Extern functions ************************************************************************************************************/
extern void printMenu();
extern void getCmd(int* cmd);
extern void addEmployee(Manage* List);
extern void printList(Manage* List);

#endif /* __employee__ */