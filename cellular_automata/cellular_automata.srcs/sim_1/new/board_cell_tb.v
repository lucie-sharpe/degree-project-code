`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 29.01.2024 21:09:50
// Design Name: 
// Module Name: board_cell_tb
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


module board_cell_tb;
    localparam BOARD_WIDTH = 3;
    localparam BOARD_HEIGHT = 3;
    localparam BOARD_SIZE = BOARD_WIDTH * BOARD_HEIGHT;
    
    // Default value to set neigbour to if it extends out of the board
    localparam DEFAULT_EDGE_VALUE = 1'b0;

    reg clk, set_state;
    reg new_state;
    reg [0:BOARD_SIZE] board_state;
    wire state [0:1];
    wire [0:1] generated_board;
    
    // concatinate the cell states
    genvar i;
    generate
        for (i=0; i<2; i=i+1) begin
            assign generated_board[i] = state[i];
        end
    endgenerate
    
    board_cell #(1,1,BOARD_WIDTH,BOARD_HEIGHT) cell_1 (clk, set_state, new_state, board_state, state[0]);
    board_cell #(2,1,BOARD_WIDTH,BOARD_HEIGHT) cell_2 (clk, set_state, new_state, board_state, state[1]);
    
    initial begin
        clk <= 0;
        set_state <= 0;
        new_state <= 0;
        // Validate make alive PASS
        board_state <= {9'b100100100, DEFAULT_EDGE_VALUE};
        #1 clk <= 1;
        #1 clk <= 0;
        // Validate kill PASS
        board_state <= {9'b110100100, DEFAULT_EDGE_VALUE};
        #1 clk <= 1;
        #1 clk <= 0;
        // Validate edge (should make cell_2 alive) PASS
        board_state <= {9'b000000000, 1'b1};
        #1 clk <= 1;
        #1 clk <= 0;
    end

endmodule
