
#include "../drivers/screen.h"
#include "../drivers/cursor.h"
#include "../drivers/keyboard/keyboard.h"

void shell(){ 
    char* username = "thakee@sony-pc"; // get it as args
    char* path = "/Desktop";
    int offset = 0;
    while(1){
        offset += printAtOffset(username, offset, 0xa);
        offset += printAtOffset(":", offset, WHITE_ON_BLACK);
        offset += printAtOffset(path, offset, COLOR_WHITE_BLUE);
        offset += printAtOffset("$ ", offset, COLOR_WHITE);

        char input[256]; for (int i=0; i<256; i++) input[i]=0;
        char* inp = keyboard_get_input(offset, input);
        offset = set_cursor_nextline();
        if (*inp!=0){
            int temp_cursor_offset = get_cursor_offset();
            /*TODO:ececute the command*/ temp_cursor_offset+=printAtOffset(inp, offset, 0xe);
            set_cursor_offset(temp_cursor_offset);
            offset = set_cursor_nextline();
        }

    }
}