/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich, Emily Raventos, Ashlee Hart
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"


 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   pos.setX(99.0);
   pos.setY(random(75.0, 95.0));
   angle.setRadians(0.0);
   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0, 2.0));
   status = PLAYING;
   fuel = 5000.0;
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   /*Acceleration acceleration;
   double ddx = 0.0;
   double ddy = gravity;
   
   
   acceleration.setDDY(gravity);*/
   pos.setX(0.0);
   return Acceleration();
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   velocity.add(acceleration, time);
   velocity.setDX(velocity.getDX()); 
   velocity.setDY(velocity.getDY());

   pos.setX((pos.getX() + velocity.getDX() * time) + (0.5 * acceleration.getDDX() * (time * time))); 
   pos.setY((pos.getY() + velocity.getDY() * time) + (0.5 * acceleration.getDDY() * (time * time)));
}
