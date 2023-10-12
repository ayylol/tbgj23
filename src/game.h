#include "util.h"

struct Actor {
    char character;
    struct Vec2 pos;
};

struct Game {
    struct Actor p1;
    struct Actor p2;
    uint8_t turn;
    uint8_t *board;
    struct Vec2 bound;
};

struct Vec2 actor_move(struct Actor *a, struct Vec2 move);

void init_game();
void play_game();
void draw_map();
