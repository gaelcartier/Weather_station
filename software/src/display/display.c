#include "display.h"

void display_create_zone_matrix( zone_matrix_t* zm, zone_t* zone_array, uint row, uint col, point_t start, point_t end ){
    zm->start = start;
    zm->end = end;
    zm->row = row;
    zm->col = col;
    zm->z_width = (end.x - start.x)/col;
    zm->z_height = (end.y - start.y)/row;
    for( int i=0; i<row; i++ ) {
        for( int j=0; j<col; j++ ) {
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

// void display_zone_matrix_content_init( zone_matrix_t* zm, void* contents ){
//     for(int i = 0; i < zm->row*zm->col; i++){
//         zm->z[i].content = contents[i];
//     }
// }
