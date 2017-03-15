//
//  OthelloView.cpp
//  Project 3
//
//  Created by Hao Lu on 4/30/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "OthelloView.h"
using namespace std;

void OthelloView::PrintBoard(ostream &s) const {
   cout << "- 0 1 2 3 4 5 6 7" << endl;
   for (int i = 0; i < BOARD_SIZE; i++) {
      cout << i;
      for (int j = 0; j < BOARD_SIZE; j++){
         if (mOthelloBoard->mBoard[i][j] == 0)
            cout << " .";
         if (mOthelloBoard->mBoard[i][j] == 1)
            cout << " B";
         if (mOthelloBoard->mBoard[i][j] == -1)
            cout << " W";
      }
      cout << "\n";
   }
}

/*
ostream& operator<<(ostream &lhs, const OthelloView &rhs) {
   rhs.PrintBoard(lhs);
   return lhs;
   
}
*/