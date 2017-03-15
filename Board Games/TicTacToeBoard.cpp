//
//  TicTacToeBoard.cpp
//  Project 3
//
//  Created by Hao Lu on 5/2/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "TicTacToeBoard.h"
// #include "GameBoard.h"
using namespace std;

TicTacToeBoard::TicTacToeBoard()
: GameBoard()
{
   for (int i = 0; i < BOARD_SIZE_3; i++) {
      for (int j = 0; j < BOARD_SIZE_3; j++) {
         mBoard[i][j] = 0;
      }
   }
}

void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   for (int r = 0; r < BOARD_SIZE_3; r++) {
      for (int c = 0; c < BOARD_SIZE_3; c++) {
         if (mBoard[r][c] == 0) {
            GameMove * move = CreateMove();
            *move = *move = "(" + to_string(r) + ","+to_string(c)+ ")";
            list->push_back(move);
         }
      }
   }
}

void TicTacToeBoard::ApplyMove(GameMove *move) {
   GameMove* hist = CreateMove();
   *hist = "(" + to_string(dynamic_cast<TicTacToeMove*>(move)->mRow) + ","
   + to_string(dynamic_cast<TicTacToeMove*>(move)->mCol) + ")";
   
   if (dynamic_cast<TicTacToeMove *>(move)->mRow == -1 &&
       dynamic_cast<TicTacToeMove *>(move)->mCol == -1) {
      mPassCount++;
   }
   
   // If not, apply the move to the board
   else {
      mPassCount = 0;
      mBoard[dynamic_cast<TicTacToeMove *>(move)->mRow]
      [dynamic_cast<TicTacToeMove *>(move)->mCol] = mNextPlayer;
      
   }
   mHistory.push_back(hist);
   mNextPlayer = -mNextPlayer;
   CheckForWinner();
}

void TicTacToeBoard::UndoLastMove() {
   mBoard[dynamic_cast<TicTacToeMove *>(mHistory.back())->mRow]
   [dynamic_cast<TicTacToeMove *>(mHistory.back())->mCol] = 0;
   
   GameMove *del = mHistory.back();
   delete del;
   mHistory.pop_back();
   mNextPlayer = -mNextPlayer;
}

void TicTacToeBoard::CheckForWinner() {
   int results[8] = {};
   for (int i = 0; i < BOARD_SIZE_3; i++) {
      // rows
      results[i] = mBoard[i][0] + mBoard[i][1] + mBoard[i][2];
      // cout << "HERE" << results[i+1];
      
      // columns
      results[i + 3] = mBoard[0][i] + mBoard[1][i] + mBoard[2][i];
   }
   // diagonal
   results[6] = mBoard[0][0] + mBoard[1][1] + mBoard[2][2];
   
   // other diagonal
   results[7] = mBoard[2][0] + mBoard[1][1] + mBoard[0][2];
   
   /*
   for (int i = 0; i < 8; i++) {
      cout << i << ":" << results[i] << endl;
   }
    */
   
   // char noWin = 0;
   for (int i = 0; i < 9; i++) {
      if (results[i] == 3) {
         cout << "X wins" << endl;;
         // noWin = 1;
         mPassCount = 2;
         break;
      }
      else if (results[i] == -3) {
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
   }
   
   /*
   char winner = 0;
   for (int i = 0; i < 3; i++) {
      // cout << i << endl;
      // row win
      if (mBoard[i][0] == mBoard[i][1] && mBoard[i][0] ==  mBoard[i][2]) {
         winner = mBoard[i][0];
         cout << "Row win!" << endl;
         break;
      }
      // column win
      if (mBoard[0][i] == mBoard[1][i] && mBoard[0][i] == mBoard[2][i] == 1) {
         winner = mBoard[0][i];
         cout << "Column win!" << endl;
         break;
      }
      // diagonal win
      if (mBoard[0][0] == mBoard[1][1] && mBoard[0][0] == mBoard[2][2]) {
         winner = mBoard[1][1];
         cout << "here 3:" << endl;
         break;
      }
      // other diagonal win
      if (mBoard[2][0] == mBoard[1][1] && mBoard[2][0] == mBoard[0][2]) {
         winner = mBoard[1][1];
         break;
      }
   }
   if (winner == 1 && winner == -1) {
      mPassCount = 2;
   }
    */
    /*
   if (winner == 1)
      cout << "X wins!" << endl;
   else if (winner == -1)
      cout << "Y wins!" << endl;
   else
      cout << "Tie!" << endl;
    */
}