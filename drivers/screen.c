#include "screen.h"
#include "ports.h"
#include "cursor.h"
#include "./keyboard/keycodes.h"
#include "./keyboard/keyboard.h"

/* Declaration of private functions */
void print_screen_error(char* error_msg);
void print_char_hex(unsigned char hex, int offset, char attr);


void test(){ 
    int offset=0;
    //printAttr("[", COLOR_WHITE);
    //printAttr("*", COLOR_LIGHT_GREEN);
    //printAttr("] everything is ok", COLOR_WHITE);
    //set_cursor_nextline();
    //offset = set_cursor_nextline();

    while(1){
    offset += printAtOffset("thakee@sony-pc", offset, 0xa);
    offset += printAtOffset(":", offset, WHITE_ON_BLACK);
    offset += printAtOffset("/Desktop", offset, COLOR_WHITE_BLUE);
    offset += printAtOffset("$ ", offset, COLOR_WHITE);

    char input[256]; for (int i=0; i<256; i++) input[i]=0;
    char* inp = keyboard_get_input(offset, input);
    offset = set_cursor_nextline();
    if (*inp!=0){
        printAtOffset(inp, offset, 0xe);
        offset = set_cursor_nextline();
    }

    }
  
}


/* puclic API */
void clearScreen()
{
    unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
    for(int i=0; i<25*80*2; i++){
        vidmem[i] = 0;
    }
    set_cursor_offset(0);       // set the cursor at the top left
    vidmem[1] = WHITE_ON_BLACK; // set color of the cursor

}

int print_char_offset(unsigned char c, int offset, unsigned char attr){
    unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
    vidmem[offset*2] = c;
    vidmem[offset*2+1] = attr;
    return 1;
}

int printAtOffset(char* text, int offset, char attr){
    int len=0;
    unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
    if (offset>=0 && offset<80*25){
        offset *=2;
        while(*text){
            vidmem[offset++] = *text++;
            vidmem[offset++] = attr;
            len++;
        }
    } else {
        print_screen_error("ERROR: invalid print offset!");
    } return len;
}

int printAtCord(char* text, int col, int row, char attr){
    unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
    int offset = (MAX_COLS*row+col);
    return printAtOffset(text, offset, attr);

}

int print(char* string){
    int len = printAtOffset(string, get_cursor_offset(), WHITE_ON_BLACK);
    set_cursor_offset( get_cursor_offset()+len );
    return len;
}

int printAttr(char* string, char attr){
    int len =  printAtOffset(string, get_cursor_offset(), attr);
    set_cursor_offset( get_cursor_offset()+len );
    return len;   
}

/* private functions */
void print_screen_error(char* error_msg){
    unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
    int addr_ptr = (80*24);
    printAtOffset(error_msg, addr_ptr, RED_ON_BLACK);
}

void print_char_hex(unsigned char hex, int offset, char attr){ 
  offset--;
  unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
  char c1 = (hex&0xf), c2 = (hex&0xf0)>>4;
  if (c1<10) { vidmem[offset*2+4] = c1+48; vidmem[offset*2+5] = attr; }
  else { vidmem[offset*2+4] = c1+55; vidmem[offset*2+5] = attr;  }
  
  if (c2<10) { vidmem[offset*2+2] = c2+48; vidmem[offset*2+3] = attr; }
  else { vidmem[offset*2+2] = c2+55; vidmem[offset*2+3] = attr; }

  vidmem[offset*2] = 'x'; vidmem[offset*2+1] = attr;
  
}




