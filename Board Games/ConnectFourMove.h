//
//  ConnectFourMove.h
//  Project 3
//
//  Created by Hao Lu on 5/3/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#ifndef __Project_3__ConnectFourMove__
#define __Project_3__ConnectFourMove__

#include <stdio.h>
#include "GameMove.h"
#include <iostream>

class ConnectFourMove : public GameMove {
private:
   friend class ConnectFourBoard;
   
   int mRow, mCol;
   
   ConnectFourMove();
   ConnectFourMove(int row, int col);
   
public:
   virtual GameMove& operator=(const std::string &);
   virtual bool Equals(const GameMove &other) const;
   virtual operator std::string() const;
   
   static int mOnHeap;
   
   static void* operator new(std::size_t sz){
      mOnHeap++;
      std::cout << "operator new: " << mOnHeap << " ConnectFourMove on the heap" << std::endl;
      return ::operator new(sz);
   }
   
   static void operator delete(void* ptr, std::size_t sz) {
      mOnHeap--;
      std::cout << "operator delete: " << mOnHeap << " ConnectFourMove on the heap" << std::endl;
      ::operator delete(ptr);
   }
   
   
};

#endif /* defined(__Project_3__ConnectFourMove__) */
