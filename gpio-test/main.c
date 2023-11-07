#include <stdint.h>

#include "common.h"
#include "kprintf.h"

/************************** Constant Definitions *****************************/

#define XGPIO_DATA_OFFSET	0x0   /**< Data register for 1st channel */
#define XGPIO_TRI_OFFSET	0x4   /**< I/O direction reg for 1st channel */
#define XGPIO_DATA2_OFFSET	0x8   /**< Data register for 2nd channel */
#define XGPIO_TRI2_OFFSET	0xC   /**< I/O direction reg for 2nd channel */

#define XGPIO_GIE_OFFSET	0x11C /**< Glogal interrupt enable register */
#define XGPIO_ISR_OFFSET	0x120 /**< Interrupt status register */
#define XGPIO_IER_OFFSET	0x128 /**< Interrupt enable register */

#define XGPIO_CHAN_OFFSET  8	/**< Channel offeset */

#define LED 0x01   /* Assumes bit 0 of GPIO is connected to an LED  */
#define	XGPIO_AXI_BASEADDRESS 0x60040000
#define GPIO_CHANNEL 1
#define DELAY 10000000

/****************************************************************************/

static void set_32(uint64_t Addr, uint32_t Value)
{
	volatile uint32_t *LocalAddr = (volatile uint32_t *)Addr;
	*LocalAddr = Value;
}

#define Gpio_WriteReg(BaseAddress, RegOffset, Data) \
	set_32((BaseAddress) + (RegOffset), (uint32_t)(Data))



/****************************************************************************/

int main(void)
{
	volatile int Delay;

	kprintf("\n");

	uint64_t DataOffset = ((GPIO_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET;

	/* Loop forever blinking the LED */

	while (1) {
		/* Set the LED to High */
		Gpio_WriteReg(XGPIO_AXI_BASEADDRESS, DataOffset, LED);
		kprintf("High\n");

		/* Wait a small amount of time so the LED is visible */
		for (Delay = 0; Delay < DELAY; Delay++);

		/* Clear the LED bit */
		Gpio_WriteReg(XGPIO_AXI_BASEADDRESS, DataOffset, 0x00);
		kprintf("Low\n");

		/* Wait a small amount of time so the LED is visible */
		for (Delay = 0; Delay < DELAY; Delay++);
	}

}
