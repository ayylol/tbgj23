#include <ncurses.h>

struct Vec2 {
    int32_t x;
    int32_t y;
};
struct Vec2 
add_vec2(struct Vec2 a, struct Vec2 b) {
    return (struct Vec2) {
        .x = a.x + b.x, 
        .y = a.y + b.y };
}

struct Actor {
    char character;
    struct Vec2 pos;
};
struct Vec2 
actor_move(struct Actor *a, struct Vec2 move){
    struct Vec2 pos_after = add_vec2(a->pos, move);
    // Check collision
    if ( true ){
        a->pos = pos_after;
    }
    return a->pos;
}
enum Attribute {
    ATTR_CAN_PLACE  = 0b0001,
    ATTR_IS_HOUSE   = 0b0001,
    ATTR_OBSTACLE   = 0b0010,
    ATTR_HAS_SIGN   = 0b0100,
    ATTR_INFLUENCE  = 0b1000,
};
enum Tile {
    T_ROAD          = 0b00,
    T_GRASS         = ATTR_CAN_PLACE,
    T_OBSTACLE      = ATTR_OBSTACLE,
    T_HOUSE         = ATTR_OBSTACLE | ATTR_IS_HOUSE
};

int 
main(){
    uint32_t ch=0;
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);

    struct Actor player={.character = '&', .pos = {.x=0,.y=0}};
    while( ch != 'q' ) {
        mvaddch(player.pos.y, player.pos.x,player.character|A_BOLD);
        refresh();
        ch = getch();
        struct Vec2 move = {0,0};
        if (ch == KEY_LEFT) move.x -= 1;
        if (ch == KEY_RIGHT) move.x += 1;
        if (ch == KEY_DOWN) move.y += 1;
        if (ch == KEY_UP) move.y -= 1;
        mvaddch(player.pos.y, player.pos.x,' ');
        actor_move(&player,move);
    }
    endwin();
    return 0;
}

