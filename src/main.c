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
struct Vec2 screen_size = {.x=0,.y=0};

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
// Influence Colors
enum Color {
    NONE            = 0,
    RED_PLAYER      = 1,
    RED_LOW         = 2,
    RED_MID         = 3,
    RED_HIGH        = 4,
    BLUE_PLAYER     = 5,
    BLUE_LOW        = 6,
    BLUE_MID        = 7,
    BLUE_HIGH       = 8,
};

int 
main(){
    uint32_t ch=0;
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    start_color();
    curs_set(0);
    getmaxyx(stdscr, screen_size.y, screen_size.x);
    init_pair(NONE, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_PLAYER, COLOR_RED, COLOR_BLACK);
    init_pair(RED_LOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(RED_MID, COLOR_RED, COLOR_YELLOW);
    init_pair(RED_HIGH, COLOR_YELLOW, COLOR_RED);
    init_pair(BLUE_PLAYER, COLOR_BLUE, COLOR_BLACK);
    init_pair(BLUE_LOW, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLUE_MID, COLOR_BLUE, COLOR_CYAN);
    init_pair(BLUE_HIGH, COLOR_CYAN, COLOR_BLUE);

    struct Actor player={.character = '&', .pos = {.x=screen_size.x/2,.y=screen_size.y/2}};
    int i = 0;
    while( ch != 'q' ) {
        i= (i+1)%9;
        getmaxyx(stdscr, screen_size.y, screen_size.x);
        attron(COLOR_PAIR(i));
        mvaddch(player.pos.y, player.pos.x,player.character);
        attroff(COLOR_PAIR(i));
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

