#include <stdio.h>
#include <memory.h>
#if 0
inline __attribute__((always_inline)) int abs(int x) {
    return (x<0) ? -x : x;
#
#endif

#define CONSTANT 10

int main() {
    int a, b, c, d, e, f;

    // if(a == b && c == d && e == f) {return 0;}

    if(((a-b) | (c-d) | (e-f)) == 0) {return 0;}

#if 0
    int i, j;
    j = (i > CONSTANT) ? 1 : 0;
    int i, j;

    if(i > CONSTANT) {
        j = 1;
    } else {
        j = 0;
    }
#endif
#if 0
    int x = -5;
    int y = abs(x);
    int z = abs(y);

    int a, b;

    switch(a) {
        case 0: b = a + 5; break;
        case 1: b = a - 10; break;
        default : b = a * 25; break;
    }
#endif

#if 0
    if(a == 0) b = a + 5;
    else if(a == 1) b = a - 10;
    else b = a * 25;
#endif
#if 0
    int a, b;
    char chx;

    if(chx == 'a' || chx == 'A') b = a + 5;
    if(chx == 'm' || chx == 'M') b = a - 10;
    if(chx == 't' || chx == 'T') b = a * 25;
#endif

#if 0
    chx = chx | 0x20;
    if(chx == 'a') b = a + 5;
    if(chx == 'm') b = a - 10;
    if(chx == 't') b = a * 25;
#endif

#if 0
    int a[3][3][3];
    int b[3][3][3];

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            for(int k=0; k<3; k++) {
                a[i][j][k] = 0;
                b[i][j][k] = 0;
            }
        } 
    }
#endif

#if 0
    typedef struct {
        int element[3][3][3];
    } Three3DType;

    Three3DType a, *b;
    b = &a;
    memset(&a, 0, sizeof(a));

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            for(int k=0; k<3; k++) {
                printf("a[%d][%d][%d]=%d\n", i, j, k, a.element[i][j][k]);
            }
        } 
    }
#endif
}