#include "util.h"

struct Vec2 screen_size = {.x=0,.y=0};

struct Vec2 
add_vec2(struct Vec2 a, struct Vec2 b) {
    return (struct Vec2) {
        .x = a.x + b.x, 
        .y = a.y + b.y };
}

void
init_engine() {
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    start_color();
    curs_set(0);
    init_pair(NONE, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_PLAYER, COLOR_RED, COLOR_BLACK);
    init_pair(RED_LOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(RED_MID, COLOR_RED, COLOR_YELLOW);
    init_pair(RED_HIGH, COLOR_YELLOW, COLOR_RED);
    init_pair(BLUE_PLAYER, COLOR_BLUE, COLOR_BLACK);
    init_pair(BLUE_LOW, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLUE_MID, COLOR_BLUE, COLOR_CYAN);
    init_pair(BLUE_HIGH, COLOR_CYAN, COLOR_BLUE);
    getmaxyx(stdscr, screen_size.y, screen_size.x);
}

void
stop_engine() {
    endwin();
}

char get_tile (uint8_t val){
    switch (val){
        case T_ROAD:
            return '#';
        case T_GRASS:
            return 'G';
        case T_OBSTACLE:
            return 'O';
        case T_HOUSE:
            return 'H';
        default:
            return '!';
    }
}
