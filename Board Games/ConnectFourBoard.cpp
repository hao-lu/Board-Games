//
//  ConnectFourBoard.cpp
//  Project 3
//
//  Created by Hao Lu on 5/3/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "ConnectFourBoard.h"
using namespace std;

ConnectFourBoard::ConnectFourBoard()
: GameBoard()
{
   for (int i = 0; i < BOARD_SIZE_6; i++) {
      for (int j = 0; j < BOARD_SIZE_7; j++) {
         mBoard[i][j] = 0;
      }
   }
}

void ConnectFourBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   for (int c = 0; c < BOARD_SIZE_7; c++) {
      for (int r = BOARD_SIZE_6 - 1; r >= 0; r--) {
         if (mBoard[r][c] == 0) {
            GameMove * move = CreateMove();
            *move = *move = "(" + to_string(r) + ","+to_string(c)+ ")";
            list->push_back(move);
            break;
         }
      }
   }

}

void ConnectFourBoard::ApplyMove(GameMove *move) {
   GameMove* hist = CreateMove();
   *hist = "(" + to_string(dynamic_cast<ConnectFourMove*>(move)->mRow) + ","
   + to_string(dynamic_cast<ConnectFourMove*>(move)->mCol) + ")";
   
   if (dynamic_cast<ConnectFourMove *>(move)->mRow == -1 &&
       dynamic_cast<ConnectFourMove *>(move)->mCol == -1) {
      mPassCount++;
   }
   
   // If not, apply the move to the board
   else {
      mPassCount = 0;
      mBoard[dynamic_cast<ConnectFourMove *>(move)->mRow]
      [dynamic_cast<ConnectFourMove *>(move)->mCol] = mNextPlayer;
      
   }
   mHistory.push_back(hist);
   mNextPlayer = -mNextPlayer;
   CheckForWinner();

}

void ConnectFourBoard::UndoLastMove() {
   mBoard[dynamic_cast<ConnectFourMove *>(mHistory.back())->mRow]
   [dynamic_cast<ConnectFourMove *>(mHistory.back())->mCol] = 0;
   
   GameMove *del = mHistory.back();
   delete del;
   mHistory.pop_back();
   mNextPlayer = -mNextPlayer;
}

void ConnectFourBoard::CheckForWinner() {
   int result[30] = {0};
   int rowTotal = 0, colTotal = 0, increment = 0;
   for (int r = 0; r < BOARD_SIZE_7; r++) {
      for (int c = 0; c < BOARD_SIZE_7; c++) {
         if (r < BOARD_SIZE_6) {
            rowTotal += mBoard[r][c];
            cout << "ROWincrement: " << increment << " r: " << r << " c: " << c << endl;
         }
         if (c < BOARD_SIZE_6) {
            colTotal += mBoard[c][r];
            cout << "COLincrement: " << increment << " r: " << c << " c: " << r << endl;
         }
      }
      cout << "INCREMENT: " << increment << endl;
      result[increment++] = rowTotal;
      cout << "INCREMENT: " << increment << endl;
      // Too hacky
      if (increment < 13)
         result[increment++] = colTotal;
   }
   
   
   for (int i = 0; i < 30; i++) {
      cout << i << ":" << result[i] << endl;
   }
   /*
   // char noWin = 0;
   for (int i = 0; i < 9; i++) {
      if (result[i] == 3) {
         cout << "X wins" << endl;;
         // noWin = 1;
         mPassCount = 2;
         break;
      }
      else if (result[i] == -3) {
         cout << "O wins" << endl;
         // noWin = 1;
         mPassCount = 2;
         break;
      }
      else if (mHistory.size() == 9) {
         cout << "Tie game" << endl;
         mPassCount = 2;
         break;
      }
   }*/

   
}