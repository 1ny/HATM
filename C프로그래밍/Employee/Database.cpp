#include <iostream>
#include <stdexcept>
#include "Database.h"

using namespace std;

namespace Records {
    // ���ο� Employee ��ü ���� �� vector�� �߰�
    Employee& Database::addEmployee(const string& firstName, const string& lastName)
    {
        Employee theEmployee(firstName, lastName);
        // ���� ������ ���ο� ��ȣ�� �ޱ����� 1 ����
        theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
        theEmployee.hire();
        mEmployees.push_back(theEmployee);

        return mEmployees[mEmployees.size() - 1];
    }

    // ������� for���� ����Ͽ� mEmployees�� �ִ� ��� ������ ���鼭
    // ���޵� ������ȣ�� ���� ������ ã�´�.
    Employee& Database::getEmployee(int employeeNumber)
    {
        for (auto& employee : mEmployees) {
            if (employee.getEmployeeNumber() == employeeNumber) {
                return employee;
            }
        }
        // ���ٸ� ���� �߻�
        throw logic_error("No employee found.");
    }

    // ������ ��, �̸��� �޾ƿ� �ش� ������ �ִ��� ��ȸ
    Employee& Database::getEmployee(const string& firstName, const string& lastName)
    {
        for (auto& employee : mEmployees) {
            if (employee.getFirstName() == firstName &&
                employee.getLastName() == lastName) {
                return employee;
            }
        }
        // ���ٸ� ���� �߻�
        throw logic_error("No employee found.");
    }

    // ��� ������ ���Ͽ� Loop�� ���鼭 ���� ���ǿ� �����ϴ�
    // ������ ������ �ֿܼ� ���
    void Database::displayAll() const
    {
        for (const auto& employee : mEmployees) {
            employee.display();
        }
    }

    // ���� �������� ��� ���� ������ ����Ѵ�.
    void Database::displayCurrent() const
    {
        for (const auto& employee : mEmployees) {
            if (employee.isHired())
                employee.display();
        }
    }

    // ���ſ� �ٳ���� ������ ��ȸ�Ѵ�.
    void Database::displayFormer() const
    {
        for (const auto& employee : mEmployees) {
            if (!employee.isHired())
                employee.display();
        }
    }

}