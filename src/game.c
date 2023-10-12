#include "game.h"

// GAME
struct Game game;
uint8_t map[4][4] = {
    {T_ROAD,    T_GRASS,    T_GRASS,    T_ROAD},
    {T_ROAD,    T_HOUSE,    T_OBSTACLE, T_ROAD},
    {T_ROAD,    T_OBSTACLE, T_HOUSE,    T_ROAD},
    {T_ROAD,   T_GRASS,    T_GRASS,    T_ROAD}
};

struct Vec2 
actor_move(struct Actor *a, struct Vec2 move, struct Actor *b) {
    struct Vec2 pos_after = add_vec2(a->pos, move);
    uint8_t tile = *(game.board+(pos_after.x+pos_after.y*game.bound.x));
    // Check collision
    if ( pos_after.x >= 0 && pos_after.y >= 0 &&
        pos_after.x < game.bound.x && pos_after.y < game.bound.y &&
        !(b->pos.x == pos_after.x && b->pos.y == pos_after.y) &&
        !(tile & ATTR_OBSTACLE)
        ){
        a->pos = pos_after;
    }
    return a->pos;
}

void 
init_game(){
    init_engine();
    game.board = &map[0][0];
    game.bound = (struct Vec2){.x = 4, .y = 4};
    game.p1 = (struct Actor){.character = '$', .pos = {.x=0,.y=0}};
    game.p2 = (struct Actor){.character = '&', .pos = {.x=game.bound.x-1,.y=game.bound.y-1}};
    draw_map();
}

void 
play_game() {
    bool should_quit = false;
    while( !should_quit ) {
        getmaxyx(stdscr, screen_size.y, screen_size.x);
        refresh();
        should_quit = get_input();
        draw_map();
    }
    stop_engine();
}

void 
draw_map(){
    struct Vec2 zero = {
        .x = (screen_size.x-game.bound.x)/2, 
        .y = (screen_size.y-game.bound.y)/2, 
    };
    for (uint8_t y = 0; y < game.bound.y; ++y){
        for (uint8_t x = 0; x < game.bound.x; ++x){
            mvaddch(zero.y + y, zero.x + x, get_tile( *(game.board+(x+y*game.bound.x)) ));
        }
    }
    // Draw Players
    attron(COLOR_PAIR(RED_PLAYER));
    mvaddch(zero.y + game.p1.pos.y, zero.x + game.p1.pos.x,game.p1.character);
    attroff(COLOR_PAIR(RED_PLAYER));
    attron(COLOR_PAIR(BLUE_PLAYER));
    mvaddch(zero.y + game.p2.pos.y, zero.x + game.p2.pos.x,game.p2.character);
    attroff(COLOR_PAIR(BLUE_PLAYER));
}
bool
get_input(){
    uint32_t input = getch();
    struct Vec2 move = {0,0};
    switch (input){
    case 'q':
        return true;
    case KEY_LEFT:
        move.x -= 1;
        break;
    case KEY_RIGHT:
        move.x += 1;
        break;
    case KEY_DOWN:
        move.y += 1;
        break;
    case KEY_UP:
        move.y -= 1;
        break;
    }
    actor_move(&game.p1,move, &game.p2);
    return false;
}
