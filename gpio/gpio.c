#include <stdint.h>

#define XGPIO_DATA_OFFSET	0x0   /* < Data register for 1st channel        */
#define XGPIO_TRI_OFFSET	0x4   /* < I/O direction reg for 1st channel    */
#define XGPIO_DATA2_OFFSET	0x8   /* < Data register for 2nd channel        */
#define XGPIO_TRI2_OFFSET	0xC   /* < I/O direction reg for 2nd channel    */

#define XGPIO_GIE_OFFSET	0x11C /* < Glogal interrupt enable register */
#define XGPIO_ISR_OFFSET	0x120 /* < Interrupt status register        */
#define XGPIO_IER_OFFSET	0x128 /* < Interrupt enable register        */

#define XGPIO_CHAN_OFFSET  8    /* < Channel offeset */

typedef struct gpio {
    volatile uint32_t gpio_data;    /* < Data register for 1st channel      */
    volatile uint32_t gpio_tri;     /* < I/O direction reg for 1st channel  */
    volatile uint32_t gpio_data2;   /* < Data register for 2nd channel      */
    volatile uint32_t gpio_tri2;    /* < I/O direction reg for 2nd channel  */
} GPIO;

void gpio_write(uint32_t data, int channel, uint64_t base_address) {
    GPIO * gpio_reg = (GPIO *)base_address;

    if (channel == 1) {
        gpio_reg->gpio_data = data;
    } else if (channel == 2) {
        gpio_reg->gpio_data2 = data;
    }
}