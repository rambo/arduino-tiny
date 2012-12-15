/**
 * This is a dummy bootloader for burning fuses
 *
 * NOTE: The empty_all.hex (which is handcrafted) should work fine, there definitely is no need for separate HEX file
 * for each fuse combination.
 *
 * Compile for the target mcu with
 *
 *  avr-gcc -g -Wall -O2 -mmcu=<target> -nostartfiles empty.c -o empty.elf
 *  avr-objcopy  -O ihex empty.elf empty.hex
 *  rm empty.elf empty.asm
 *  mv empty.hex empty<target>.hex
 *
 * To disassemble (if you want to see what the compiler did)
 *
 *  avr-objdump -Dx empty.elf > empty.asm
 *
 */
int main(void)
{
    while(1) {}
	return 0;
}
