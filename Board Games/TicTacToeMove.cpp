//
//  TicTacToeMove.cpp
//  Project 3
//
//  Created by Hao Lu on 5/2/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include <sstream>
using namespace std;

int TicTacToeMove::mOnHeap = 0;

TicTacToeMove::TicTacToeMove()
:mRow(-1), mCol(-1)
{
   
}

TicTacToeMove::TicTacToeMove(int row, int col)
:mRow(row), mCol(col)
{
   
}

GameMove& TicTacToeMove::operator=(const string &s) {
   istringstream ss(s);
   int row, col;
   char bad;
   ss >> bad >> row >> bad >> col >> bad;
   // If input good
   if ((row >= 0 && row < BOARD_SIZE_3 && col >= 0 && col < BOARD_SIZE_3) ||
       (row == -1 && col == -1)) {
      this->mRow = row;
      this->mCol = col;
      return *this;
   }
   // Throw exception if move is out of bounds or not pass
   else {
      throw TicTacToeException("Out of range");
   }
   
}
bool TicTacToeMove::Equals(const GameMove &other) const{
   return this->mRow == dynamic_cast<const TicTacToeMove&>(other).mRow &&
   this->mCol == dynamic_cast<const TicTacToeMove&>(other).mCol;

   
}
TicTacToeMove::operator std::string() const {
   if (mRow == -1 && mCol == -1) {
      return "pass";
   }
   string s = "(" + to_string(mRow) + "," + to_string(mCol) + ")";
   return s;
}