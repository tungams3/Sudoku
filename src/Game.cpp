/**************************************
* Suduko                              *
*                                     *
* By Scott McGregor                   *
**************************************/

/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Game.h"

// Find main function below

Game::Game()            // Initializes variables
{
    Window = NULL;
    DifficultyWindow = NULL;
    Grid = NULL;
    UndoButton = NULL;
    UndoGreyed = NULL;
    RedoButton = NULL;
    RedoGreyed = NULL;
    ResetButton = NULL;
    SolutionButton = NULL;
    PencilButton = NULL;
    Background = NULL;
    Star = NULL;
    Tick = NULL;

    Font = NULL;
    PencilFont = NULL;

    SolutionInitialized = false;
    ShowSolution = false;

    NumberCount = 0;
    GuessCount = 0;

    FontColour = {0, 0, 0};
    PencilFontColour = {128, 128, 128};

    WindowRect.x = 0;
    WindowRect.y = 0;
    WindowRect.h = 700;
    WindowRect.w = 950;
}


int Game::Execute()
{
    if (Init() == false)        // Initiate SDL, load images etc
        return -1;

    SDL_Event event;

    while (Running)
    {
        while (SDL_PollEvent(&event))
            HandleEvents(&event);

        Logic();
        Render();
    }

    Cleanup();

    return 0;
}

int main(int argc, char** argv)
{
    Game game;

    srand(time(NULL));      // For random number generator used in Solution class
    return game.Execute();
}
