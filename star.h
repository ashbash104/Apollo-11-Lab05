/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich, Ashlee Hart, and Emily Raventos
 * Sources:
 *    ChatGPT (but the code didn't work so not helpful)
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR
#include <vector>

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
   // Constructor
   Star() : pos(Position(0, 0)), phase(0) {}
   // Star() : position(random(-200, 200), random(-200, 200)), phase(random(0, 255)) {}
   Star(const Position& pos, unsigned char p) : pos(pos), phase(p) {}
   //static std::vector<Star> reset(); 

   void reset(double width, double height)
   {
      pos.setX(random(0.0, width));
      pos.setY(random(0.0, height));
      phase = random(0, 255);
   }

   // Method to draw the star
   void draw(ogstream & gout)
   {
      gout.drawStar(pos, phase++);
   }

   // Method to generate 50 stars with random positions and phases

private:
   Position pos; // Position of the star
   unsigned char phase; // Phase of the star
};
