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

	kprintf("reg3 = %d\n", reg->reg3);
    reg->reg0 = 10;
    kprintf("reg3 = %d\n", reg->reg3);
    reg->reg2 = 4;
    kprintf("reg3 = %d\n", reg->reg3);
    reg->reg1 = 7;
    kprintf("reg3 = %d\n", reg->reg3);
    
    kprintf("reg0 = %d, reg1 = %d, reg2 = %d, reg3 = %d\n", reg->reg0, reg->reg1, reg->reg2, reg->reg3);
}
