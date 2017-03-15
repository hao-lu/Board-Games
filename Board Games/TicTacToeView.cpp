//
//  TicTacToeView.cpp
//  Project 3
//
//  Created by Hao Lu on 5/2/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "TicTacToeView.h"
#include <ostream>
using namespace std;

void TicTacToeView::PrintBoard(ostream &s) const {
   cout << "- 0 1 2" << endl;
   for (int i = 0; i < BOARD_SIZE_3; i++) {
      cout << i;
      for (int j = 0; j < BOARD_SIZE_3; j++){
         if (mTicTacToeBoard->mBoard[i][j] == 0)
            cout << " .";
         if (mTicTacToeBoard->mBoard[i][j] == 1)
            cout << " X";
         if (mTicTacToeBoard->mBoard[i][j] == -1)
            cout << " O";
      }
      cout << "\n";
   }

}