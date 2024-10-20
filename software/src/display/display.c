#include "display.h"

point_t display_point_init( int x , int y ) {
    point_t point = {x, y};
    return point;
}

zone_t display_zone_init() {
    zone_t z;
    z.content = NULL;
    z.long_point_handler = NULL;
    z.point_handler = NULL;
    z.has_border = true;
    z.p1 = display_point_init(0,0);
    z.p2 = display_point_init(0,0);
    return z;
}

void display_create_zone_matrix( zone_matrix_t* zm, zone_t* zone_array, uint row, uint col, point_t start, point_t end ) {
    zm->start = start;
    zm->end = end;
    zm->row = row;
    zm->col = col;
    zm->z_width = (end.x - start.x)/col;
    zm->z_height = (end.y - start.y)/row;
    for( int i=0; i<row; i++ ) {
        for( int j=0; j<col; j++ ) {
            zone_array[i*col+j] = display_zone_init();
            zone_array[i*col+j].p1.x = start.x + j * zm->z_width;
            zone_array[i*col+j].p1.y = start.y + i * zm->z_height;
            zone_array[i*col+j].p2.x = start.x + zm->z_width + j * zm->z_width;
            zone_array[i*col+j].p2.y = start.y + zm->z_height + i * zm->z_height;
            zone_array[i*col+j].has_border = true;
        }
    }
    zm->z = zone_array;
}

void display_draw_zone( zone_t z, uint16_t color ) {
    if(z.has_border) lcd_rect( z.p1.x, z.p2.x, z.p1.y, z.p2.y, color );
}

zone_matrix_t* display_find_zone_matrix_from_coordinates(display_if_t* mode_if, uint16_t x, uint16_t y) {
    for(int i=0; i < mode_if->matrix_number; i++){
        if( x>= mode_if->matrix_if[i]->start.x && x < mode_if->matrix_if[i]->end.x && y >= mode_if->matrix_if[i]->start.y && y < mode_if->matrix_if[i]->end.y)
            return mode_if->matrix_if[i];
    }
}

zone_t* display_find_zone_from_coordinates( zone_matrix_t *zm, uint16_t x, uint16_t y ){
    for(int i = 0; i < zm->col*zm->row; i ++){
        if( x >= zm->z[i].p1.x && x < zm->z[i].p2.x && y >= zm->z[i].p1.y && y < zm->z[i].p2.y )
            return &zm->z[i];
    }
}

// void display_zone_matrix_content_init( zone_matrix_t* zm, void* contents ){
//     for(int i = 0; i < zm->row*zm->col; i++){
//         zm->z[i].content = contents[i];
//     }
// }
