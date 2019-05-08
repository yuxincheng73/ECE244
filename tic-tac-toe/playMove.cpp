//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    //determining who the current player is
    int player;
    if(turn) {
        player = X;
    } 
    else {
        player = O;
    }
    
    if(board[row][col] == Empty) {
        board[row][col] = player;
        validMove = true;
    }
    else if(board[row][col] != Empty) {
        //do nothing but print the board again
        validMove = false;
    }
    
    //to determine if someone has won
    if(!gameOver) {
        int count;
 
        //checks if won horizontally
        for(int i = 0; i < 3; i++) {
            count = 0;
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == player) {
                    count++;
                    if(count == 3) {
                        if(i == 0) {
                            winCode = 1;
                        } else if(i == 1) {
                            winCode = 2;
                        } else if(i == 2) {
                            winCode = 3;
                        }
                        gameOver = true;
                    }
                }
            }
        }

        //checks if won vertically
        for(int i = 0; i < 3; i++) {
            count = 0;
            for(int j = 0; j < 3; j++) {
                if(board[j][i] == player) {
                    count++;
                    if(count == 3) {
                        if(i == 0) {
                            winCode = 4;
                        } else if(i == 1) {
                            winCode = 5;
                        } else if(i == 2) {
                            winCode = 6;
                        }
                        gameOver = true;
                    }
                }
            }
        }

        //checks if won diagonally from top left to bottom right
        for(int i = 0; i < 3; i++) {
            if(board[i][i] == player) {
                count++;
                if(count == 3) {
                    winCode = 7;
                    gameOver = true;
                }
            }
        }

        //checks if won diagonally from top right to bottom left
        count = 0;
        for(int i = 0, j = 2; i < 3; i++, j--) {
            if(board[i][j] == player) {
                count++;
                if(count == 3) {
                    winCode = 8;
                    gameOver = true;
                }
            }
        }
    }
    
    
    //change turn to other player
    turn = !turn;
        
    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
    }
    cout << row << " " << col << " " << turn << " " << validMove << " " << gameOver << " " << winCode << endl;
}

