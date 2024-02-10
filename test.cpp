/***********************************************************************
 * Source File:
 *    TEST
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner which will implement execute all the unit tests
 ************************************************************************/

#include "testPosition.h"
#include "testAcceleration.h"
#include "testVelocity.h"
#include "testAngle.h"
#include "testThrust.h"
#include "testLander.h"

/************************************
 * TEST RUNNER
 * Run all the unit tests
 ************************************/
void testRunner()
{
   // Unit tests
   TestAngle().run();
   TestAcceleration().run();
   TestVelocity().run();
   TestPosition().run();
   TestThrust().run();
   TestLander().run();
   TestThrust().run();
}
