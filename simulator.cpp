/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 * Authors: 
 *    Br. Helfirch, Ashlee Hart, and Emily Raventos
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include "lander.h"      // for lander
#include "star.h"        // for star
#include "acceleration.h"// for acceleration
#include "windows.h"     // for sleep

using namespace std;

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public: 
   Lander lander;
   Thrust thrust;
   bool needToSleep;
   Star stars[50];

   // set up the simulator
   Simulator(const Position& posUpperRight) : ground(posUpperRight), lander(posUpperRight), thrust(), needToSleep(false)
   {
      for (int i = 0; i < 50; i++)
      {
         stars[i].reset(posUpperRight.getX(), posUpperRight.getY());
      }
   }
       
   // display stuff on the screen
   void display();
  
   Ground ground;

   void drawStars(ogstream &gout)
   {
      for (int i = 0; i < 50; i++)
      {
         stars[i].draw(gout);
      }
   }
};

/**********************************************************
 * DISPLAY
 * Draw on the screen
 **********************************************************/
void Simulator::display()
{
   ogstream gout;

   // Pause for user to see end message, then reset.
   if (needToSleep)
   {
      Sleep(2000);
      needToSleep = false;
      lander.reset(ground.getUpperRight());
      ground.reset();
   }

   // draw 50 stars
   drawStars(gout);

   // draw the ground
   ground.draw(gout);

   // set position and display stats
   Position posText;
   posText.setX(20);
   posText.setY(375);

   gout.setPosition(posText);

   gout << "Fuel: " << lander.getFuel() << endl;
   gout << "Altitude: " << ground.getElevation(lander.getPosition()) << endl;
   gout << "Speed: " << lander.getSpeed() << endl;

   // set position and display end message
   Position endText;
   endText.setX(125);
   endText.setY(250);

   gout.setPosition(endText);

   // change status and end when hits ground
   if (ground.hitGround(lander.getPosition(), LANDER_WIDTH))
   {
      gout << "Houston, we have a problem!" << endl;
      lander.crash();
      needToSleep = true;
   }

   // change status and end when lands
   if (ground.onPlatform(lander.getPosition(), LANDER_WIDTH))
   {
      gout << "The Eagle has landed!" << endl;
      lander.land();
      needToSleep = true;
   }

   // draw lander
   lander.draw(thrust, gout);
}

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   ogstream gout;
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;
   pSimulator->thrust.set(pUI);
   pSimulator->lander.input(pSimulator->thrust, GRAVITY);
   pSimulator->lander.coast(pSimulator->lander.input(pSimulator->thrust, GRAVITY), TIME);

   // draw the game
   pSimulator->display();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
#ifdef _WIN32
   AllocConsole();
   FILE* stream;
   errno_t err;
   err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);
   //simulator.show50Stars();

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
