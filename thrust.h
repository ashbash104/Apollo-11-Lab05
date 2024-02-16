/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface
#include <iostream>
using namespace std; 

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      return (clockwise ? 0.1 : 0.0) +
      (counterClockwise ? -0.1 : 0.0);
      /*double radAngle = 0.0;
      if (clockwise == true && counterClockwise == false) { radAngle += 0.1; }
      else if (clockwise == false && counterClockwise == true) { radAngle -= 0.1; }

      return radAngle;*/
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      return 45000.00 / 15103.00;
   }


   // reflect what is firing
   bool isMain()    const { return mainEngine == true;       }
   bool isClock()   const { return clockwise == true;        }
   bool isCounter() const { return counterClockwise == true; }

   // set the thrusters
   void set(const Interface * pUI)
   {
      mainEngine       = pUI->isDown();
      clockwise        = pUI->isLeft();
      counterClockwise = pUI->isRight();
      cout << mainEngine << ", " << clockwise << ", " << counterClockwise << "\n";
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
// Create object in simulator to get thrust, 
// Set it
