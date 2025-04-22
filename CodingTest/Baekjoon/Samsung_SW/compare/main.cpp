#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    ifstream fin1("output.txt");
    ifstream fin2("output2.txt");

    if (!fin1.is_open() || !fin2.is_open()) {
        cerr << "������ �� �� �����ϴ�.\n";
        return 1;
    }

    char ch1, ch2;
    int pos = 0;
    int line = 1, col = 1;

    while (true) {
        bool read1 = static_cast<bool>(fin1.get(ch1));
        bool read2 = static_cast<bool>(fin2.get(ch2));

        if (!read1 && !read2) break;

        if (read1 != read2 || ch1 != ch2) {
            cout << "�ٸ� �߰�! ��ġ: " << pos << " (�� " << line << ", �� " << col << ")\n";
            cout << "  output.txt:   '" << (read1 ? ch1 : '?') << "' (ASCII " << static_cast<int>(ch1) << ")\n";
            cout << "  output2.txt:  '" << (read2 ? ch2 : '?') << "' (ASCII " << static_cast<int>(ch2) << ")\n";
            return 0;
        }

        if (ch1 == '\n') {
            line++;
            col = 1;
        }
        else {
            col++;
        }

        pos++;
    }

    cout << "�� ������ ������ �����մϴ�.\n";
    return 0;
}
