//
//  main.cpp
//  Project 3
//
//  Created by Hao Lu on 4/30/15.
//  Copyright (c) 2015 Hao Lu. All rights reserved.
//

#include "GameBoard.h"
#include "OthelloBoard.h"
#include "TicTacToeBoard.h"
#include "ConnectFourBoard.h"
#include "GameView.h"
#include "OthelloView.h"
#include "TicTacToeView.h"
#include "ConnectFourView.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/*
 
 TO DO LIST
 
 Check destructor for GameBoard x
 Check casting
 Delete board after done x
 Print board after tic tac toe won x
 Call possible moves for tie x
 
 
 */

int main(int argc, const char * argv[]) {
   GameBoard *board;
   GameView *v;
   string userInput; // a string to hold the user's command choice
   vector<GameMove *> possMoves; // a holder for possible moves
   int gameType;
   string command, position;
   
   do {
      cout << "What game do you want to play" << endl;
      cout << "1) Othello" << endl;
      cout << "2) Tic Tac Toe" << endl;
      cout << "3) Connect Four " << endl;
      cout << "4) Exit" << endl;
      cin >> gameType;
      // Clear cin buffer for getline
      cin.ignore();
      
      if (gameType == 1) {
         board = new OthelloBoard();
         v = new OthelloView(board);
      }
      else if (gameType == 2) {
         board = new TicTacToeBoard();
         v = new TicTacToeView(board);
      }
      else if (gameType == 3) {
         board = new ConnectFourBoard();
         v = new ConnectFourView(board);
      }
      else if (gameType == 4) {
         break;
      }
      
      do {
         // Print out the board
         cout << *v << endl;
         
         // For inner loop
         bool input = true;
         
         // Print out current player turn
         cout << board->GetPlayerString(board->GetNextPlayer()) + "'s turn" << endl;
         
         // Possible moves
         board->GetPossibleMoves(&possMoves);
         cout << "Possible moves: ";
         for (GameMove* move : possMoves) {
            cout << (string)*move << " ";
         }
         cout << "" << endl;
         
         while (input) {
            cout << "\nEnter in a command: ";
            getline(cin, userInput);
            istringstream ss(userInput);
            
            // string command, position;
            ss >> command >> position;
            
            if (command.compare("move") == 0) {
               // Creates a GameMove on the heap
               GameMove* m = board->CreateMove();
               try {
                  *m = position;
               }
               catch (GameException &oe) {
                  cout << "\n" << oe.what( )<< "\n" << endl;
                  delete m;
                  break;
               }
               bool valid = false;
               for (GameMove* move : possMoves) {
                  if (*m == *move) {
                     valid = true;
                     break;
                  }
               }
               if (valid == false) {
                  cout << "\nNot a valid move\n" << endl;
               }
               else {
                  board->ApplyMove(m);
               }
               delete m;
               input = false;
               
            }
            else if (command.compare("undo") == 0) {
               for (int i = 0; i < stoi(position); i++) {
                  // Check so can't undo large number of times
                  if (board->GetMoveHistory()->size() == 0) {
                     cout << "No moves to undo" << endl;
                     break;
                  }
                  board->UndoLastMove();
               }
               input = false;
               
            }
            else if (command.compare("showValue") == 0) {
               cout << "\nBoard value: " << board->GetValue() << "\n" << endl;
               input = false;
               
            }
            else if (command.compare("showHistory") == 0) {
               int player = board->GetNextPlayer();
               for (long i = board->GetMoveHistory()->size() - 1; i >= 0; i--) {
                  player = -player;
                  cout << board->GetPlayerString(player) <<  ":"
                  <<(string)*board->GetMoveHistory()->at(i) << endl;
               }
               cout << "" << endl;
               input = false;
               
            }
            else if (command.compare("quit") == 0) {
               input = false;
            }
            else {
               cout << "\nNot a valid command\n" << endl;
               input = false;
            }
         }
         // Clear possible moves vector and delete it off the heap
         for (GameMove* move : possMoves) {
            delete move;
         }
         possMoves.clear();
         
         // Quit out of the current game
         if (command.compare("quit") == 0) {
            break;;
         }
         
      } while(!board->IsFinished());
      cout << *v << endl;
      delete board;
      delete v;
   } while(gameType != 3);
   
}
