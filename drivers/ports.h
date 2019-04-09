#ifndef PORTS_H
#define PORTS_H
/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

unsigned char  byte_in(unsigned short port);
void           byte_out (unsigned short port, unsigned char data);
unsigned short word_in (unsigned short port);
void           word_out (unsigned short port, unsigned short data);

#endif
