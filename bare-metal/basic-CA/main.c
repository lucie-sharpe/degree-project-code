#include <stdint.h>

#include "common.h"
#include "kprintf.h"

#define	AXI_BASEADDRESS 0x60040000
#define DELAY 2000000

#define BOARD_WIDTH 32
#define BOARD_HEIGHT 32

#define CONTROL_RST_BOARD 0
#define CONTROL_GEN_STATE 1

#define NUM_ITER 150

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

    volatile uint32_t control;    /* send control signals (1=generate new state) */
    volatile uint32_t response;
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
  uint32_t *rows = reg;
  rows = rows+32;
  
  for (int row_idx=0; row_idx < BOARD_HEIGHT; row_idx++) {
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

  //  CGOL test
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

  //  Conways game of life quad flyers
  //  reg->set_state_12 = 0x3C000;
  //  reg->set_state_13 = 0x0;
  //  reg->set_state_14 = 0xFF000;
  //  reg->set_state_15 = 0x0;
  //  reg->set_state_16 = 0x3FFC00;
  //  reg->set_state_17 = 0x0;
  //  reg->set_state_18 = 0xFF000;
  //  reg->set_state_19 = 0x0;
  //  reg->set_state_20 = 0x3C000;

  //  Repeating patern
  //  0110000000001100000000000000 - 600C000
  //  0111101000001100000000000000 - 7A0C000
  //  0101001110000000000000000000 - 5380000
  //  0000000000001000000000000000 - 8000
  //  0000011000010100000000000000 - 614000
  //  0000010000010010000100000000 - 412100
  //  0000000000001100001100000000 - C300
  //  0000000000000000000000000000 - 0
  //  0000000000000000111001010000 - E50
  //  0000000000011000001011110000 - 182F0
  //  0000000000011000000000110000 - 18030
  
  reg->control = CONTROL_RST_BOARD;

  reg->set_state_21 = 0x600C000;
  reg->set_state_20 = 0x7A0C000;
  reg->set_state_19 = 0x5380000;
  reg->set_state_18 = 0x8000;
  reg->set_state_17 = 0x614000;
  reg->set_state_16 = 0x412100;
  reg->set_state_15 = 0xC300;
  reg->set_state_14 = 0x0;
  reg->set_state_13 = 0xE50;
  reg->set_state_12 = 0x182F0;
  reg->set_state_11 = 0x18030;

  //kprintf("Inital on Acc:\n");
  //print_state(reg);

  //  volatile int Delay;
  //  while(1) {
  //    for (Delay = 0; Delay < DELAY; Delay++);
  //    reg->control = 1;
  //    print_state(reg);
  //  }

  int done = 0;

  uintptr_t acc_time_start;
  uintptr_t acc_time_end;
  
  kprintf("Start on Accelerator:\n");
  print_state(reg);

  // Compute on accelerator
  asm volatile ("csrr %0, 0xB00" : "=r" (acc_time_start)); // Assembly code to read control and status register holding machine cycle counter (https://book.rvemu.app/hardware-components/03-csrs.html)
  reg->control = NUM_ITER;
  while(!done) {
    if (reg->response) {
      asm volatile ("csrr %0, 0xB00" : "=r" (acc_time_end));
      done = 1;
    }
  }
  kprintf("End on Accelerator:\n");
  print_state(reg);

  // ======== Software ======

  uintptr_t soft_time_start;
  uintptr_t soft_time_end;

  int board[32][32] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
  int board_counts[32][32];
  
  // Print software board state
  kprintf("Start on Software:\n");
  for (int y=0;y<BOARD_HEIGHT;y++) {
    for (int x=0;x<BOARD_WIDTH;x++) {
      if (board[y][x]) {
        //kprintf("[#] ");
        kprintf("o");
      } else {
        //kprintf("[ ] ");
        kprintf(" ");
      }
    }
    kprintf("\n");        
  }
  
  // Compute software CA
  asm volatile ("csrr %0, 0xB00" : "=r" (soft_time_start));
  for (int i=0;i<NUM_ITER;i++) {
    // Compute sum of neigbors
    for (int y=0;y<BOARD_HEIGHT;y++) {
      for (int x=0;x<BOARD_WIDTH;x++) {
        int nvalid = (y-1)>=0;
        int evalid = (x+1)<32;
        int svalid = (y+1)<32;
        int wvalid = (x-1)>=0;

        int n  = nvalid           ? board[y-1][x]   : 0;
        int e  = evalid           ? board[y][x+1]   : 0;
        int s  = svalid           ? board[y+1][x]   : 0;
        int w  = wvalid           ? board[y][x-1]   : 0;
        int ne = nvalid && evalid ? board[y-1][x+1] : 0;
        int nw = nvalid && wvalid ? board[y-1][x-1] : 0;
        int se = svalid && evalid ? board[y+1][x+1] : 0;
        int sw = svalid && wvalid ? board[y+1][x-1] : 0;

        board_counts[y][x] = n+e+s+w+ne+nw+se+sw;
      }
    }
    
    // Compute next state
    for (int y=0;y<BOARD_HEIGHT;y++) {
      for (int x=0;x<BOARD_WIDTH;x++) {
        if (board[y][x]) { // Alive
          if (board_counts[y][x] < 2 || board_counts[y][x] > 3) {
            board[y][x] = 0;
          }
        } else { // Dead
          if (board_counts[y][x] == 3) {
            board[y][x] = 1;
          }
        }
      }
    }
  }
  asm volatile ("csrr %0, 0xB00" : "=r" (soft_time_end));
  
  // Print software board state
  kprintf("End on Software:\n");
  for (int y=0;y<BOARD_HEIGHT;y++) {
    for (int x=0;x<BOARD_WIDTH;x++) {
      if (board[y][x]) {
        //kprintf("[#] ");
        kprintf("o");
      } else {
        //kprintf("[ ] ");
        kprintf(" ");
      }
    }
    kprintf("\n");        
  }
  
  // ========
  
  kprintf("Clock Cycles: %d\n", acc_time_end-acc_time_start);
  kprintf("Clock Cycles: %d\n", soft_time_end-soft_time_start);
    
  return 1;
}
