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
#include "thrust.h"


 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   angle.setUp();
   
   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0, 2.0));
   pos.setX(posUpperRight.getX() - 1.0); 
   pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));
   status = PLAYING;
   fuel = FUEL_MAX;
   /*pos.setX(99.0);
   pos.setY(random(75.0, 95.0));
   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0, 2.0));*/
   
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   gout.drawLander(pos, angle.getRadians());
   if (isFlying() && fuel > 0.0)
      gout.drawLanderFlames(pos, angle.getRadians(),
         thrust.isMain(), thrust.isClock(), thrust.isCounter());
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   Acceleration acceleration; 

   acceleration.addDDY(gravity);
   if (fuel == 0.0)
      return acceleration;
   //double angle = thrust.rotation();

   if (thrust.isMain())
   {
      double power = (LANDER_THRUST / LANDER_WEIGHT);
      acceleration.addDDX(-sin(angle.getRadians())* power); 
      acceleration.addDDY((cos(angle.getRadians()) * power)); 
      fuel -= FUEL_MAIN_THRUST;
      cout << fuel << "\n";
   }

   if (thrust.isClock()) 
   {
      angle.add(0.1);
      fuel -= FUEL_ROTATE;
   }

   if (thrust.isCounter())
   {
      angle.add(-0.1);
      fuel -= FUEL_ROTATE;
   }

   if (fuel < 0.0)
   {
      fuel = 0.0;
   }

   return acceleration;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   velocity.add(acceleration, time);
   pos.add(acceleration, velocity, time);
}
