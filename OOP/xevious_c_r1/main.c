#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "key_driver.h"

#include "game_pack/xevious/r2/xevious.h"
//#include "game_pack/tetris/r1/tetris.h"
//#include "game_pack/baseball/r1/baseball.h"
//#include "game_pack/updown/r1/updown.h"

extern bool running;
extern bool demo_running;

static void button_01_press(void (*callback)(void)) { callback(); } // left
static void button_02_press(void (*callback)(void)) { callback(); } // right
static void button_03_press(void (*callback)(void)) { callback(); } // up
static void button_04_press(void (*callback)(void)) { callback(); } // down

static void button_05_press(void (*callback)(void)) { callback(); } // button A
static void button_06_press(void (*callback)(void)) { callback(); } // B
static void button_07_press(void (*callback)(void)) { callback(); } // D
static void button_08_press(void (*callback)(void)) { callback(); } // E
static void button_09_press(void (*callback)(void)) { callback(); } // F
static void button_10_press(void (*callback)(void)) { callback(); } // G

static void button_11_press(void (*callback)(void)) { callback(); } // coin
static void button_12_press(void (*callback)(void)) { callback(); } // start

// 이건 game_fsm.c를 만들어 넣는게 좋겠다.
// 일단 동작되는 것만 볼라고 여기에 구현했다.
//static game_draw(&xeviou_game_draw);
static void game_draw(void (*callback)(void)) { callback(); } // 각 게임의 draw 함수를 호출한다.
static void game_over(void (*callback)(void)) { callback(); }
static void game_init(void (*callback)(void)) { callback(); }
static void game_demo(void (*callback)(void)) { callback(); }

int main(void) {
    key_init();
    printf("aa Press any key...\r\n");
    uint16_t key_code = 0;

    game_init(&xevious_game_init);
    while (demo_running) {
        game_demo(&xevious_game_demo);
        key_code = key_get_code();
        switch (key_code) {
        case KEY_0:
            //printf("000\r\n");
            //button_10_press(&xevious_init);
            demo_running = false;
            running = true;
            break;
        }

    }

    while (running) {
        //key_read();
        key_code = key_get_code();

        switch (key_code) {
        case KEY_LEFT:
            //printf("aaa\r\n");
            button_01_press(&xevious_key_left);
            break;
        case KEY_RIGHT:
            //printf("bbb\r\n");
            button_02_press(&xevious_key_right);
            break;
        case KEY_UP:
            //printf("ccc\r\n");
            //button_03_press(&updown_key_up);
            break;

        case KEY_DOWN:
            //printf("ddd\r\n");
            //button_04_press(&updown_key_down);
            break;

        case KEY_SPACE:
            //printf("sss\r\n");
            button_05_press(&xevious_key_fire);
            break;

        case KEY_0:
            //printf("000\r\n");
            //button_10_press(&xevious_init);
            demo_running = false;
            running = true;
            break;

        case KEY_2:
            //button_06_press(&updown_key_bomb);
            break;

        case KEY_9: // insert coin
            //button_11_press(&updown_game_coin_inserted);
            break;

        }
        game_draw(&xevious_game_draw);
        Sleep(200);
    }

    //printf("Bye...\r\n");
    game_over(&xevious_game_over);
    return 0;
}