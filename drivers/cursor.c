#include "ports.h"
#include "screen.h"

void disable_cursor()
{
	byte_out(0x3D4, 0x0A);
	byte_out(0x3D5, 0x20);
}


void enable_cursor(){
	byte_out(0x3D4, 0x0A);
	byte_out(0x3D5, (byte_in(0x3D5) & 0xC0) | 10);
 
	byte_out(0x3D4, 0x0B);
	byte_out(0x3D5, (byte_in(0x3D5) & 0xE0) | 12);

}



void set_cursor_offset(int offset){
    unsigned char* vidmem = (unsigned char*) VIDEO_ADDRESS;
    vidmem[offset*2+1] = WHITE_ON_BLACK;
    byte_out(REG_SCREEN_CTRL, 14);
    byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    byte_out(REG_SCREEN_CTRL, 15);
    byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_cursor_offset() {
    byte_out(REG_SCREEN_CTRL, 14);
    int offset = byte_in(REG_SCREEN_DATA) << 8;
    byte_out(REG_SCREEN_CTRL, 15);        
    offset += byte_in(REG_SCREEN_DATA);
    return offset;
}

int set_cursor_nextline(){
    int cursor = get_cursor_offset();
    cursor+= 80-(cursor%80);
    set_cursor_offset( cursor);
    return get_cursor_offset();
}

