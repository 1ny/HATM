#include <iostream>
#include <set>

using namespace std;

int main(void) {

    set<int> s;

    s.insert(1);
    s.insert(200);
    s.insert(-1);
    s.insert(3);

    set<int>::iterator iter;
    for (iter = s.begin(); iter != s.end(); iter++)
        printf("%d ", *iter);
    printf("\n");

    s.erase(200);
    s.clear();

    set<int>::reverse_iterator riter;
    for (riter = s.rbegin(); riter != s.rend(); riter++) {
        printf("%d ", *riter);
    }

    return 0;
}