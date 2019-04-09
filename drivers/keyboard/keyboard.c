#include "keycodes.h"
#include "keyboard.h"
#include "../ports.h"
#include "../cursor.h"
#include "../screen.h"


unsigned char shift_pressed = 0; // LSHIFT || RSHIFT
unsigned char capslock_on   = 0;
unsigned char ctrl_pressed  = 0;

char* keyboard_get_input(int cursor_offset_start, char* input){
    set_cursor_offset(cursor_offset_start);
    int offset = cursor_offset_start;
    unsigned char previous_key = get_key();
    int input_arr_ptr = 0;
	while(1){
		key_handler_loop();
		unsigned char key = get_key();
	    if( previous_key != key ) {
	    	previous_key = key;
	        unsigned char kchar = get_key_char(key);
	        if(key== KEY_PRESSED_ENTER){ return input; }
	        else if (key== KEY_PRESSED_BACKSPACE){
	        	if (offset == cursor_offset_start) continue;
	        	print_char_offset(0, --offset, 0);
	        	input[--input_arr_ptr]=0;
	        }
	        else if(kchar!=0){
	        	input[input_arr_ptr++] = kchar;
	        	print_char_offset(kchar, offset++, WHITE_ON_BLACK);
	        }
	        set_cursor_offset(offset);
	    }
	}
}



unsigned char  get_key(){
    while (1) { // ignoring 0xE0
        unsigned char val = byte_in(KEY_MEMORY); 
        if(val!=0xE0) return val;
    }
}

unsigned char get_key_char(unsigned char key){
    unsigned char caps = special_key_state.capslock_on ;
    unsigned char shift = special_key_state.shift_pressed;
    unsigned char upper = caps || shift;
    switch (key){
	case KEY_PRESSED_A: return upper?'A':'a';
	case KEY_PRESSED_B: return upper?'B':'b';
	case KEY_PRESSED_C: return upper?'C':'c';
	case KEY_PRESSED_D: return upper?'D':'d';
	case KEY_PRESSED_E: return upper?'E':'e';
	case KEY_PRESSED_F: return upper?'F':'f';
	case KEY_PRESSED_G: return upper?'G':'g';
	case KEY_PRESSED_H: return upper?'H':'h';
	case KEY_PRESSED_I: return upper?'I':'i';
	case KEY_PRESSED_J: return upper?'J':'j';
	case KEY_PRESSED_K: return upper?'K':'k';
	case KEY_PRESSED_L: return upper?'L':'l';
	case KEY_PRESSED_M: return upper?'M':'m';
	case KEY_PRESSED_N: return upper?'N':'n';
	case KEY_PRESSED_O: return upper?'O':'o';
	case KEY_PRESSED_P: return upper?'P':'p';
	case KEY_PRESSED_Q: return upper?'Q':'q';
	case KEY_PRESSED_R: return upper?'R':'r';
	case KEY_PRESSED_S: return upper?'S':'s';
	case KEY_PRESSED_T: return upper?'T':'t';
	case KEY_PRESSED_U: return upper?'U':'u';
	case KEY_PRESSED_V: return upper?'V':'v';
	case KEY_PRESSED_W: return upper?'W':'w';
	case KEY_PRESSED_X: return upper?'X':'x';
	case KEY_PRESSED_Y: return upper?'Y':'y';
	case KEY_PRESSED_Z: return upper?'Z':'z';
	case KEY_PRESSED_MINUS: return shift?'_':'-';
	case KEY_PRESSED_EQUAL: return shift?'+':'=';
	case KEY_PRESSED_OSBRACKET: return shift?'{':'[';
	case KEY_PRESSED_CSBRACKET: return shift?'}':']';
	case KEY_PRESSED_SEMICOLON: return shift?':':';';
	case KEY_PRESSED_SQUOTE: return shift?'\'':'\"';
	case KEY_PRESSED_COMA: return shift?'<':',';
	case KEY_PRESSED_DOT: return shift?'>':'.';
	case KEY_PRESSED_FRONTSLASH: return shift?'/':'?';
	case KEY_PRESSED_SPACE: return ' ';
	//case KEY_PRESSED_ENTER: return '\n';
	default : return 0;


    }
}
