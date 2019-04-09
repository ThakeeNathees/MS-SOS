#include "../drivers/screen.h"
#include "../drivers/keyboard/keyboard.h"

void kernel_main()
{
    // inits
    clearScreen();
    key_handler_init();

    // main loop
    //while (1){key_handler_loop();}
    
    test();
}
