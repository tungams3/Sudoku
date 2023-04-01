/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

/** This class is responsible any surface blitting etc
*/

class Surface
{
    public:
    Surface();

    static SDL_Surface* LoadPNG(char*);
    static bool DrawSurface(SDL_Surface*, SDL_Surface*, int, int);
};

#endif // SURFACE_H_INCLUDED
