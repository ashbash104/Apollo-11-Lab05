/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 * Authors: 
 *    Br. Helfirch, Ashlee Hart
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include "lander.h"
#include "star.h"
#include "acceleration.h"
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

   // set up the simulator
   Simulator(const Position& posUpperRight) : phase(0), ground(posUpperRight), lander(posUpperRight), thrust() { }
       
   // display stuff on the screen
   void display();
  
   unsigned char phase;
   Ground ground;

   void show50Stars() 
   {
      ogstream gout; 
      for (int i = 0; i < 50; i++)
      {
         // Create and set a random position 
         Position posStar; 
         posStar.setX(random(-200, 400)); 
         posStar.setY(random(-375, 750)); 
         gout.drawStar(posStar, phase); 
         //phase++; 
      }
   }
   
};

/**********************************************************
 * DISPLAY
 * Draw on the screen
 **********************************************************/
void Simulator::display()

// We need a method to coast and to grab the thrust from the UI. 
// coast will take the thrust from get input and add velocity or acceleration to it. Input gets that from the UI, depending on what button is pressed.
{
   ogstream gout;
   
   // draw a star
   Position posStar;
   posStar.setX(100);
   posStar.setY(375);
   gout.drawStar(posStar, phase);
   phase++;

   string text = "Hello World";

  /* Position posText;
   posText.setX(-100);
   posText.setY(-375);

   ogstream ogstream;
   ogstream.drawText(posTopLeft, text);*/

   //show50Stars();
   // draw the ground
   ground.draw(gout);
   gout << "Fuel: " << lander.getFuel() << endl;
   gout << "Altitude: " << ground.getElevation(lander.getPosition()) << endl;
   gout << "Speed: " << lander.getSpeed() << endl;


   // draw the lander
   Position posLander;
   posLander.setX(200);
   posLander.setY(375);
   //gout.drawLander(posLander, lander.getRadians());
   //lander.coast(lander.input(pSimulator->thrust, gravity);
   lander.draw(thrust, gout);
   //cout << a.getRadians() << "\n";

   //phase++;

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

    //handle input
   //if (pUI->isRight())
   //   //pSimulator->lander.moveRight();
   //   pSimulator->a.add(-0.1);
   //if (pUI->isLeft())
   //   //pSimulator->lander.moveLeft();  
   //   pSimulator->a.add( 0.1);
   //if (pUI->isDown())
   //   //pSimulator->lander.moveDown();
   //   gout.drawLanderFlames();


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
