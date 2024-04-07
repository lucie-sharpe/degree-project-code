#include <stdint.h>

#include "common.h"
#include "kprintf.h"

#define	AXI_BASEADDRESS 0x60040000
#define DELAY 2000000

#define REG_WIDTH 32
#define BOARD_WIDTH_NUM_REG 4

#define CONTROL_RST_BOARD 0
#define CONTROL_GEN_STATE 1

typedef struct reg {
    volatile uint32_t set_state_1; /* set a new board state */
    volatile uint32_t set_state_2;
    volatile uint32_t set_state_3;
    volatile uint32_t set_state_4;
    volatile uint32_t set_state_5;
    volatile uint32_t set_state_6;
    volatile uint32_t set_state_7;
    volatile uint32_t set_state_8;
    volatile uint32_t set_state_9;
    volatile uint32_t set_state_10;
    volatile uint32_t set_state_11;
    volatile uint32_t set_state_12;
    volatile uint32_t set_state_13;
    volatile uint32_t set_state_14;
    volatile uint32_t set_state_15;
    volatile uint32_t set_state_16;
    volatile uint32_t set_state_17;
    volatile uint32_t set_state_18;
    volatile uint32_t set_state_19;
    volatile uint32_t set_state_20;
    volatile uint32_t set_state_21;
    volatile uint32_t set_state_22;
    volatile uint32_t set_state_23;
    volatile uint32_t set_state_24;
    volatile uint32_t set_state_25;
    volatile uint32_t set_state_26;
    volatile uint32_t set_state_27;
    volatile uint32_t set_state_28;
    volatile uint32_t set_state_29;
    volatile uint32_t set_state_30;
    volatile uint32_t set_state_31;
    volatile uint32_t set_state_32;
    volatile uint32_t read_state_1; /* read state of board */
    volatile uint32_t read_state_2;
    volatile uint32_t read_state_3;
    volatile uint32_t read_state_4;
    volatile uint32_t read_state_5;
    volatile uint32_t read_state_6;
    volatile uint32_t read_state_7;
    volatile uint32_t read_state_8;
    volatile uint32_t read_state_9;
    volatile uint32_t read_state_10;
    volatile uint32_t read_state_11;
    volatile uint32_t read_state_12;
    volatile uint32_t read_state_13;
    volatile uint32_t read_state_14;
    volatile uint32_t read_state_15;
    volatile uint32_t read_state_16;
    volatile uint32_t read_state_17;
    volatile uint32_t read_state_18;
    volatile uint32_t read_state_19;
    volatile uint32_t read_state_20;
    volatile uint32_t read_state_21;
    volatile uint32_t read_state_22;
    volatile uint32_t read_state_23;
    volatile uint32_t read_state_24;
    volatile uint32_t read_state_25;
    volatile uint32_t read_state_26;
    volatile uint32_t read_state_27;
    volatile uint32_t read_state_28;
    volatile uint32_t read_state_29;
    volatile uint32_t read_state_30;
    volatile uint32_t read_state_31;
    volatile uint32_t read_state_32;
    volatile uint32_t control;       /* send control signals (1=generate new state) */
    volatile uint32_t wolfram_code;  /* Wolfram CA code to use (0-255) */
} REG;

void print_row_state(uint32_t state) {
  for (int col=REG_WIDTH-1; col >= 0; col--) { // For each col in row from MSB to LSB
    if ((state>>(col)) & 1) { // Right shift so Nth bit is LSB then bitwise and with 1
      //kprintf("[#] ");
      //kprintf("o");
      kprintf("█");
    } else {
      //kprintf("[ ] ");
      kprintf(" ");
    }
  }
}

void print_state(REG * reg) {
  kprintf("Board State:\n");
  uint32_t *rows = reg;
  rows = rows+32;
  
  for (int row_idx=0; row_idx < BOARD_WIDTH_NUM_REG; row_idx++) {
    print_row_state(*(rows+row_idx));
  }
  kprintf("\n"); // Endo of row
}

int main(void) {
  REG * reg = (REG *)AXI_BASEADDRESS;
  
  /*
  * Each set_state element represents a row on the board.
  * The element holds 32 bits. The MSB is the far right and the LSB is the far left.
  * set_state_1 represents the bottom row on the board and set_state_32 represents the top row.
  *
  * Control functions:
  * Wrirte a control value to reg->control to run it.
  * CONTROL_RST_BOARD = reset board to 0
  * CONTROL_GEN_STATE = generate a new board state
  */
  
  kprintf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  // CGOL test
//  reg->control = CONTROL_RST_BOARD;
//  reg->set_state_24 = 0x800;
//  reg->set_state_25 = 0x800;
//  reg->set_state_26 = 0x800;
//  print_state(reg);
//  reg->control = CONTROL_GEN_STATE;
//  print_state(reg);
//  reg->control = CONTROL_GEN_STATE;
//  print_state(reg);
//  reg->control = CONTROL_RST_BOARD;
//  print_state(reg);
//  reg->set_state_30 = 1;
//  print_state(reg);
//  reg->control = CONTROL_GEN_STATE;
//  print_state(reg);
  // Conways game of life quad flyers
//  reg->set_state_12 = 0x3C000;
//  reg->set_state_13 = 0x0;
//  reg->set_state_14 = 0xFF000;
//  reg->set_state_15 = 0x0;
//  reg->set_state_16 = 0x3FFC00;
//  reg->set_state_17 = 0x0;
//  reg->set_state_18 = 0xFF000;
//  reg->set_state_19 = 0x0;
//  reg->set_state_20 = 0x3C000;
  
  reg->control = CONTROL_RST_BOARD;
  reg->set_state_31 = 0x10000;
  //reg->set_state_15 = 0x3F508C7;
  reg->wolfram_code = 30;
  //reg->wolfram_code = 90;
  //reg->wolfram_code = 184;
  
  volatile int Delay;
  
  kprintf("Board State:\n");
  while (1) {
    print_state(reg);
    reg->control = CONTROL_GEN_STATE;
    for (Delay = 0; Delay < DELAY; Delay++);
  }
  
  return 1;
}
