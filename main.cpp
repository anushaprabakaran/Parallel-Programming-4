// Conway's Game of Life
// main.cpp 
// Its evolution is determined by its initial state, requiring no further input.
// The input is got in as a file (eg:input.txt) or generates the starting state as random number.
// 



#include "MASS.h"
#include "Board.h"
#include "Timer.h"   //Timer
#include <stdlib.h>  // atoi
#include <unistd.h>
#include <cstring>
#include <vector>

// If true, prints out every turn
//const bool printOutput = true; 
// If false, prints only the inital and final output after all turns 
const bool printOutput = false;

// Prints the board based on the one-dimensional array
// # is used to denote a cell with life and . to denote
// a cell without life
void printBoard(int* output, int sizeX, int sizeY) {
	std::cout << std::endl;

	for( int i = 0; i < sizeY; i++ ) {
		for( int j = 0; j < sizeX; j++ ) {
			if( *(output + j + (i * sizeX)) == 0 ) {
				std::cout << ".";
			}
			else {
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Timer timer;

int main( int argc, char *args[] ) {

	// Check that all arguments are present 
	// Exit with an error if they are not
	if ( argc != 11 ) {
		cerr << "usage: ./main username password machinefile port nProc nThreads numGenerations sizeX sizeY inputFile" << endl;
		return -1;
	}
  
	// Get the arguments passed in
	char *arguments[4];
	arguments[0] = args[1]; // username
	arguments[1] = args[2]; // password
	arguments[2] = args[3]; // machinefile
	arguments[3] = args[4]; // port
	
	int nProc = atoi( args[5] ); // number of processes
	int nThr = atoi( args[6] );  // number of threads
  
	const int numGenerations = atoi( args[7] );	//Run this simulation for numGenerations
	const int sizeX = atoi( args[8] );  // size of the board
	const int sizeY = atoi( args[9] );  // size of the board
	char* inputFileName = args[10];  // input file name

	// Initialize MASS with the machine information,
	// Number of processes, and number of threads
	MASS::init( arguments, nProc, nThr ); 

	// Prepare a message for the places (this is argument below)
	char *msg = (char *)("hello\0"); // should not be char msg[]
  
	// Create the places.
	// Arguments are, in order:
	//    handle, className, boundary_width, argument, argument_size, dim, ...
	Places *board = new Places( 1, "Board", 1, msg, 7, 2, sizeX, sizeY );

	int inputState[sizeX][sizeY];
	for( int i = 0; i < sizeX; i++ ) {
		for( int j = 0; j < sizeY; j++ ) {
			inputState[i][j] = 0;
		}
	}
	
	int x, y;
	
	// Reading the input text file to intialize the state of the board.
	// Format of the file : One live location per line 
	// xCoordinate yCoordinate
	// (or) Randomly generate with same seed as it is repeatble
	if(inputFileName[0] != '0' || strlen(inputFileName) != 1) {
		std::ifstream infile(inputFileName);
		while( infile >> x >> y ) {
		    if( (x < 0 || x >= sizeX) || (y < 0 || y >= sizeY) ) {
		    	std::cerr << "Invaild input coordinates" << x <<"," << y << endl;
		    }
		    else {
		    	inputState[x][y] = 1;
		    	
	        }
		}
	}
	else {
		srand (1);
		for( int i = 0; i < sizeX; i++ ) {
			for( int j = 0; j < sizeY; j++ ) {
				if( rand() % 3 == 0 ) {
					inputState[i][j] = 1;
				}
			}
		}
	}

	board->callAll(Board::init_);	//Initialize the Board

	// Pass the intial state as read from the input file to the each board location
    int *retVals = (int *)board->callAll(Board::setInitialState_, (void **)inputState, sizeof(int), sizeof(int));
    printBoard(retVals, sizeX, sizeY);
    delete retVals;
    
	timer.start();
		
	for( int turn = 0; turn < numGenerations; turn++ ) {
		if( printOutput ) {
			int* currentTurn = new int;
			*currentTurn = turn;
			std::cerr << "Printing Board for turn " << turn << std::endl;
			// Get the current state of each board location in parallel
			int *retVals = (int *)board->callAll(Board::getState_, (void **)inputState, sizeof(int), sizeof(int));	// display the current state
			printBoard(retVals, sizeX, sizeY);
			delete retVals;
		}

		// Set the out message of each board location as its curent state
		board->callAll(Board::displayStateAsOut_);	

		// Exchange information on the boundary nodes.
		board->exchangeBoundary();

		// Compute the next state of each of the board locations by using the 
		// rules of the "Game of Life"
		board->callAll(Board::computeState_);
	}
	
	// Prints the board	after all generations
	std::cerr << "Printing Board after turn " << numGenerations << std::endl;
	retVals = (int *)board->callAll(Board::getState_, (void **)inputState, sizeof(int), sizeof(int));	// Display the current state
	printBoard(retVals, sizeX, sizeY);
	delete retVals;
	
	long elaspedTime_END =  timer.lap();
	printf( "\nEnd of simulation. Elasped time using MASS framework with %i processes and %i thread and %i generations :: %ld \n",nProc,nThr,numGenerations, elaspedTime_END);
  
	MASS::finish( );
}
