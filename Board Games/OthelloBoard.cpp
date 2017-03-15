//
//  OthelloBoard.cpp
//  Project 3
//
//  Created by Hao Lu on 4/30/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "OthelloBoard.h"
// #include "GameBoard.h"

using namespace std;

const int VAL = 100, START_1 = 3, START_2 = 4;

// Default constructor
OthelloBoard::OthelloBoard()
: GameBoard()
{
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         mBoard[i][j] = 0;
      }
   }
   mBoard[START_1][START_1] = -1;
   mBoard[START_1][START_2] = 1;
   mBoard[START_2][START_1] = 1;
   mBoard[START_2][START_2] = -1;
}

void OthelloBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   for (int x = 0; x < BOARD_SIZE; ++x) {
      for (int y = 0; y < BOARD_SIZE; ++y) {
         // If current player piece found
         if (mBoard[x][y] == mNextPlayer) {
            int row = x, col = y;
            // Check in all 8 directions
            for (int r = -1; r < 2; r++) {
               for (int c = -1; c < 2; c++) {
                  // Set temp row and col
                  row = x;
                  col = y;
                  // Take 1 step in that direction
                  row += r;
                  col += c;
                  // If enemy found
                  if (mBoard[row][col] == -mNextPlayer) {
                     // Keep going in that direction and check for more whites
                     for (;mBoard[row][col] == -mNextPlayer; row+=r, col+=c) {
                     }
                     // If white then empty
                     if (mBoard[row][col] == 0 && InBounds(row, col)) {
                        // Save into vector
                        GameMove* move = CreateMove();
                        *move = "(" + to_string(row) + ","+to_string(col)+ ")";
                        // If list move is empty, add one
                        if (list->empty()) {
                           list->push_back(move);
                        }
                        // Else compare the list and add in the correct spot
                        // from least r to greater c
                        else {
                           // Add in sorted order
                           int moveTotal = row * VAL + col, add = 0;
                           for (int i = 0; i < list->size(); i++) {
                              int pt = dynamic_cast<OthelloMove *>(list->at(i))->mRow*VAL
                              + dynamic_cast<OthelloMove *>(list->at(i))->mCol;
                              // If less than or equal
                              if (moveTotal < pt || moveTotal == pt) {
                                 // If less than then add at that location in
                                 // the vector
                                 if (moveTotal < pt) {
                                    list->insert(list->begin() + i, move);
                                 }
                                 // If move is already in vector, delete move
                                 else if (moveTotal == pt) {
                                    delete move;
                                 }
                                 add = 1;
                                 break;
                              }
                           }
                           // Add if move isn't already in the vector or greater
                           if (add == 0) {
                              list->push_back(move);
                           }
                           
                        }
                     }
                  }
                  
               }
            }
            
         }
      }
   }
}


/*
 Applies a valid move to the board, updating the board state accordingly.
 You may assume that this move is valid, and is consistent with the list
 of possible moves returned by GetAllMoves. Make sure you account for changes
 to the current player, pass count, and board value.
 */
void OthelloBoard::ApplyMove(GameMove *move) {
   // Create history move
   GameMove* hist = CreateMove();
   *hist = "(" + to_string(dynamic_cast<OthelloMove*>(move)->mRow) + ","
   + to_string(dynamic_cast<OthelloMove*>(move)->mCol) + ")";
   if (hist == nullptr) {
      throw OthelloException("Tried to apply a non-OthelloMove.");
   }
   
   // If (-1,-1), increase passCount
   if (dynamic_cast<OthelloMove *>(move)->mRow == -1 &&
       dynamic_cast<OthelloMove *>(move)->mCol == -1) {
      mPassCount++;
   }
   
   // If not, apply the move to the board
   else {
      mPassCount = 0;
      
      // Applies the move selection on the board
      mBoard[dynamic_cast<OthelloMove *>(move)->mRow]
      [dynamic_cast<OthelloMove *>(move)->mCol] = mNextPlayer;
      // Applies move and add one to board (mValue)
      mValue += mNextPlayer;
      
      
      // Counts the number of enemies encountered. RowMove is the current row
      // position and colMove is the current column move.
      int enemy = 0, row = dynamic_cast<OthelloMove *>(move)->mRow,
      col = dynamic_cast<OthelloMove *>(move)->mCol, switches = 0;
      for (int r = -1; r < 2; r++) {
         for (int c = -1; c < 2; c++) {
            //Reset
            if (enemy == 0) {
               row = dynamic_cast<OthelloMove *>(move)->mRow;
               col = dynamic_cast<OthelloMove *>(move)->mCol;
            }
            // Take 1 step in that direction
            row += r;
            col += c;
            
            // Out of bounds or space is empty
            if (!(InBounds(row, col)) || (mBoard[row][col] == 0)) {
               enemy = 0;
            }
            // Enemy piece is found
            else if (mBoard[row][col] == -(mNextPlayer)) {
               enemy++;
               // Move back c to continue to move down the row to check for more
               // enemy pieces
               c--;
            }
            // Friendly piece and found and at least one enemy piece is counted
            else if (mBoard[row][col] == mNextPlayer && enemy > 0) {
               // Create flip set
               OthelloMove::FlipSet flip(switches, r, c);
               
               for (int tempRow = row += -r, tempCol = col += -c; enemy > 0;
                    enemy--, tempRow += -r, tempCol += -c, flip.switched++) {
                  // Flip
                  mBoard[tempRow][tempCol] = mNextPlayer;
                  // switches++;
                  // flip.switched++;
                  mValue += 2 * mNextPlayer;
               }
               // Add move to FlipSet
               dynamic_cast<OthelloMove *>(hist)->AddFlipSet(flip);
               
            }
         }
      }
   }
   mHistory.push_back(hist);
   mNextPlayer = -mNextPlayer;
   
}

/*
 Undoes the last move applied to the board, restoring it to the state it was
 in prior to the most recent move (including whose turn it is, what the
 board value is, and what the pass count is).
 */
void OthelloBoard::UndoLastMove() {
   // While the flipset has something inside
   while (!(dynamic_cast<OthelloMove *>(mHistory.back())->mFlips.empty())) {
      // Reset variables
      int row = dynamic_cast<OthelloMove *>(mHistory.back())->mRow,
      col = dynamic_cast<OthelloMove *>(mHistory.back())->mCol;
      int r = dynamic_cast<OthelloMove *>(mHistory.back())->mFlips.back().rowDelta,
      c = dynamic_cast<OthelloMove *>(mHistory.back())->mFlips.back().colDelta,
      sw = dynamic_cast<OthelloMove *>(mHistory.back())->mFlips.back().switched;
      // Does the flipping
      for (int i = 0; i < sw; i++) {
         // Flip
         mBoard[row += r][col += c] = mNextPlayer;
         // Board value
         mValue += 2 * mNextPlayer;
      }
      // Pop the last flipset on vector
      dynamic_cast<OthelloMove *>(mHistory.back())->mFlips.pop_back();
   }
   // Empty the last move on the board
   mBoard[dynamic_cast<OthelloMove *>(mHistory.back())->mRow]
   [dynamic_cast<OthelloMove *>(mHistory.back())->mCol] = 0;
   // Change value of the board
   mValue += mNextPlayer;
   // Delete the OthelloMove of history off the heap
   GameMove *del = mHistory.back();
   delete del;
   // Shrink the history vector
   mHistory.pop_back();
   // Switch players
   mNextPlayer = -mNextPlayer;
   
}

