/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Game.h"

// This function initializes everything and loads images

bool Game::Init()
{
    if ((SDL_Init(SDL_INIT_EVERYTHING)) == -1)
        return false;

    if ((TTF_Init()) == -1)
        return false;

    if ((Window = SDL_SetVideoMode(933, 700, 0, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
        return false;

    if ((DifficultyWindow = Surface::LoadPNG((char*) "./gfx/DifficultyWindow.png")) == NULL)
        return false;

    if ((Background = Surface::LoadPNG((char*) "./gfx/background.png")) == NULL)
        return false;

    if ((Grid = Surface::LoadPNG((char*) "./gfx/Grid.png")) == NULL)
         return false;

    if ((UndoGreyed = Surface::LoadPNG((char*) "./gfx/UndoGreyed.png")) == NULL)
         return false;

    if ((RedoGreyed = Surface::LoadPNG((char*) "./gfx/RedoGreyed.png")) == NULL)
         return false;

    if ((ResetButton = Surface::LoadPNG((char*) "./gfx/ResetButton.png")) == NULL)
        return false;

    if ((SolutionButton = Surface::LoadPNG((char*) "./gfx/SolutionButton.png")) == NULL)
        return false;

    if ((PencilButton = Surface::LoadPNG((char*) "./gfx/PencilButton.png")) == NULL)
        return false;

    if ((EraserButton = Surface::LoadPNG((char*) "./gfx/EraserButton.png")) == NULL)
        return false;

    if ((Star = Surface::LoadPNG((char*) "./gfx/Star.png")) == NULL)
        return false;

    if ((Tick = Surface::LoadPNG((char*) "./gfx/Tick.png")) == NULL)
        return false;

    if ((Font = TTF_OpenFont("./gfx/font.TTF", 45)) == NULL)
    {
        printf("TTF Error: %s\n", TTF_GetError());
        return false;
    }

    if ((PencilFont = TTF_OpenFont("./gfx/font.TTF", 22.5)) == NULL)
    {
        printf("TTF Error: %s\n", TTF_GetError());
        return false;
    }

    ClearStacks();      // Clear memory stacks of undo/redo functions

    SDL_FillRect(Window, &WindowRect, SDL_MapRGB(Window->format, 0XFF, 0XFF, 0XFF));    // Fill screen white

    return true;
}

