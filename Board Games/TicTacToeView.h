//
//  TicTacToeView.h
//  Project 3
//
//  Created by Hao Lu on 5/2/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#ifndef __Project_3__TicTacToeView__
#define __Project_3__TicTacToeView__

#include <stdio.h>
#include "TicTacToeBoard.h"
#include "GameView.h"

class TicTacToeView : public GameView {
private:
   TicTacToeBoard *mTicTacToeBoard;
   virtual void PrintBoard(std::ostream &s) const;
   
public:
   TicTacToeView(GameBoard *b) : mTicTacToeBoard(dynamic_cast<TicTacToeBoard*>(b)) {}
};

#endif /* defined(__Project_3__TicTacToeView__) */
