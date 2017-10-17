#!/bin/sh

export MASS_DIR=../..
g++ -Wall Board.cpp -I$MASS_DIR/source -shared -fPIC -o Board
g++ -Wall main.cpp Timer.cpp -I$MASS_DIR/source -L$MASS_DIR/ubuntu -lmass -I$MASS_DIR/ubuntu/ssh2/include -L$MASS_DIR/ubuntu/ssh2/lib -lssh2 -o main
