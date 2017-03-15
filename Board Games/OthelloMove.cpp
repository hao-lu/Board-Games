//
//  OthelloMove.cpp
//  Project 3
//
//  Created by Hao Lu on 4/30/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "OthelloMove.h"
#include "OthelloBoard.h"
#include <sstream>
using namespace std;

int OthelloMove::mOnHeap = 0;

// Default constructor (pass)
OthelloMove::OthelloMove()
:mRow(-1), mCol(-1)
{
   
}

// Initialized constructor (move)
OthelloMove::OthelloMove(int row, int col)
: mRow(row), mCol(col)
{
   
}

/*
 This assignment operator takes a string representation of an Othellomove
 and uses it to initialize the move. The string is in the format
 (r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
 anymore.]
 */
GameMove& OthelloMove::operator=(const string &s) {
   istringstream ss(s);
   int row, col;
   char bad;
   ss >> bad >> row >> bad >> col >> bad;
   // If input good
   if ((row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) ||
       (row == -1 && col == -1)) {
      this->mRow = row;
      this->mCol = col;
      return *this;
   }
   // Throw exception if move is out of bounds or not pass
   else {
      throw OthelloException("Out of range");
   }
}

/*
 Compares two OthelloMove objects for equality (if rows and cols are same).

bool operator==(const OthelloMove &lhs, const OthelloMove &rhs) {
   // return lhs.mRow == rhs.mRow && lhs.mCol == rhs.mCol;
   return lhs.Equals(rhs);
}
*/

bool OthelloMove::Equals(const GameMove &other) const {
   return this->mRow == dynamic_cast<const OthelloMove&>(other).mRow &&
   this->mCol == dynamic_cast<const OthelloMove&>(other).mCol;
}

/*
 Converts the OthelloMove into a string representation, one that could be
 used correctly with operator=(string). Returns "pass" if move is a pass.
 */
OthelloMove::operator string() const {
   if (mRow == -1 && mCol == -1) {
      return "pass";
   }
   string s = "(" + to_string(mRow) + "," + to_string(mCol) + ")";
   return s;
}

