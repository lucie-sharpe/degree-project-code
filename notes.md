# Explanation of AXI board controler

## AXI Registers:

- reg0: Write new states this to set the state of the board (read returns last value set)

- reg1: Read current state of board from this register (write dose nothing)
  
  - *Should this be merged with reg0?*

- reg2: Write control signals to this reg (read returns last value set)
  
  - generate new state: 0x00000001

## AXI IP interface

### port:

- IN (wire): board_state (AXI - read reg 1)

- OUT (wire):: new_board_state (AXI - write reg 0)

- OUT (reg): new_state_set (one clk pulse when write made to AXI reg 0)

- OUT (wire): command (AXI - write reg 2)

- OUT (reg): command_sent (one clk pulse when write made to AXI reg 2)

```verilog
// The state input from board submodule
input wire [C_S_AXI_DATA_WIDTH-1 : 0] board_state,
// Holds value of last new state sent from AXI
output wire [C_S_AXI_DATA_WIDTH-1 : 0] new_board_state,
// Pulses when a new state is sent from axi
output reg new_state_set,
// Holds value of last command sent over AXI
output wire [C_S_AXI_DATA_WIDTH-1 : 0] command,
// Pulses when a command is sent
output reg command_sent,
```

### Custom code:

#### new_board_state, command

Simply assign the value of reg0/reg2 to the output

```verilog
    assign new_board_state = slv_reg0;
    assign command = slv_reg2;
```

#### new_state_set, command_sent

- On reset set to 0

- When reg0/reg2 is writen to assert this flag

- On next clock de-assert this flag

Modifications are made to the register select and write block. New lines are commented

```verilog
    always @( posedge S_AXI_ACLK )
    begin
      if ( S_AXI_ARESETN == 1'b0 )
        begin
          slv_reg0 <= 0;
          slv_reg1 <= 0;
          slv_reg2 <= 0;
          slv_reg3 <= 0;

          // Reset flag
          new_state_set <= 0;
          command_sent <= 0;
        end 
      else begin
        // If flag is set reset it
        if (new_state_set)
          new_state_set <= 0;
        if (command_sent)
          command_sent <= 0;

        if (slv_reg_wren)
          begin
            case ( axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )
              2'h0: // Slave register 0
                begin
                  for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                    if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                      slv_reg0[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                  new_state_set <= 1; // Assert on write to reg0
                end

              2'h2: // Slave register 2
                begin
                  for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                    if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                      slv_reg2[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end  

                  command_sent <= 1; // Assert on write to reg2
```

##### Testing this

```verilog
always @( posedge S_AXI_ACLK )
	begin
	  if ( S_AXI_ARESETN == 1'b0 )
	    cnt <= 0;
	  else if (command_flag || set_state_flag)
	    cnt <= cnt + 1;
	end
```



#### board_state

Modified register select and read block to return input

```verilog
    assign slv_reg_rden = axi_arready & S_AXI_ARVALID & ~axi_rvalid;
    always @(*)
    begin
          // Address decoding for reading registers
          case ( axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )
            2'h0   : reg_data_out <= slv_reg0;
            2'h1   : reg_data_out <= board_state; // Return board state
            2'h2   : reg_data_out <= slv_reg2;
            2'h3   : reg_data_out <= slv_reg3;
            default : reg_data_out <= 0;
          endcase
    end
```

## Board

I am not sure how to handle clock domain crossing from the AXI clk to board clock so i am running the board with the AXI clk
