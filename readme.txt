Report.pdf also has the source codes and the execution snapshots.

input.txt is the file used for getting the input as a file.
If random generation option is chosen, please enter 0 in the console.


REPORT - PROGRAMMING ASSIGNMENT 4


SUMMARY

Application: Conway’s Game of Life

The evolution is determined by the initial state with no further input and creates the patterns with these four Conway’s rules :

1. Any live cell with fewer than two live neighbors dies, as if caused by under-population.

2. Any live cell with two or three live neighbor’s lives on to the next generation.

3. Any live cell with more than three live neighbors dies, as if by overcrowding.

4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

main.cpp : The driver will generate the starting state. I have set two options :

1. Read from text file (eg:input.txt which has the exact matrix location to be initialized. Format of the file: one live location per line; xCoordinate yCoordinate)

2. Random generator with the same seed so that it is repeatable.

callAll() : This initial input state is then transferred to all nodes (board locations) using the callAll() function. Then the method is invoked to set the out messages of the locations to set the current state (0 as dead, 1 as alive).

exchangeBoundary() : The out messages across the nodes get exchanged.

computeState() : Queries the out messages of all the 8 neighboring locations to calculate the number of live neighbors then it applies the 4 Conway’s rules to determine the next state.

If print is needed, we use callAll() to invoke getState() on all board locations to retrieve the current state of the board and print it on stdout. Prints the board based on the one-dimensional array. The symbol ‘#’ is used to denote a cell with life and the symbol ‘.’ to denote a cell without life.

Board.h : It is a derived class of Place.

setInitialState() : Set the state of this board location to the input argument.

getState() : Return the state of this board location to the caller

displayStateAsOut() : Set the outMessage as state of this board location.

computeState() : Use the outMessage of neighbors to determine the number of live neighbors. Apply the 4 Conway’s rules to compute the next state.

resetForNextTurn() : Resets the board for next turn.

Parallelization : Every cell works independently. The board is distributed to different computing nodes. The computation of number of live neighbors and the next state happens in parallel across all the board locations. Have used the callAll( int functionId, void *arguments[], int argument_size, int return_size )which in parallel calls the method specified with functionId of all array elements as passing arguments[i] to element[i]’s method, and receives a return value from it and exchangeBoundary( )of the Place from the MASS library.

EVALUATION OF EXECUTION

Graph 1: Performance Evaluation

Table 1: Performance Improvement for big sets Configuration 1 Node: 1 Thread 1 Node : 4 Threads 2 Node: 2 Threads 2 Node: 4 Threads 4 Nodes: 4 Threads 8 Nodes: 4 Threads 40 x 40 - 10 Turns 1.0 2.0 2.3 3.4 3.5 3.7

80 x 80 - 20 Turns
1.0
2.2
2.3
3.0
4.1
5.5 80 x 80 - 40 Turns 1.0 2.5 2.2 3.4 4.3 5.9
160 x 160 - 40 Turns
1.0
2.6
2.9
4.0
6.7
10.3 160 x 160 - 80 Turns 1.05 2.7 3.2 3.9 7.4 10.8
Table 2: Small Input sets (Execution Time in milliseconds) Configuration 1 Node : 1 Thread 2 Nodes : 2 Threads 4 Nodes : 4 Threads 8 X 8 - 4 Turns 722 4341 6436
16 x 16 - 4 Turns
6711
4936
6691 20 x 20 - 4 Turns 10230 7535 7725
40 x 40 - 4 Turns
37412
13766
11000

Observations:

 Increasing the thread count helps reducing the execution time.

 Increasing the node count also reduces the execution time.

 For small input sets increasing the node count increases execution time. The overhead of communication and synchronization seems to be more than the benefit of parallelization for small input sets.

 When comparing 1 node x 4 threads with 2 nodes x 2 threads each, the second configuration seems to be better. So given a choice between threads and nodes, increasing the number of nodes seems to help performance more.

1 Node: 1Thread
1 Node : 4Threads
2 Node: 2Threads
2 Node: 4Threads
4 Nodes: 4Threads
8 Nodes: 4Threads

40 x 40 - 10 Turns
84355
41662
36278
24696
24367
22803
80 x 80 - 20 Turns
408932
185771
177275
135001
99176
73961
80 x 80 - 40 Turns
750627
297461
339323
222429
172608
126517
160 x 160 - 40 Turns
2738883
1061937
960383
679248
408984
265113
160 x 160 - 80 Turns
5431255
2049051
1672511
1388680
735574
502313
0
1000000
2000000
3000000
4000000
5000000
6000000
Time in milliseconds

MASS Performance Evaluation

MASS PROGRAMMABILITY ANALYSIS

It is a moderate programming but the learning curve is steep because of lack of proper in-depth documentation. The only source for learning are the examples and the documentation. The examples provided were helpful to understand the implementation of the methods mentioned in the documentation. But once learnt, it is very easy and if given another project it can be done much faster than this.

It was easy to implement as the number of lines of code was less compared to MPI. The data distribution with Place is very simple and easy to use.

It has a very fast performance for bigger data size than the smaller data size.

Computational granularity: It is fine grain

Discovery of utilization is difficult as the documentation is not completely self-explanatory. The callAll() in documentation did not explain the case of multi-dimensional array clearly. Only from the sample programs under redhat in MASS-Cpp, I was able to understand the concept better.

land->callAll( Land::callalltest_, (void **)callargs, sizeof( int ),
sizeof( double ) );

For neighbors I created a static const array which had all the relative location of the 8 neighbors. Constant arguments which do not change does not accept const in signature. I could not use it as all the methods expect a non const argument only.

Inherent synchronization is very simple. It does not need open communication all the time. It is easier to maintain as we need to control only Places from the source.

For logging on/off mode, it would be nice if MASS controls over with a switch (set logging mode to verbose). I need to define the macro. 

If there is library support for that, the code will be much cleaner.

Not fault tolerant – If a machine in the machine list is down, MASS doesn’t pick the next available “up” node. This caused a lot of time being spent in identifying “up” and “down” nodes, for running with 8 nodes, even when lab machine pool has 15 nodes. The “up” machine list changes over time as well.

EXECUTION OUTPUT

Since the 8 nodes were not working all the time, there are many typescripts.
Executuion output :
typescript1: Most of the execution output results are in this
typescript2: Shows Node 8 : Thread 4 output with the connection failures
typescript3: Shows Node 8 : Thread 4 outputs
typescriptBinker : BLINKER pattern. With the print turned on (to print all the turns) and the input from input file option. Node 1 : Thread 1 and Node 4 : Thread 4.
Below are the few snap shots.

