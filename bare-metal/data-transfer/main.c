#include <stdint.h>

#include "common.h"
#include "kprintf.h"

#define	AXI_BASEADDRESS 0x60040000
#define DELAY 1000000

typedef struct reg {
    volatile uint32_t reg0;    /* < Data register for 1st channel      */
    volatile uint32_t reg1;     /* < I/O direction reg for 1st channel  */
    volatile uint32_t reg2;   /* < Data register for 2nd channel      */
    volatile uint32_t reg3;    /* < I/O direction reg for 2nd channel  */
} REG;

int main(void) {
	volatile int Delay;
	volatile uint32_t data;
	REG * reg = (REG *)AXI_BASEADDRESS;

	kprintf("reg2 = %d\n", reg->reg2);

	for (data = 0; data <= 0xFFFF; data++) {
		reg->reg0 = data;
		kprintf("Input: %d - ShiftReg0: %d - ShiftReg1+300: %d\n", reg->reg1, reg->reg3);

		for (Delay = 0; Delay < DELAY; Delay++);
	}

}
