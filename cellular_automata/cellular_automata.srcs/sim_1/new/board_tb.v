`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.02.2024 19:01:33
// Design Name: 
// Module Name: board_tb
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


module board_tb();
    localparam BOARD_WIDTH = 3;
    localparam BOARD_HEIGHT = 3;
    localparam BOARD_SIZE = BOARD_WIDTH * BOARD_HEIGHT;

    reg clk, rst, set_state, generate_state;
    reg [(BOARD_SIZE-1):0] new_state;
    wire [(BOARD_SIZE-1):0] state;

    board #(BOARD_WIDTH, BOARD_HEIGHT) board_module (clk, rst, set_state, generate_state, new_state, state);
    
    initial begin
        clk <= 0;                  // Set clk low
        rst <= 0;
        generate_state <= 0;
        set_state <= 0;            // Set set_state low
        new_state <= 9'b000111000; // Set inital state // This should create a line that rotates h/v on clk pulse
        
        // Initalise board with new_state
        #1 set_state <= 1;
        clk <= 1;
        #2 set_state <= 0;
        clk <= 0;
        $display(state, " = 56 = 000111000");
        // 0 0 0
        // 1 1 1
        // 0 0 0
        
        // Clock the board
        #3 generate_state <= 1;
        clk <= 1;
        #4 generate_state <= 0;
        clk <= 0;
        $display(state, " = 146 = 010010010");
        // 0 1 0
        // 0 1 0
        // 0 1 0
        
        // Clock the board
        #5 generate_state <= 1;
        clk <= 1;
        #6 generate_state <= 0;
        clk <= 0;
        $display(state, " = 56 = 000111000");
        // 0 0 0
        // 1 1 1
        // 0 0 0
        
        // Initalise board with a different state
        new_state <= 9'b000010000;
        #7 set_state <= 1;
        clk <= 1;
        #8 set_state <= 0;
        clk <= 0;
        $display(state, " = 16 = 000010000");
        // 0 0 0
        // 0 1 0
        // 0 0 0
        
        // Clock the board
        #9 generate_state <= 1;
        clk <= 1;
        #10 generate_state <= 0;
        clk <= 0;
        $display(state, " = 0 = 000000000");
        // 0 0 0
        // 0 0 0
        // 0 0 0
    end

endmodule
