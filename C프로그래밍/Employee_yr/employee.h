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

#define STAT_CURRENT			(1)
#define STAT_FORMER				(0)

#define INIT_SALARY				(30000)

class Employee {
private:
	string firstName;
	string lastName;
	int status;	// 1: Current, 0: Former
	int num;
	int salary;

public:
	// 객체를 생성했다는 건 hiring 했다는 것~
	Employee() : status(STAT_CURRENT), salary(INIT_SALARY) {}	

	void setInfo(string pFirstName, string pLastName, int pNum) {
		this->firstName = pFirstName;
		this->lastName = pLastName;
		num = pNum;
	}
	void displayInfo() {
		cout << "Employee: " << lastName << ", " << firstName << endl;
		cout << "-------------------------" << endl;

		if (status == STAT_CURRENT) cout << "Current Employee" << endl;
		else cout << "Former Employee" << endl;

		cout << "Employee Number: " << num << endl;
		cout << "Salary: &" << salary << endl;
	}

	void setStat(int pStatus) {
		status = pStatus;
	}

	int getStat() {
		return status;
	}

	void addSalary(int promote) {
		salary += promote;
	}
};

class Manage {
public:
	Employee p[100];
	int count;

	Manage() : count(0) {}
};

/* Extern functions ************************************************************************************************************/
void printMenu();
void getCmd(int* cmd);
void addEmployee(Manage* pList);
void delEmployee(Manage* pList);
void promoteEmployee(Manage* pList);
void printAllList(Manage* pList);
void printCurrList(Manage* pList);
void printFormList(Manage* pList);

#endif /* __employee__ */