/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Surface.h"

using namespace std;

Surface::Surface()
{}

SDL_Surface* Surface::LoadPNG(char* File)          // Load a PNG image
{
    SDL_Surface* Temp = NULL;
    SDL_Surface* Return = NULL;

    if ((Temp = IMG_Load(File)) == NULL)
        return NULL;

    Return = SDL_DisplayFormatAlpha(Temp);
    SDL_FreeSurface(Temp);

    return Return;
}

// Draw one surface onto another
bool Surface::DrawSurface(SDL_Surface* Dest, SDL_Surface* Src, int x, int y)
{
    if (Dest == NULL || Src == NULL)
        return false;

    SDL_Rect DestR;

    DestR.x = x;
    DestR.y = y;

    SDL_BlitSurface(Src, NULL, Dest, &DestR);

    return true;
}
