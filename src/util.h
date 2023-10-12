#include <stdint.h>
#include <ncurses.h>

struct Vec2 {
    int32_t x;
    int32_t y;
};
struct Vec2 add_vec2(struct Vec2 a, struct Vec2 b);

extern struct Vec2 screen_size;

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
char get_tile (uint8_t val);

void init_engine();
void stop_engine();
