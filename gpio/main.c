#include <stdint.h>

#include "common.h"
#include "kprintf.h"
#include "gpio.h"

#define LED 0x01
#define	GPIO_AXI_BASEADDRESS 0x60040000
#define GPIO_CHANNEL 1
#define DELAY 100000

int main(void) {
	volatile int Delay;
	volatile uint32_t data;

	kprintf("\n");

	for (data = 0; data <= 0xFFFF; data++) {
		gpio_write(data, GPIO_CHANNEL, GPIO_AXI_BASEADDRESS);
		kprintf("Update\n");
		for (Delay = 0; Delay < DELAY; Delay++);
	}

}
