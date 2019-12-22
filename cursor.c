#include <stdio.h>
#include "cursor.h"
#include "matrix.h"

/** @requires : nothing 
 *  @assings : modifies cursor's position attributes
 *  @ensures : actualizes the cursor's position in the matrix depending on the direction, knowing that the matrix is toric 
*/
void move(cursor *curs, direction dir, matrix m) {
    switch (dir) {
        case up : 
            curs->pos_y -= 1 % m.height;
            break;        
        case up_right : 
            curs->pos_y -= 1 % m.height;
            curs->pos_x += 1 % m.width;
            break;    
        case right :
            curs->pos_x += 1 % m.width;
            break;    
        case down_right :
            curs->pos_y += 1 % m.height;
            curs->pos_x += 1 % m.width;
            break;    
        case down :
            curs->pos_y += 1 % m.height;
            break;
        case down_left :
            curs->pos_y += 1 % m.height;
            curs->pos_x -= 1 % m.width;
            break;
        case left :
            curs->pos_x -= 1 % m.width;
            break;
        case up_left :
            curs->pos_y -= 1 % m.height;
            curs->pos_x -= 1 % m.width;
            break;
    }
}
