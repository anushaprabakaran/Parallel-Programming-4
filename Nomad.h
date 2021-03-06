#ifndef NOMAD_H
#define NOMAD_H

#include "Agent.h"
#include "MASS_base.h"
#include <sstream> // ostringstream

//Used to toggle output in Nomad.h
const bool printOut = false;
//const bool printOut = true;

using namespace std;

class Nomad : public Agent {

 
 public:
  // define functionId's that will 'point' to the functions they represent.
  static const int agentInit_ = 0;
  static const int somethingFun_ = 1;
  static const int createChild_ = 2;
  static const int killMe_ = 3;
  static const int move_ = 4;
  static const int callalltest_ = 5;
  static const int addData_ = 6;
  static const int move2_ = 7;
  
   /**
   * Initialize a Nomad object
   */
  Nomad( void *argument ) : Agent( argument ) {
    if(printOut == true)
        MASS_base::log( "BORN!!" );
  };
  
  /**
   * the callMethod uses the function ID to determine which method to execute.
   * It is assumed the arguments passed in contain everything those 
   * methods need to run.
   */
  virtual void *callMethod( int functionId, void *argument ) {
    switch( functionId ) {
    case agentInit_: return agentInit( argument );
    case somethingFun_: return somethingFun( argument );
    case createChild_: return createChild( argument );
    case killMe_: return killMe( argument );
    case move_: return move( argument );
    case callalltest_: return callalltest( argument );
    case addData_: return addData( argument );
    case move2_: return move2( argument );
    }
    return NULL;
  };

 private:
  void *agentInit( void *argument );
  void *somethingFun( void *argument );
  void *createChild( void *argument );
  void *killMe( void *argument );
  void *move( void *argument );
  void *callalltest( void *argument );
  void *addData( void *argument );
  void *move2( void *argument );
};

#endif
