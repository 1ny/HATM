// Database.h
// std::vector Ŭ������ �̿��Ͽ� Employee ��ü ����
#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records {
    // ���� ������ ���� ������ȣ�� DB ���ο��� �ڵ� �Ҵ��� ���� ���۰��� ����� ����
    const int kFirstEmployeeNumber = 1000;

    class Database
    {
    public:
        // ��, �̸����� ���� ���� �߰�
        Employee& addEmployee(const std::string& firstName,
            const std::string& lastName);
        // ������ȣ�� ���� ��ȸ
        Employee& getEmployee(int employeeNumber);
        // ��, �̸����� ���� ��ȸ
        Employee& getEmployee(const std::string& firstName,
            const std::string& lastName);

        // ��� ���� ������ ���
        void displayAll() const;
        // ���� �������� ���� ���� ���
        void displayCurrent() const;
        // ����� ���� ���� ���
        void displayFormer() const;

    private:
        // mEmployees�� Employee ��ü�� ������ �ִ� �迭
        std::vector<Employee> mEmployees;
        // ���������� �Ҵ�� ���� ��ȣ�� ����ϸ� ����� �ʱ�ȭ
        int mNextEmployeeNumber = kFirstEmployeeNumber;
    };
}