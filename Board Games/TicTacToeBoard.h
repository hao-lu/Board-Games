//
//  TicTacToeBoard.h
//  Project 3
//
//  Created by Hao Lu on 5/2/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#ifndef __Project_3__TicTacToeBoard__
#define __Project_3__TicTacToeBoard__

// #include <stdio.h>
#include <vector>
#include "GameBoard.h"
#include "TicTacToeMove.h"
// #include "GameMove.h"

const int BOARD_SIZE_3 = 3;

class TicTacToeBoard : public GameBoard {
   
public:
   // Default constructor
   TicTacToeBoard();
   
   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;
   
   virtual void ApplyMove(GameMove *move);
   
   virtual void UndoLastMove();
   
   virtual GameMove *CreateMove() const { return new TicTacToeMove; }
   
   virtual bool IsFinished() const {
      return mPassCount == 2;
   }
   
   virtual std::string GetPlayerString(char player) {
      return (player == 1 ? "X" : "O");
      
   }
   
private:
   friend class TicTacToeView;
   char mBoard[BOARD_SIZE_3][BOARD_SIZE_3];
   int mPassCount;
   
   void CheckForWinner();
   
};


#endif /* defined(__Project_3__TicTacToeBoard__) */


