#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "xevious.h"


class IGame {  // 게임이란 게임은 (무슨 게임이 될지 모르겠지만)모두 이 규칙을 따르게 강제 하겠다.
    // 이 약속을 하겠다. = 인터페이스
public:
    virtual ~IGame() {}
    virtual void game_init(void) = 0;   // 순수 가상함수로 자식 클래스에게 오버라이딩 함수 구현 강제성을 부여한다..
    virtual void game_demo(void) = 0;
    virtual void game_play(void) = 0;
    virtual void game_over(void) = 0;

    virtual void button_left_press(void) = 0;
    virtual void button_right_press(void) = 0;
    virtual void button_up_press(void) = 0;
    virtual void button_down_press(void) = 0;

    virtual void button_01_press(void) = 0;
    virtual void button_02_press(void) = 0;
    //virtual void button_03_press(void) = 0;
    //virtual void button_04_press(void) = 0;
    //virtual void button_05_press(void) = 0;
    //virtual void button_06_press(void) = 0;
};



// 제비우스는 IGame 인터페이스의 순수 가상 함수를 모두 구현해야 생성할수 있다.
class Xevious : public IGame {
public:
    bool game_running = false; // qqq game_running
    bool demo_running = true;

    // 플레이어와 적의 위치
    int player_pos = SCREEN_WIDTH / 2;
    int enemy_pos = SCREEN_WIDTH / 2;
    int bullet_pos = -1;

    Xevious() {
        // 제비우스 게임 객체 생성시 필요한 설정 넣기
        game_running = false;
        demo_running = true;
    }
    ~Xevious() {
        // 제비우스 게임 객체 소멸시 필요한 설정 넣기
        game_running = false;
        demo_running = false;
    }
    void game_init(void) override;
    void game_demo(void) override;
    // void game_start(void) override; // 캐릭터 선택도 만들면 좋겠다.
    void game_play(void) override;
    void game_over(void) override;

    void button_left_press(void) override;
    void button_right_press(void) override;
    void button_up_press(void) override;
    void button_down_press(void) override;
    void button_01_press(void) override;
    void button_02_press(void) override;
    //void button_03_press() override{}
    //void button_04_press() override{}
    //void button_05_press() override{}
    //void button_06_press() override{}

    void gotoxy(int, int);
    //void draw_screen(void);
    //void update_game(void);

    void key_input(void);
};

void Xevious::gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//int a;
//int b;
//void h_rand(void) {
//    srand((unsigned int)time(NULL));
//    a = rand() % 70 + 3; //x좌표
//    b = rand() % 25 + 3; //y좌표
//    //너무 가깝거나 너무 멀지 않게
//}


void Xevious::game_play(void) { // draw_screen과 update screen 함수를 합침
    system("cls");
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (i == SCREEN_HEIGHT - 1 && j == player_pos) {
                printf("<-*->"); // 플레이어
            }
            else if (i == 0 && j == enemy_pos) {
                printf("[-|-]"); // 적
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

    if (bullet_pos > 0) bullet_pos--; // 총알 위로 이동
    if (bullet_pos == 0 && player_pos == enemy_pos) {
        printf("적을 격파했습니다!\n");
        game_running = false;
        //exit(0); // 게임 종료
    }
}

void Xevious::button_left_press(void) {
    if (player_pos > 0) { player_pos--; }  // 왼쪽 이동
}
void Xevious::button_right_press(void) {
    //printf("yyy\r\n");
    if (player_pos < SCREEN_WIDTH - 1) { player_pos++; } // 오른쪽 이동w
}

void Xevious::button_up_press(void) {
    // 미구현
}
void Xevious::button_down_press(void) {
    // 미구현
}

void Xevious::button_01_press(void) {
    //printf("fire\r\n");
    if (bullet_pos == -1) { bullet_pos = SCREEN_HEIGHT - 2; }// 총알 발사 
}

void Xevious::button_02_press(void) {
    //printf("bomb\r\n");
    // 미구현
}

void Xevious::game_over(void) { // 원래 void end_screen() 인데 인터페이스에 맞춤
    system("cls");
    gotoxy(36, 14);
    printf("The End");
    Sleep(2);
}

//void xevious_game_draw(void) {
//    draw_screen();
//    update_game();
//}

void Xevious::game_init(void) { // 원래 setting 함수였는데 인터페이스에 맞춤
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

void Xevious::key_input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'a' && player_pos > 0) { player_pos--; }  // 왼쪽 이동
        else if (ch == 'd' && player_pos < SCREEN_WIDTH - 1) { player_pos++; } // 오른쪽 이동w
        else if (ch == 'w' && bullet_pos == -1) { bullet_pos = SCREEN_HEIGHT - 2; }// 총알 발사 
    }
}

void Xevious::game_demo(void) { // 원래 start_screen(); 함수였는데 game_demo 인터페이스에 맞춤
    int tic = 0;

    while (demo_running) {

        //하트 반짝반짝
        if (tic % 2 == 0) {
            gotoxy(27, 12);
            printf("♡♥♡ Let's defeat the aliens! ♡♥♡");
        }
        else if (tic % 2 == 1) {
            gotoxy(27, 12);
            printf("♥♡♥ Let's defeat the aliens! ♥♡♥");
        }

        gotoxy(34, 16);
        printf("Press '0' to start the game");

        if (_kbhit()) {
            char ch = _getch();
            if (ch == '0') { 
                demo_running= false; 
                game_running = true;
            }
        }
        Sleep(400);
        tic++;


        system("cls");
    }
}

int main() {
    Xevious xevious;
    xevious.game_init();
    xevious.game_demo();

    while (xevious.game_running) {
        //draw_screen();
        //handle_input();
        xevious.game_play();

        //xevious.button_left_press();
        //xevious.button_right_press();
        //xevious.button_up_press();
        //xevious.button_down_press();
        //xevious.button_01_press();
        //xevious.button_02_press();

        xevious.key_input();

        Sleep(50); // 게임 속도 조절
    }

    xevious.game_over();
    return 0;
}

/*
C에서 돌릴때 모양

int main() {
    setting();
    start_screen();

    while (!game_over) {
        draw_screen();
        //handle_input();
        updown_key_left();
        updown_key_right();
        updown_key_fire();
        update_game();
        Sleep(50); // 게임 속도 조절
    }
    end_screen();
    return 0;
}
*/
