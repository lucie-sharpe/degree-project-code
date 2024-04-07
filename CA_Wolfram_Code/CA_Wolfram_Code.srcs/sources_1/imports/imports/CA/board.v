`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.02.2024 14:02:14
// Design Name: 
// Module Name: board
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

// at 50x50, it toke 6:48 to compile and showed usage of LUT: 3, FF: 1 (I dont trust this)
// at 5x5 with outputs used, it showed usage LUT: 130, FF: 50 (I think some stuff was not synthisised as the outputs were not used) (AVG per cell: LUT: 5.2, FF: 2)
// at 7x7, it showed usage LUT: 274, FF: 98 (AVG per cell: LUT: 5.59, FF: 2)
// at 9x9, it showed usage LUT: 484, FF: 162 (AVG per cell: LUT: 5.98, FF: 2)
// at 10x10, it showed usage LUT: 614, FF: 200 (AVG per cell: LUT: 6.14, FF: 2)
// at 1x1, it showed usage LUT: 3, FF: 1

// Using a predicted graph from the LUT datapoints 32x32 would take 8414 LUTs (13.27%)

module board
    #(
    parameter BOARD_WIDTH = 0
    )(
    input clk, rst,
    input [7:0] wolfram_code,
    input set_state, generate_state,
    input [(BOARD_WIDTH-1):0] new_board_state,
    output [(BOARD_WIDTH-1):0] board_state
    );
    
    // Board Register
    
    localparam DEFAULT_EDGE_VALUE = 1'b0; // Value to be used if neighbour is off edge of board
    
    wire [BOARD_WIDTH:0] cell_state_register;
    assign cell_state_register[BOARD_WIDTH] = DEFAULT_EDGE_VALUE; // Final bit if register holds default edge value
    
    assign board_state = cell_state_register[(BOARD_WIDTH-1):0]; // Output current state
    
    // Board Cells
    
    genvar x;
    genvar y;
    generate
        for (x=0; x<BOARD_WIDTH; x=x+1) begin
            board_cell #(x,BOARD_WIDTH) cell_module (clk, rst, wolfram_code, set_state, generate_state, new_board_state[x], cell_state_register, cell_state_register[x]);
        end
    endgenerate
    
    
endmodule
