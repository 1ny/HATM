#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

bool running = true;

//bool game_over = false;

#define RED 4
#define YELLOW 6
#define GREEN 10
#define GRAY 8
#define WHITE 15

void set_color(unsigned short text, unsigned short back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int a;
int b;
void h_rand() {
    srand((unsigned int)time(NULL));
    a = rand() % 70 + 3; //x좌표
    b = rand() % 25 + 3; //y좌표
    //너무 가깝거나 너무 멀지 않게
}

void setting() {
    //콘솔창 설정
    //system("title 하트를 찾아서");
    //system("mode con:cols=80 lines=30");

    //커서 설정
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.dwSize = 1;
    ConsoleCursor.bVisible = 0; //커서 숨기기
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}


int key = 0;
void start_screen() {

    int tic = 0;

    while (1) {

        //하트 반짝반짝
        if (tic % 2 == 0) {
            gotoxy(27, 12);
            set_color(YELLOW, 0);
            printf("♡♥♡ Let's defeat the aliens! ♡♥♡");
        }
        else if (tic % 2 == 1) {
            gotoxy(27, 12);
            set_color(RED, 0);
            printf("♥♡♥ Let's defeat the aliens! ♥♡♥");
        }

        gotoxy(34, 16);
        printf("Press '0' to start the game");

        Sleep(400);
        tic++;

        if (_kbhit()) { //'스페이스 바' 입력받으면 시작
            key = _getch();
            if (key == '0') {
                running = true;
                system("cls");
                break;
            }
        }
    }
    set_color(WHITE, 0);
}


// 게임 화면 크기
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 10

// 플레이어와 적의 위치
int player_pos = SCREEN_WIDTH / 2;
int enemy_pos = SCREEN_WIDTH / 2;
int bullet_pos = -1;

// 화면 그리기
void draw_screen() {
    system("cls");
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (i == SCREEN_HEIGHT - 1 && j == player_pos) {
                set_color(GREEN, 0);
                printf("<-*->"); // 플레이어
                set_color(WHITE, 0);
            }
            else if (i == 0 && j == enemy_pos) {
                set_color(RED, 0);
                printf("[-|-]"); // 적
                set_color(WHITE, 0);

            }
            else if (i == bullet_pos && j == player_pos) {
                printf("+"); // 총알
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// 게임 업데이트
void update_game() {
    if (bullet_pos > 0) bullet_pos--; // 총알 위로 이동
    if (bullet_pos == 0 && player_pos == enemy_pos) {
        printf("적을 격파했습니다!\n");
        running = false;
        //exit(0); // 게임 종료
    }
}

// 사용자 입력 처리
// 원래 코드가 이런데 이를 
//updown_key_left
//updown_key_right
//updown_key_fire
//로 바꿔보자.
void handle_input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'a' && player_pos > 0) { player_pos--; }  // 왼쪽 이동
        else if (ch == 'd' && player_pos < SCREEN_WIDTH - 1) { player_pos++; } // 오른쪽 이동w
        else if (ch == 'w' && bullet_pos == -1) { bullet_pos = SCREEN_HEIGHT - 2; }// 총알 발사 
    }
}

//void xevious_key_left(void) {
//    if (player_pos > 0) { player_pos--; }  // 왼쪽 이동
//}
//void xevious_key_right(void) {
//    if (player_pos < SCREEN_WIDTH - 1) { player_pos++; } // 오른쪽 이동w
//}
//
//void xevious_key_fire(void) {
//    if (bullet_pos == -1) { bullet_pos = SCREEN_HEIGHT - 2; }// 총알 발사 
//}


void end_screen() {
    system("cls");
    gotoxy(36, 14);
    printf("The End");
}

void xevious_game_draw() {
    draw_screen();
    update_game();
}

void xevious_game_init() {
    setting();
    start_screen();
}

void xevious_game_over() {
    end_screen();
}

int main() {
    setting();
    start_screen();

    while (running) {
        draw_screen();
        handle_input();
        //updown_key_left();
        //updown_key_right();
        //updown_key_fire();
        update_game();
        Sleep(50); // 게임 속도 조절
    }
    end_screen();
    return 0;
}
