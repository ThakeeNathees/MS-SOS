#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_BLACK 0x0c

// color definitions
#define COLOR_DARK_BLUE   0x01
#define COLOR_DARK_GREEN  0x02
#define COLOR_LIGHT_BLUE  0x03
#define COLOR_DARK_RED    0x04
#define COLOR_PURPLE      0x05
#define COLOR_ORANGE      0x06
#define COLOR_LIGHT_GRAY  0x07
#define COLOR_DARK_GRAY   0x08 
#define COLOR_BLUE        0x09
#define COLOR_LIGHT_GREEN 0x0a
#define COLOR_WHITE_BLUE  0x0b
#define COLOR_LIGHT_RED   0x0c 
#define COLOR_PINK        0x0d
#define COLOR_YELLO       0x0e 
#define COLOR_WHITE       0x0f

/* public scereen API */
void clearScreen();
int printAtOffset(char* text, int offset, char attr);
int printAtCord(char* text, int col, int row, char attr);
int print(char* string);
int printAttr(char* string, char attr);
int print_char_offset(unsigned char c, int offset, unsigned char attr);

void test();

#endif
