/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
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
   // Star() : position(random(-200, 200), random(-200, 200)), phase(random(0, 255)) {}
   Star(const Position& pos, unsigned char p) : position(pos), phase(p) {}

   // Method to draw the star
   void draw(ogstream& gout) const
   {
      gout.drawStar(position, phase);
   }

   // Method to generate 50 stars with random positions and phases
   static std::vector<Star> reset()
   {
      std::vector<Star> stars;
      for (int i = 0; i < 50; ++i)
      {
         Position position(random(-200, 200), random(-200, 200));
         unsigned char phase = random(0, 255);
         stars.emplace_back();
      }         
      return stars;
   }


private:
   Position position; // Position of the star
   unsigned char phase; // Phase of the star
};
