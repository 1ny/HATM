#include "employee.h"

int main() {
	Manage pList;
	int cmd = 0;

	printMenu();
	cout << "select number: ";
	cin >> cmd;

	while (1) {
		switch (cmd) {
		case CMD_HIRE_EMPLOYEE:
			addEmployee(&pList);
			break;
		case CMD_FIRE_EMPLOYEE:
			delEmployee(&pList);
			break;
		case CMD_PROMOTE_EMPLOYEE:
			promoteEmployee(&pList);
			break;
		case CMD_LIST_ALL:
			printAllList(&pList);
			break;
		case CMD_LIST_ALL_CURR:
			printCurrList(&pList);
			break;
		case CMD_LIST_ALL_FORMER:
			printFormList(&pList);
			break;
		case CMD_QUIT:
			break;
		default:
			cout << "wrong command" << endl;
			break;
		}

		cout << endl;
		printMenu();
		cout << "select number: ";
		cin >> cmd;

		if (cmd == 0) break;
	}

	return 0;
}