// Conway's Game of Life
// Board.cpp : Impementation of Board.h
// 


#include "Board.h"
#include "MASS_base.h"
#include <sstream>     // ostringstream


extern "C" Place* instantiate( void *argument ) {
  return new Board( argument );
}

extern "C" void destroy( Place *object ) {
  delete object;
}

/**
 * Initializes a Board object.
 */
void *Board::init( void *argument ) {
  
  resetForNextTurn();					

  //Initialize by clearing the state
  myState = 0;
  
  return NULL;
}

const int Board::neighbor[NUM_NEIGHBORS][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

/** (void)
*	Resets for the next turn
*/
void *Board::resetForNextTurn() {
	outMessage = NULL;
	outMessage_size = 0;
	inMessages.clear();	
	return NULL;
}

/** (void)
*	Set the state of this board location to the input argument
*/
void *Board::setInitialState( void* argument ) {
  	int *retVal = new int;
  	*retVal = *(int *)argument;
	//Debug logging: 
    myState = *(int *)argument;
	
	//Debug logging: 
	//ostringstream convert1;
	//convert1 << "setInitialState:  Board[" << index[0] << "][" << index[1] << "] has the state of " << myState << " argument " << argument;
	//MASS_base::log( convert1.str( ) );
	
	return retVal;
}

/** (void)
*	Set the outmessage as state of this board location
*/
void *Board::displayStateAsOut( void* argument ) {
	outMessage_size = sizeof( int );
    outMessage = new int( );
    *(int *)outMessage = myState;
	
	//Debug logging: 
	//ostringstream convert;
	//convert << "displayStateAsOut:  Board[" << index[0] << "][" << index[1] << "] has the state of " << myState;
	//MASS_base::log( convert.str( ) );
	
	return NULL;
}

/** (void)
*	Return the state of this board location to the caller
*/
void *Board::getState( void* argument )
{
	int *retVal = new int;
    *retVal = myState;
	
	//Debug logging: 
	//ostringstream convert;
	//convert << "getState:  Board[" << index[0] << "][" << index[1] << "] has the state of " << myState;
	//MASS_base::log( convert.str( ) );
	
	return retVal;
}

/** (void)														
*	Use the outmessage of neighbors to determine the number of live neighbors.
*   Apply the 4 rules to compute the next state.
*/
void *Board::computeState(void *argument) {
	int liveNeighbors = 0;
	// Count the number of live neighbors
	for ( int i = 0; i < NUM_NEIGHBORS; i++ ) {
    	int *ptr = (int *)getOutMessage( 1, const_cast<int*>(neighbor[i]) );
    	if( ptr != NULL && *ptr == 1 ) {
        	liveNeighbors++;
        }
    }

	int nextState = 0;
	
	/*
	Rules:
	1.	Any live cell with fewer than two live neighbours dies, as if caused by under-population.
	2.	Any live cell with two or three live neighbours lives on to the next generation.
	3.	Any live cell with more than three live neighbours dies, as if by overcrowding.
	4.	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
	*/
	if( myState == 1 && liveNeighbors < 2 ) { //rule 1
		nextState = 0;
	}
	else if( myState == 1 && (liveNeighbors == 2 || liveNeighbors == 3) ) { //rule 2
		nextState = 1;
	}
	else if( myState == 1 && liveNeighbors > 3 ) { //rule 3
		nextState = 0;
	}
	else if( myState == 0 && liveNeighbors == 3 ) { //rule 4
		nextState = 1;
	}

	//Debug logging: 
	//ostringstream convert;
	//convert << "computeState[" << index[0] << "][" << index[1] 
	//  << "]  liveNeighborcount = " << liveNeighbors << " current state " << myState 
	//  << " next State " << nextState;
	//MASS_base::log( convert.str( ) );

	myState = nextState;
	
	return NULL;
}
