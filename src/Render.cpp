/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Game.h"
#include "GridNumbers.h"

using namespace std;

void Game::ReloadGrid()
{
    if (Grid != NULL)
       SDL_FreeSurface(Grid);

    if ((Grid = Surface::LoadPNG((char*) "./gfx/Grid.png")) == NULL)
        return;
}

void Game::Render()
{
    // Draw surfaces onto window
    Surface::DrawSurface(Window, Background, 0, 0);
    Surface::DrawSurface(Window, Grid, 53, 53);
    Surface::DrawSurface(Window, ResetButton, 660, 190);
    Surface::DrawSurface(Window, SolutionButton, 660, 325);
    Surface::DrawSurface(Window, PencilButton, 660, 460);
    Surface::DrawSurface(Window, EraserButton, 660, 575);

    if (DifficultyChosen == false)
    {
        if (DifficultyWindow == NULL)
            DifficultyWindow = Surface::LoadPNG((char*) "./gfx/DifficultyWindow.png");

        Surface::DrawSurface(Window, DifficultyWindow, 169.5, 150);

        if (UndoGreyed == NULL)
            UndoGreyed = Surface::LoadPNG((char*) "./gfx/UndoGreyed.png");

        if (RedoGreyed == NULL)
            RedoGreyed = Surface::LoadPNG((char*) "./gfx/RedoGreyed.png");

        Surface::DrawSurface(Window, UndoGreyed, 660, 55);
        Surface::DrawSurface(Window, RedoGreyed, 780, 55);
    }

    else
    {
        if (DifficultyWindow != NULL)
        {
            SDL_FreeSurface(DifficultyWindow);
            DifficultyWindow = NULL;
        }

        for (int i = 1; i <= SelectedLevel; ++i)
            Surface::DrawSurface(Window, Star, 200 + (65 * (i % 4)), 660);      // Draw stars according to difficulty

        if (EraserEnabled == true)
            Surface::DrawSurface(Window, Tick, 880, 608);

        // Undo/redo buttons
        UndoRedoRender();
    }

    if ((drawn == 0) && (DifficultyChosen == true))     // If numbers have been drawn and difficulty chosen
    {
        if (SolutionInitialized == false)       // If solution hasn't been generated
        {
            ReloadGrid();
            InitializeSolution();

            for(int i = 0; i <= 80; ++i)
                GridElements[i] = SolutionElements[i][0];

            SolutionInitialized = true;
        }

        if (ShowSolution == true)       // If the user wants to see the solution
        {
            for(int i = 0; i <= 80; ++i)
                GridElements[i] = SolutionElements[i][0];

            if (SolutionCells.size() != 0)
                SolutionCells.clear();

            for(int i = 0; i <= 80; ++i)
            {
                if (GridElements[i] != -1)
                {
                    SolutionCells.push_back(i);
                }
            }

            ReloadGrid();
            ShowSolution = false;
        }

        else
        {
            DetermineDifficulty(GridElements);

            if (SolutionCells.size() != 0)
                SolutionCells.clear();

            for(int i = 0; i <= 80; ++i)
            {
                if (GridElements[i] != -1)
                {
                    SolutionCells.push_back(i);
                }
            }
        }

        DrawGridNumbers(Grid, Font, FontColour);
        drawn = 1;
    }

    if ((SDL_Flip(Window)) != 0)
        cout << "Error updating screen " << endl;       // Update the window
}
