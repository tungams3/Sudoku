/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Game.h"

void Game::Cleanup()        // Free all surfaces
{
    SDL_FreeSurface(Window);
    SDL_FreeSurface(DifficultyWindow);
    SDL_FreeSurface(Background);
    SDL_FreeSurface(Grid);
    SDL_FreeSurface(UndoButton);
    SDL_FreeSurface(RedoButton);
    SDL_FreeSurface(ResetButton);
    SDL_FreeSurface(SolutionButton);
    SDL_FreeSurface(PencilButton);
    SDL_FreeSurface(EraserButton);
    SDL_FreeSurface(Star);
    SDL_FreeSurface(Tick);

    TTF_CloseFont(Font);
    TTF_CloseFont(PencilFont);

    TTF_Quit();
    SDL_Quit();
}
