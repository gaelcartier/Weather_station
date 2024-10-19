#include "buffer_loop.h"

void buffer_loop_init(buffer_loop_t *b, void* buffer, uint8_t element_size, uint16_t buffer_size){
    b->read_index = 0;
    b->write_index = 0;
    b->buffer = (void*)buffer;
    b->element_size = element_size;
    b->buffer_size = buffer_size;
}

bool buffer_loop_is_empty(buffer_loop_t b) {
	return b.write_index == b.read_index;
}

void buffer_loop_write_index_up(buffer_loop_t* b){
    b->write_index = (b->write_index == (b->buffer_size*b->element_size-b->element_size) ) ? 0 : b->write_index + b->element_size;
}

void buffer_loop_read_index_up(buffer_loop_t* b){
    b->read_index = (b->read_index == (b->buffer_size*b->element_size-b->element_size) ) ? 0 : b->read_index + b->element_size;
}

bool buffer_loop_is_full(buffer_loop_t b){
    uint16_t nexte_write_index = (b.write_index == (b.buffer_size * b.element_size - b.element_size) ) ? 0 : b.write_index + b.element_size;
	return nexte_write_index == b.read_index;
}

void buffer_loop_push(buffer_loop_t* b, void* v) {
	if( b != NULL ) {
		memcpy( &(b->buffer[b->write_index]), v, b->element_size);
        buffer_loop_write_index_up(b);
	}
}

void buffer_loop_pop(buffer_loop_t* b, void* dest) {
	if( b!=NULL && !buffer_loop_is_empty(*b) ) {
		dest = memcpy((void*)dest, &(b->buffer[b->read_index]), b->element_size);
        buffer_loop_read_index_up(b);
    }
}

int buffer_loop_element_count( buffer_loop_t b ) {
	if( b.write_index < b.read_index )
		return ( b.write_index + (b.buffer_size - b.read_index) );
	else
		return b.write_index - b.read_index;
}

void buffer_loop_clear(buffer_loop_t* b) {
    b->read_index = 0;
    b->write_index = 0;
}