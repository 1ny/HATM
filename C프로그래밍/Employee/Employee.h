// Employee.h
#pragma once // ���� ������ ������ �ҷ����� �ʵ��� ��.

#include <string>

// Records��� ���ӽ����̽��� ���ϵ��� ����
namespace Records {
    // ���������� �⺻ �޿� ����
    const int kDefaultStartingSalary = 30000; // ����� �տ� k�� ���̴� ����

    class Employee {
        // �ٸ� �ڵ忡�� �������� ���ϵ��� private�� ������ �ɹ� ����
    private:
        std::string mFirstName;
        std::string mLastName;
        int mEmployeeNumber = -1;
        int mSalary = kDefaultStartingSalary;
        bool mHired = false;

    public:
        // default ������ & ��, �̸��� �޴� ������
        Employee() = default;
        Employee(const std::string& firstName, const std::string& lastName);

        // ���� type�� �Ű������� ����. �⺻���� ������ �־ �Ű������� ���ٸ� default������
        void promote(int raiseAmount = 1000);
        void demote(int demeritAmount = 1000);
        void hire(); // ���� ���
        void fire(); // ���� �ذ�.
        void display() const;// ���� ���� �ܼ� ���

        // getter & setter
        void setFirstName(const std::string& firstName);
        const std::string& getFirstName() const;

        void setLastName(const std::string& lastName);
        const std::string& getLastName() const;

        void setEmployeeNumber(int employeeNumber);
        int getEmployeeNumber() const;

        void setSalary(int newSalary);
        int getSalary() const;

        bool isHired() const;



    };
}