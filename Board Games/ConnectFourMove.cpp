//
//  ConnectFourMove.cpp
//  Project 3
//
//  Created by Hao Lu on 5/3/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "ConnectFourMove.h"
#include "ConnectFourBoard.h"
#include <sstream>
using namespace std;

int ConnectFourMove::mOnHeap = 0;

ConnectFourMove::ConnectFourMove()
:mRow(-1), mCol(-1)
{
   
}

ConnectFourMove::ConnectFourMove(int row, int col)
:mRow(row), mCol(col)
{
   
}

GameMove& ConnectFourMove::operator=(const string &s) {
   istringstream ss(s);
   int row, col;
   char bad;
   ss >> bad >> row >> bad >> col >> bad;
   // If input good
   if ((row >= 0 && row < BOARD_SIZE_6 && col >= 0 && col < BOARD_SIZE_7) ||
       (row == -1 && col == -1)) {
      this->mRow = row;
      this->mCol = col;
      return *this;
   }
   // Throw exception if move is out of bounds or not pass
   else {
      throw ConnectFourException("Out of range");
   }
   
}
bool ConnectFourMove::Equals(const GameMove &other) const{
   return this->mRow == dynamic_cast<const ConnectFourMove&>(other).mRow &&
   this->mCol == dynamic_cast<const ConnectFourMove&>(other).mCol;
   
   
}
ConnectFourMove::operator std::string() const {
   if (mRow == -1 && mCol == -1) {
      return "pass";
   }
   string s = "(" + to_string(mRow) + "," + to_string(mCol) + ")";
   return s;
}