`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.02.2024 19:51:03
// Design Name: 
// Module Name: board_large_tb
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

// Testbech for a larger 10x10 board
// The initial state should reach a stable state after 8 iterations then remail the same

module board_large_tb();
    localparam BOARD_WIDTH = 10;
    localparam BOARD_HEIGHT = 10;
    localparam BOARD_SIZE = BOARD_WIDTH * BOARD_HEIGHT;

    reg clk, set_state;
    reg [0:(BOARD_SIZE-1)] new_state;
    wire [0:(BOARD_SIZE-1)] state;

    board #(BOARD_WIDTH, BOARD_HEIGHT) board_module (clk, set_state, new_state, state);
    
    initial begin
        clk <= 0;                  // Set clk low
        set_state <= 0;            // Set set_state low
        new_state <= 100'b0000000000000000000000100000000000110000000100100000010010000000110000000000010000000000000000000000; // Set inital state // This should create a line that rotates h/v on clk pulse
        
        // Initalise board with new_state
        #1 set_state <= 1;
        #2 set_state <= 0;
        $display(state, " = 151171148828059449163776");
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 1 0 0 0 0 0 0 0
        // 0 0 0 0 1 1 0 0 0 0
        // 0 0 0 1 0 0 1 0 0 0
        // 0 0 0 1 0 0 1 0 0 0
        // 0 0 0 0 1 1 0 0 0 0
        // 0 0 0 0 0 0 0 1 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        
        // Clock the board (1)
        #3 clk <= 1;
        #4 clk <= 0;
        $display(state, " = 129208352534226272256");
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 1 1 1 0 0 0 0
        // 0 0 0 1 0 0 1 0 0 0
        // 0 0 0 1 0 0 1 0 0 0
        // 0 0 0 0 1 1 1 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        
        // Clock the board (2)
        #5 clk <= 1;
        #6 clk <= 0;
        $display(state, " = 37908284335077527126016");
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 1 0 0 0 0 0
        // 0 0 0 1 1 1 0 0 0 0
        // 0 0 1 1 0 0 1 0 0 0
        // 0 0 0 1 0 0 1 1 0 0
        // 0 0 0 0 1 1 1 0 0 0
        // 0 0 0 0 0 1 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0
        
        // Clock the board (3)
        #7 clk <= 1;
        #8 clk <= 0;
        $display(state, " = 38818018955959252167966720");
        
        // Clock the board (4)
        #9 clk <= 1;
        #10 clk <= 0;
        $display(state, " = 132392440058543402385408");
        
        // Clock the board (5)
        #11 clk <= 1;
        #12 clk <= 0;
        $display(state, " = 135494600599585499134353408");
        
        // Clock the board (6)
        #13 clk <= 1;
        #14 clk <= 0;
        $display(state, " = 39710899718102521888909598736");
        
        // Clock the board (7)
        #15 clk <= 1;
        #16 clk <= 0;
        $display(state, " = 39720542732728678264646770704");
        
        // Clock the board (8) // Stable state
        #17 clk <= 1;
        #18 clk <= 0;
        $display(state, " = 59517949731509673738704560176");
        
        // Clock the board (9)
        #19 clk <= 1;
        #20 clk <= 0;
        $display(state, " = 59517949731509673738704560176");
    end

endmodule
