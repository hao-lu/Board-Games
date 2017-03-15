//
//  ConnectFourBoard.h
//  Project 3
//
//  Created by Hao Lu on 5/3/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#ifndef __Project_3__ConnectFourBoard__
#define __Project_3__ConnectFourBoard__

#include <stdio.h>
#include "GameBoard.h"
#include "ConnectFourMove.h"

const int BOARD_SIZE_6 = 6;
const int BOARD_SIZE_7 = 7;

class ConnectFourBoard : public GameBoard {
public:
   ConnectFourBoard();
   
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;
   
   virtual void ApplyMove(GameMove *move);
   
   virtual void UndoLastMove();
   
   virtual GameMove *CreateMove() const { return new ConnectFourMove; }
   
   virtual bool IsFinished() const {
      return mPassCount == 2;
   }
   
   virtual std::string GetPlayerString(char player) {
      return (player == 1 ? "Yellow" : "Red");
   }

private:
   friend class ConnectFourView;
   char mBoard[BOARD_SIZE_6][BOARD_SIZE_7];
   int mPassCount;
   
   void CheckForWinner();
   
};

#endif /* defined(__Project_3__ConnectFourBoard__) */
