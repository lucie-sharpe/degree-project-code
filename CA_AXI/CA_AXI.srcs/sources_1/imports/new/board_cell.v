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
    parameter Y = 0,
    parameter BOARD_WIDTH = 0,
    parameter BOARD_HEIGHT = 0
    )(
    input clk, rst,
    input set_state, generate_state,
    input new_state,
    input [(BOARD_WIDTH*BOARD_HEIGHT):0] board_state,
    output reg state
    );
    
    // Number of elements in board
    localparam BOARD_SIZE = BOARD_WIDTH*BOARD_HEIGHT;
    
    // -------------------
    // Get neigbour values
    // -------------------
    
    // Check if neighbours are valid at compile time
    localparam N_VALID = (Y - 1) >= 0;
    localparam E_VALID = (X + 1) < BOARD_WIDTH;
    localparam S_VALID = (Y + 1) < BOARD_HEIGHT;
    localparam W_VALID = (X - 1) >= 0;
    
    // Generate neigbours and cell indexs at compile time
    // BOARD_SIZE index holds the value used when cell is of the edge of board
    localparam C_IDX  = (Y * BOARD_WIDTH) + X;
    localparam N_IDX  = N_VALID            ? C_IDX - BOARD_WIDTH : BOARD_SIZE;
    localparam E_IDX  = E_VALID            ? C_IDX + 1           : BOARD_SIZE;
    localparam S_IDX  = S_VALID            ? C_IDX + BOARD_WIDTH : BOARD_SIZE;
    localparam W_IDX  = W_VALID            ? C_IDX - 1           : BOARD_SIZE;
    localparam NE_IDX = N_VALID && E_VALID ? N_IDX + 1           : BOARD_SIZE;
    localparam NW_IDX = N_VALID && W_VALID ? N_IDX - 1           : BOARD_SIZE;
    localparam SE_IDX = S_VALID && E_VALID ? S_IDX + 1           : BOARD_SIZE;
    localparam SW_IDX = S_VALID && W_VALID ? S_IDX - 1           : BOARD_SIZE;
    
    // Get state of neighbours
    assign n = board_state[N_IDX];
    assign e = board_state[E_IDX];
    assign s = board_state[S_IDX];
    assign w = board_state[W_IDX];
    assign ne = board_state[NE_IDX];
    assign nw = board_state[NW_IDX];
    assign se = board_state[SE_IDX];
    assign sw = board_state[SW_IDX];
    
    // Get number of alive neighbours and current state of cell
    wire [3:0] alive_neighbours;
    assign alive_neighbours = n + e + s + w + ne + nw + se + sw;
    assign current_state = board_state[C_IDX];
    
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
            // If alive, make dead when less than 2 or greater than 3 neighbours
            if (current_state) begin
                if (alive_neighbours < 2 || alive_neighbours > 3) 
                    state <= 1'b0;
            end
            
            // If dead, make alive if 3 neighbours
            else if (alive_neighbours == 3)
                state <= 1'b1;
            else
                state <= current_state;
        end
    end
    
endmodule
