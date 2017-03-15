//
//  ConnectFourView.h
//  Project 3
//
//  Created by Hao Lu on 5/3/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#ifndef __Project_3__ConnectFourView__
#define __Project_3__ConnectFourView__

#include <stdio.h>
#include "GameView.h"
#include "ConnectFourBoard.h"

class ConnectFourView : public GameView {
private:
   ConnectFourBoard *mConnectFourBoard;
   virtual void PrintBoard(std::ostream &s) const;
   
public:
   ConnectFourView(GameBoard *b) : mConnectFourBoard(dynamic_cast<ConnectFourBoard*>(b)) {}
};

#endif /* defined(__Project_3__ConnectFourView__) */
