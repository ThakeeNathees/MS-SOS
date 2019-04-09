
if [ "$1" = "start" ]; then
  echo "[auto-builder] building boot.o"
  nasm -f elf32 -o ./boot/boot.o ./boot/boot.asm

  echo "[auto-builder] building kernel"
  gcc -m32 -o ./kernel/kernel.o -c ./kernel/kernel.c -nostdlib -nostartfiles -nodefaultlibs
  gcc -m32 -o ./drivers/screen.o -c ./drivers/screen.c -nostdlib -nostartfiles -nodefaultlibs
  gcc -m32 -o ./drivers/ports.o -c ./drivers/ports.c -nostdlib -nostartfiles -nodefaultlibs
  gcc -m32 -o ./drivers/cursor.o -c ./drivers/cursor.c -nostdlib -nostartfiles -nodefaultlibs
  gcc -m32 -o ./drivers/keyboard/keyboard.o -c ./drivers/keyboard/keyboard.c -nostdlib -nostartfiles -nodefaultlibs
  gcc -m32 -o ./drivers/keyboard/keyhandler.o -c ./drivers/keyboard/keyhandler.c -nostdlib -nostartfiles -nodefaultlibs

  echo "[auto-builder] linking with linker.ld"
  ld -T ./boot/linker.ld -m elf_i386 -o os.bin ./boot/boot.o ./drivers/cursor.o ./drivers/keyboard/keyhandler.o ./drivers/keyboard/keyboard.o ./drivers/screen.o ./drivers/ports.o ./kernel/kernel.o
  
  echo "[auto-bulider] cleaning"
  rm ./boot/boot.o
  rm ./kernel/kernel.o
  rm ./drivers/screen.o
  rm ./drivers/ports.o
  rm ./drivers/cursor.o
  rm ./drivers/keyboard/keyboard.o
  rm ./drivers/keyboard/keyhandler.o

  echo "[auto-builde] starting qemu"
  qemu-system-i386 -kernel os.bin


fi
