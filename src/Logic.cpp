/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Game.h"
#include "GridNumbers.h"

void Game::Logic()
{
    HandleClickedEvents();
}

/* The following code should be relatively easy to follow. It checkes for what button has
*been clicked and acts accordingly
*/

void Game::HandleClickedEvents()
{
    if (GridClicked == true)
    {
        if (MousePressed == true)
        {
            SelectedCell = FindSelectedCell();

            if (PencilMarks == true)
                FindGuessPosition();
        }

        else
        {
            if (PencilMarks == true)
            {
                if (EraserEnabled == true)
                    EraseGuess();

                else
                    DrawGuess();
            }

            else
            {
                if (EraserEnabled == true)
                    EraseNumber();

                else
                    DrawNumber();
            }

            DrawGridNumbers(Grid, Font, FontColour);
            drawn = 1;
        }

        GridClicked = false;
    }

    else if (UndoClicked == true)
    {
        if (PencilMarks == true)
            UndoGuess();

        else
            UndoNumber();

        DrawGridNumbers(Grid, Font, FontColour);
        drawn = 1;

        UndoClicked = false;
    }

    else if (RedoClicked == true)
    {
        if (PencilMarks == true)
            RedoGuess();

        else
            RedoNumber();

        DrawGridNumbers(Grid, Font, FontColour);
        RedoClicked = false;
    }

    else if (ResetClicked == true)
    {
        SolutionInitialized = false;
        ResetClicked = false;
        DifficultyChosen = false;

        drawn = 0;
        NumberCount = 0;
        GuessCount = 0;
        PencilMarks = false;
        EraserEnabled = false;

        ClearStacks();
        ClearElements();
    }

    else if (SolutionClicked == true)
    {
        drawn = 0;
        SolutionInitialized = true;
        ShowSolution = true;
        SolutionClicked = false;

        ClearStacks();
    }

    else if (PencilClicked == true)
    {
        bool p = (PencilMarks == false ? true:false);
        PencilMarks = p;

        PencilClicked = false;
    }

    else if (EraserClicked == true)
    {
        bool r = (EraserEnabled == false ? true:false);
        EraserEnabled = r;

        EraserClicked = false;
    }

    else if (KeyPressed == true)
    {
        if (DifficultyChosen == true)
            GetChosenNumber(key);

        else
        {
            switch(key)
            {
                default:
                SelectedLevel = 0;
                break;

                case SDLK_1:
                SelectedLevel = 1;
                break;

                case SDLK_2:
                SelectedLevel = 2;
                break;

                case SDLK_3:
                SelectedLevel = 3;
                break;
            }

            if ((SelectedLevel == 1) || (SelectedLevel == 2) || (SelectedLevel == 3))
                DifficultyChosen = true;

            else
                DifficultyChosen = false;
        }
    }
}

