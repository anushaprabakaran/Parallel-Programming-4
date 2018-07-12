// Conway's Game of Life
// Board.h : Every board cell has eight neighbours. 
// It is a dervied class of Place.
// 


#ifndef Land_H
#define Land_H

#include <string.h>
#include "Place.h"

using namespace std;

class Board : public Place {
public:

	static const int NUM_NEIGHBORS = 8;    // A cell has 8 neighbors
  
  // Define functionId's that will 'point' to the functions they represent.
  static const int init_ = 0;
  static const int setInitialState_ = 1;
  static const int getState_ = 2;
  static const int displayStateAsOut_ = 3;
  static const int computeState_ = 4;
  static const int resetForNextTurn_ = 5;
      
  /**
   * Initialize a Board object by allocating memory for it.
   */
  Board( void *argument ) : Place( argument ) {
    bzero( arg, sizeof( arg ) );
    strcpy( arg, (char *)argument );
  };
  
  /**
   * The callMethod uses the function ID to determine which method to execute.
   * It is assumed the arguments passed in contain everything those 
   * methods need to run.
   */
  virtual void *callMethod( int functionId, void *argument ) {
    switch( functionId ) {
    case init_: return init( argument );
    case setInitialState_: return setInitialState( argument );
    case getState_: return getState( argument );
    case displayStateAsOut_: return displayStateAsOut( argument );
    case computeState_: return computeState( argument );
    case resetForNextTurn_: return resetForNextTurn();
    }
    return NULL;
  };

private:
  char arg[100];
  void *init( void *argument );
  void *setInitialState( void *argument );
  void *getState( void *argument );
  void *displayStateAsOut( void *argument );
  void *computeState( void *argument );						
  void *resetForNextTurn();
  static const int neighbor[8][2];		//Array form of cardinals
  int myState;											
    
};

#endif
