#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int n = 20, m = 20;
    cout << n << " " << m << "\n";
    cout << 5 << " " << 0 << " " << 0 << " " << 5 << "\n";  // 메두사, 공원

    for (int i = 0; i < m; i++) {
        int x = rand() % n;
        int y = rand() % n;
        cout << x << " " << y << " ";
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = (rand() % 10 < 2) ? 1 : 0;  // 20% 확률로 장애물
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;
}
