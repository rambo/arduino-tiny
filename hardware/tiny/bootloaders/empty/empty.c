/**
 * This is a dummy bootloader for burning fuses
 *
 * Compile for the target mcu with
 *
 *  avr-gcc -g -Wall -O2 -mmcu=<target> -nostartfiles -Wa,-adhlns=./empty.lst empty.c -o empty.elf
 *  avr-objcopy  -O ihex empty.elf empty.hex
 *  rm empty.elf empty.lst empty.asm
 *  mv empty.hex empty<target>.hex
 *
 * To disassemble
 *
 *  avr-objdump -Dx empty.elf > empty.asm
 *
 */
int main(void)
{
    while(1) {}
	return 0;
}
