/***********************************************************************
 * Header File:
 *    LANDER
 * Author:
 *    Br. Helfrich, Emily Raventos, and Ashlee Hart
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#pragma once

#include "position.h"  // for POINT
#include "velocity.h"  // for VELOCITY
#include "thrust.h"    // for THRUST
#include "uiDraw.h"    // for DRAW* and RANDOM
#include "angle.h"     // for ANGLE

/*********************************************************
*LUNAR MODULE CONSTANTS
*********************************************************/
#define LANDER_WIDTH 20
#define MAX_SPEED 4.0
#define LANDER_WEIGHT 15103.00
#define LANDER_THRUST 45000.00
#define FUEL_MAIN_THRUST 10.0
#define FUEL_ROTATE 1.0
#define FUEL_MAX 5000.0
#define GRAVITY -1.65
#define TIME 0.08  // Mess around with this to get it right. 

enum Status { PLAYING, SAFE, DEAD };

class TestLander;

/****************************************************************
 * LANDER
 * The position and status of the lander
 ***************************************************************/
class Lander
{
   friend TestLander;

public:
   // to create a lander, we need to know something about the board
   Lander(const Position& posUpperRight) : status(PLAYING) { reset(posUpperRight); }

   // reset the lander and its position
   void reset(const Position& posUpperRight);

   // get the status of the lander
   bool     isDead()         const { return status == DEAD; }
   bool     isLanded()       const { return status == SAFE; }
   bool     isFlying()       const { return status == PLAYING; }
   Position getPosition()    const { return pos; }
   double   getSpeed()       const { return velocity.getSpeed(); }
   int      getFuel()        const { return (int)fuel; }
   int      getWidth()       const { return LANDER_WIDTH; }
   double   getMaxSpeed()    const { return MAX_SPEED; }

   // draw the lander on the screen
   void draw(const Thrust& thrust, ogstream& gout) const;

   // handle input
   Acceleration input(const Thrust& thrust, double gravity);

   // what happens when we coast?
   void coast(Acceleration& acceleration, double time);

   // straighten the lander and put it on the ground
   void land() 
   { 
      angle.setUp(); 
      status = SAFE; 
   }

   // we are dead. Draw the lander upside down
   void crash() 
   { 
      status = DEAD;
      angle.setDown();  
   }

private:
   Status   status;      // are we dead or not?
   Position pos;         // the location of the lander
   Velocity velocity;    // the speed of the lander
   Angle    angle;       // the orientation of the lander
   double   fuel;        // amount of fuel remaining
};
