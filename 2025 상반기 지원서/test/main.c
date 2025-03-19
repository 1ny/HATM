#include <stdio.h>

typedef unsigned char uint8_t;

typedef struct{
    uint8_t a:2;
    uint8_t b:2;
    uint8_t c:3;
    uint8_t d:1;
} test;

typedef union {
    struct{
        uint8_t BIT1:2;
        uint8_t BIT2:2;
        uint8_t BIT3:3;
        uint8_t BIT4:1;
    } A;
    uint8_t B;
} test_2;

int main() {
    test_2 Test_2;
    test Test;

    Test_2.B = 0x00;

    Test_2.A.BIT1 = 0x1;
    Test_2.A.BIT4 = 0x1;

    Test.a = 0x1;
    Test.b = 0x0;
    Test.c = 0x0;
    Test.d = 0x1;

    uint8_t result = Test.a | (Test.b << 2) | (Test.c << 4) | (Test.d << 7);

    printf("0x%02x\n", result);
    printf("0x%02x\n", Test_2.B);
}