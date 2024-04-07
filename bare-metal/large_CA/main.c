#include <stdint.h>

#include "common.h"
#include "kprintf.h"

#define	AXI_BASEADDRESS 0x60040000
#define DELAY 2000000

#define BOARD_WIDTH 32
#define BOARD_HEIGHT 30

#define CONTROL_RST_BOARD 0
#define CONTROL_GEN_STATE 1

typedef struct reg {
    volatile uint32_t set_state_1;  /* set a new board state */
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
    volatile uint32_t set_state_33;
    volatile uint32_t set_state_34;
    volatile uint32_t set_state_35;
    volatile uint32_t set_state_36;
    volatile uint32_t set_state_37;
    volatile uint32_t set_state_38;
    volatile uint32_t set_state_39;
    volatile uint32_t set_state_40;
    volatile uint32_t set_state_41;
    volatile uint32_t set_state_42;
    volatile uint32_t set_state_43;
    volatile uint32_t set_state_44;
    volatile uint32_t set_state_45;
    volatile uint32_t set_state_46;
    volatile uint32_t set_state_47;
    volatile uint32_t set_state_48;
    volatile uint32_t set_state_49;
    volatile uint32_t set_state_50;
    volatile uint32_t set_state_51;
    volatile uint32_t set_state_52;
    volatile uint32_t set_state_53;
    volatile uint32_t set_state_54;
    volatile uint32_t set_state_55;
    volatile uint32_t set_state_56;
    volatile uint32_t set_state_57;
    volatile uint32_t set_state_58;
    volatile uint32_t set_state_59;
    volatile uint32_t set_state_60;
    
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
    volatile uint32_t read_state_33;
    volatile uint32_t read_state_34;
    volatile uint32_t read_state_35;
    volatile uint32_t read_state_36;
    volatile uint32_t read_state_37;
    volatile uint32_t read_state_38;
    volatile uint32_t read_state_39;
    volatile uint32_t read_state_40;
    volatile uint32_t read_state_41;
    volatile uint32_t read_state_42;
    volatile uint32_t read_state_43;
    volatile uint32_t read_state_44;
    volatile uint32_t read_state_45;
    volatile uint32_t read_state_46;
    volatile uint32_t read_state_47;
    volatile uint32_t read_state_48;
    volatile uint32_t read_state_49;
    volatile uint32_t read_state_50;
    volatile uint32_t read_state_51;
    volatile uint32_t read_state_52;
    volatile uint32_t read_state_53;
    volatile uint32_t read_state_54;
    volatile uint32_t read_state_55;
    volatile uint32_t read_state_56;
    volatile uint32_t read_state_57;
    volatile uint32_t read_state_58;
    volatile uint32_t read_state_59;
    volatile uint32_t read_state_60;
    
    volatile uint32_t control;    /* send control signals (1=generate new state) */
} REG;

void print_row_state(uint32_t state) {
  for (int col=BOARD_WIDTH-1; col >= 0; col--) { // For each col in row from MSB to LSB
    if ((state>>(col)) & 1) { // Right shift so Nth bit is LSB then bitwise and with 1
      //kprintf("[#] ");
      kprintf("o");
    } else {
      //kprintf("[ ] ");
      kprintf(" ");
    }
  }
}

void print_state(REG * reg) {
  kprintf("Board State:\n");
  uint32_t *rows = reg;
  rows = rows+60;
  
  for (int row_idx=0; row_idx < BOARD_HEIGHT; row_idx++) {
    print_row_state(*(rows+row_idx++));
    print_row_state(*(rows+row_idx));
    kprintf("\n"); // Endo of row
  }
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
  reg->set_state_29 = 0x3;  //     11 11
  reg->set_state_30 = 0xC0000000
  reg->set_state_33 = 0xF;  //   1111 1111
  reg->set_state_34 = 0xF0000000;
  reg->set_state_37 = 0x3F; // 111111 111111
  reg->set_state_38 = 0xFC000000;
  reg->set_state_41 = 0xF;  //   1111 11111
  reg->set_state_42 = 0xF0000000;
  reg->set_state_45 = 0x3;  //     11 11
  reg->set_state_46 = 0xC0000000;

  
  volatile int Delay;
  
  while(1) {
    reg->control = CONTROL_GEN_STATE;
    print_state(reg);
    for (Delay = 0; Delay < DELAY; Delay++);
  }
  
  return 1;
}
