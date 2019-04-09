#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_BUFFER 256
#define KEY_MEMORY 0x60

unsigned char  get_key();
unsigned char get_key_char(unsigned char key);
char* keyboard_get_input(int cursor_offset_start, char* input_store);

void key_handler_init();
void key_handler_loop();

struct special_key_state_t{
    unsigned char shift_pressed;
    unsigned char ctrl_pressed;
    unsigned char capslock_on;
};

extern struct special_key_state_t special_key_state;

#endif
