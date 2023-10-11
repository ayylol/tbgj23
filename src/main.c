#include <ncurses.h>
#include <unistd.h>

struct Vec2 {
    int x;
    int y;
};

struct Actor {
    struct Vec2 pos;
};

struct Vec2 add_vec2(struct Vec2 a, struct Vec2 b) {
    return (struct Vec2) {
        .x = a.x + b.x, 
        .y = a.y + b.y };
}
struct Vec2 actor_move(struct Actor *a, struct Vec2 move);

int main(int argc, char *argv[]){
    int ch=0;
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);

    struct Actor player={.pos = {.x=0,.y=0}};
    while( ch != 'q')
    {
        mvaddch(player.pos.y, player.pos.x,'A');
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

struct Vec2 actor_move(struct Actor *a, struct Vec2 move){
    struct Vec2 pos_after = add_vec2(a->pos, move);
    // Check collision
    if ( true ){
        a->pos = pos_after;
    }
    return a->pos;
}
