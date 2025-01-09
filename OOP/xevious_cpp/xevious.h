#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>

// 게임 화면 크기
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 10

void gotoxy(int x, int y);
void h_rand(void);
void setting(void);
void start_screen(void);
void draw_screen(void);
void update_game(void);
//void handle_input();
void end_screen(void);

void xevious_key_left(void);
void xevious_key_right(void);
void xevious_key_fire(void);

void xevious_game_init(void);
void xevious_game_draw(void);
void xevious_game_over(void);
void xevious_game_demo(void);

