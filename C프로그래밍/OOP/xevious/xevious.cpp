#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "xevious.h"

void set_color(unsigned short text, unsigned short back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

#define RED 4
#define YELLOW 6
#define GREEN 10
#define GRAY 8
#define WHITE 15

class IGame {  // �����̶� ������ (���� ������ ���� �𸣰�����)��� �� ��Ģ�� ������ ���� �ϰڴ�.
    // �� ����� �ϰڴ�. = �������̽�
public:
    virtual ~IGame() {}
    virtual void game_init(void) = 0;
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



// ����콺�� IGame �������̽��� ���� ���� �Լ��� ��� �����ؾ� �����Ҽ� �ִ�.
class Xevious : public IGame {
public:
    bool game_running = false; // qqq game_running
    bool demo_running = true;

    // �÷��̾�� ���� ��ġ
    int player_pos = SCREEN_WIDTH / 2;
    int enemy_pos = SCREEN_WIDTH / 2;
    int bullet_pos = -1;

    Xevious() {
        // ����콺 ���� ��ü ������ �ʿ��� ���� �ֱ�
        game_running = false;
        demo_running = true;
    }
    ~Xevious() {
        // ����콺 ���� ��ü �Ҹ�� �ʿ��� ���� �ֱ�
        game_running = false;
        demo_running = false;
    }
    void game_init(void) override;
    void game_demo(void) override;
    // void game_start(void) override; // ĳ���� ���õ� ����� ���ڴ�.
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
//    a = rand() % 70 + 3; //x��ǥ
//    b = rand() % 25 + 3; //y��ǥ
//    //�ʹ� �����ų� �ʹ� ���� �ʰ�
//}


void Xevious::game_play(void) { // draw_screen�� update screen �Լ��� ��ħ
    system("cls");
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (i == SCREEN_HEIGHT - 1 && j == player_pos) {
                printf("<-*->"); // �÷��̾�
            }
            else if (i == 0 && j == enemy_pos) {
                printf("[-|-]"); // ��
            }
            else if (i == bullet_pos && j == player_pos) {
                printf("+"); // �Ѿ�
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    if (bullet_pos > 0) bullet_pos--; // �Ѿ� ���� �̵�
    if (bullet_pos == 0 && player_pos == enemy_pos) {
        printf("���� �����߽��ϴ�!\n");
        game_running = false;
        //exit(0); // ���� ����
    }
}

void Xevious::button_left_press(void) {
    if (player_pos > 0) { player_pos--; }  // ���� �̵�
}
void Xevious::button_right_press(void) {
    //printf("yyy\r\n");
    if (player_pos < SCREEN_WIDTH - 1) { player_pos++; } // ������ �̵�w
}

void Xevious::button_up_press(void) {
    // �̱���
}
void Xevious::button_down_press(void) {
    // �̱���
}

void Xevious::button_01_press(void) {
    //printf("fire\r\n");
    if (bullet_pos == -1) { bullet_pos = SCREEN_HEIGHT - 2; }// �Ѿ� �߻� 
}

void Xevious::button_02_press(void) {
    //printf("bomb\r\n");
    // �̱���
}

void Xevious::game_over(void) { // ���� void end_screen() �ε� �������̽��� ����
    system("cls");
    gotoxy(36, 14);
    printf("The End");
    Sleep(2);
}

//void xevious_game_draw(void) {
//    draw_screen();
//    update_game();
//}

void Xevious::game_init(void) { // ���� setting �Լ����µ� �������̽��� ����
    //�ܼ�â ����
    //system("title ��Ʈ�� ã�Ƽ�");
    //system("mode con:cols=80 lines=30");

    //Ŀ�� ����
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.dwSize = 1;
    ConsoleCursor.bVisible = 0; //Ŀ�� �����
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void Xevious::key_input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'a' && player_pos > 0) { player_pos--; }  // ���� �̵�
        else if (ch == 'd' && player_pos < SCREEN_WIDTH - 1) { player_pos++; } // ������ �̵�w
        else if (ch == 'w' && bullet_pos == -1) { bullet_pos = SCREEN_HEIGHT - 2; }// �Ѿ� �߻� 
    }
}

void Xevious::game_demo(void) { // ���� start_screen(); �Լ����µ� game_demo �������̽��� ����
    int tic = 0;

    while (demo_running) {

        //��Ʈ ��¦��¦
        if (tic % 2 == 0) {
            gotoxy(27, 12);
            set_color(GREEN, 0);
            printf("������ Let's defeat the aliens! ������");
        }
        else if (tic % 2 == 1) {
            gotoxy(27, 12);
            printf("������ Let's defeat the aliens! ������");
        }

        gotoxy(34, 16);
        printf("Press '0' to start the game");

        if (_kbhit()) {
            char ch = _getch();
            if (ch == '0') {
                demo_running = false;
                game_running = true;
            }
        }
        Sleep(400);
        tic++;


        system("cls");

        set_color(WHITE, 0);
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

        Sleep(50); // ���� �ӵ� ����
    }

    xevious.game_over();
    return 0;
}

/*
C���� ������ ���

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
        Sleep(50); // ���� �ӵ� ����
    }
    end_screen();
    return 0;
}
*/
