
#include "keycodes.h"
#include "keyboard.h"

//private functions
void update_special_key_state_t();

unsigned char buffer[KEYBOARD_BUFFER];
unsigned char key_buffer_read;
unsigned char key_buffer_write;
struct special_key_state_t special_key_state;
unsigned char capslock_pressed_once; // to change caps lock state

void key_handler_init(){
	// clear the buffer
	for(int i=0; i<KEYBOARD_BUFFER; i++){
		buffer[i]=0;
	}
	key_buffer_write = 0;
	key_buffer_read  = 0;
	special_key_state.capslock_on   = 0;
	special_key_state.shift_pressed = 0;
	special_key_state.ctrl_pressed  = 0;
	capslock_pressed_once = 0;
}

void key_handler_loop(){
	update_special_key_state_t();
}

///////////////////////////////////////
void update_special_key_state_t(){
	unsigned char key = get_key();
	unsigned char* vidmem = (unsigned char*)0xb8000;
	
	switch (key){
	case KEY_PRESSED_CAPSLOCK:
	    if (!capslock_pressed_once){
	    	capslock_pressed_once = 1;
	    	special_key_state.capslock_on = !special_key_state.capslock_on;
	    }
	    break;
	case KEY_RELEASED_CAPSLOCK:
	    capslock_pressed_once = 0;
	    break;

	case KEY_PRESSED_RSHIFT:
	    special_key_state.shift_pressed   = 1;
	    break;
	case KEY_PRESSED_LSHIFT:
	    special_key_state.shift_pressed   = 1;
	    break;
	case KEY_RELEASED_RSHIFT:
	    special_key_state.shift_pressed   = 0;
	    break;
	case KEY_RELEASED_LSHIFT:
	    special_key_state.shift_pressed   = 0;
	    break;
	case KEY_PRESSED_CTRL:
	    special_key_state.ctrl_pressed    = 1;
	    break;
	case KEY_RELEASED_CTRL:
	    special_key_state.ctrl_pressed    = 0;
	    break;
	}
	
}
