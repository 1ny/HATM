#include "employee.h"

int main() {
	Manage List;
	int cmd = 0;

	printMenu();
	cout << "select number: ";
	cin >> cmd;

	while (1) {
		switch (cmd) {
		case CMD_HIRE_EMPLOYEE:
			addEmployee(&List);
			break;
		case CMD_FIRE_EMPLOYEE:

			break;
		case CMD_PROMOTE_EMPLOYEE:
			addEmployee(&List);
			break;
		case CMD_LIST_ALL:
			printList(&List);
			break;
		case CMD_LIST_ALL_CURR:
			
			break;
		case CMD_LIST_ALL_FORMER:

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

		if (cmd <= 0 || cmd > 6) break;
	}

	return 0;
}