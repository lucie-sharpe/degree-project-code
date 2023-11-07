#include <stdint.h>

#ifndef _GPIO_H
#define _GPIO_H

extern void gpio_write(uint32_t data, int channel, uint64_t base_address);

#endif /* _GPIO_H */