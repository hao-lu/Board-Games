//
//  ConnectFourView.cpp
//  Project 3
//
//  Created by Hao Lu on 5/3/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "ConnectFourView.h"
using namespace std;

void ConnectFourView::PrintBoard(ostream &s) const {
   cout << "- 0 1 2 3 4 5 6" << endl;
   for (int i = 0; i < BOARD_SIZE_6; i++) {
      cout << i;
      for (int j = 0; j < BOARD_SIZE_7; j++){
         if (mConnectFourBoard->mBoard[i][j] == 0)
            cout << " .";
         if (mConnectFourBoard->mBoard[i][j] == 1)
            cout << " Y";
         if (mConnectFourBoard->mBoard[i][j] == -1)
            cout << " R";
      }
      cout << "\n";
   }
}