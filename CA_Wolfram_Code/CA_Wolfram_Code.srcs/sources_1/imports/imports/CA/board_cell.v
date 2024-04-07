`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 29.01.2024 19:53:47
// Design Name: 
// Module Name: board_cell
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


module board_cell
    #(
    parameter X = 0,
    parameter BOARD_WIDTH = 0
    )(
    input clk, rst,
    input [7:0] wolfram_code,
    input set_state, generate_state,
    input new_state,
    input [BOARD_WIDTH:0] board_state,
    output reg state
    );
    
    // -------------------
    // Get neigbour values
    // -------------------
    
    // Check if neighbours are valid at compile time
    localparam E_VALID = (X + 1) < BOARD_WIDTH;
    localparam W_VALID = (X - 1) >= 0;
    
    // Generate neigbours and cell indexs at compile time
    // BOARD_SIZE index holds the value used when cell is of the edge of board
    localparam C_IDX  = X;
    localparam E_IDX = E_VALID ? C_IDX + 1 : BOARD_WIDTH;
    localparam W_IDX = W_VALID ? C_IDX - 1 : BOARD_WIDTH;
    
    // Get state of neighbours
    assign c = board_state[C_IDX];
    assign e = board_state[E_IDX];
    assign w = board_state[W_IDX];
    
    // --------------
    // Set next state
    // --------------
    
    always @ (posedge clk) begin
        // reset cell
        if (rst)
            state <= 0;
        
        // Set a new inital state
        else if (set_state) 
            state <= new_state;
            
        // Set new state based on neighbours
        else if (generate_state) begin
            if (w && c && e)
                state <= wolfram_code[7];
            if (w && c && !e)
                state <= wolfram_code[6];
            if (w && !c && e)
                state <= wolfram_code[5];
            if (w && !c && !e)
                state <= wolfram_code[4];
            if (!w && c && e)
                state <= wolfram_code[3];
            if (!w && c && !e)
                state <= wolfram_code[2];
            if (!w && !c && e)
                state <= wolfram_code[1];
            if (!w && !c && !e)
                state <= wolfram_code[0];
        end
    end
    
endmodule
