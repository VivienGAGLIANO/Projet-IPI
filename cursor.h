#ifndef _CURSOR_H
#define _CURSOR_H

//Direction type enumeration

enum direction {
    up, up_right, right, down_right, down, down_left, left, up_left
};
typedef enum direction direction;


//Cursor type definition

struct cursor {
    int pos_x, pos_y;
    direction dir;    
};
typedef struct cursor cursor;




#endif