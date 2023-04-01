/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Game.h"
#include "GridNumbers.h"

/*
This file contains functions that control drawing and erasing of numbers and guesses
*/

/*
*While this function appears similar to DrawChosenNumber(), it draws in a chosen number using that function
*but then updates the grid with guesses etc
*/

void Game::DrawNumber()
{
    // Check if there are any guesses in this cell
    for (ElementIt = PencilUndoElementStack.begin(), GuessIt = PencilUndoNumberStack.begin();
        ElementIt != PencilUndoElementStack.end(), GuessIt != PencilUndoNumberStack.end();
        ++ElementIt, ++GuessIt)
    {
        if (*ElementIt == SelectedCell)
        {
            PencilUndoElementStack.erase(ElementIt);
            PencilUndoNumberStack.erase(GuessIt);

            ElementIt = PencilUndoElementStack.begin() - 1;
            GuessIt = PencilUndoNumberStack.begin() - 1;

            GuessCount--;
        }
    }

    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);

    GetChosenNumber(key);
    GridElements[e] = n;
    UndoElementStack.push_back(e);

    NumberCount++;

    return;
}

void Game::EraseNumber()
{
    // Check user hasn't selected a solution cell
    for (ElementIt = SolutionCells.begin(); ElementIt != SolutionCells.end(); ++ElementIt)
    {
        if (SelectedCell == *ElementIt)
        {
            GridClicked = false;
            return;
        }
    }

    GridElements[e] = -1;
    NumberCount--;

    // Draw in guesses
    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);
}

void Game::DrawGuess()
{
    if ((DrawChosenNumber(Grid, PencilFont, PencilFontColour)) != 1)
    {
        PencilUndoElementStack.push_back(e);
        PencilUndoNumberStack.push_back(n);

        GuessCount++;
    }
}

void Game::EraseGuess()
{
    for (GuessIt = PencilUndoNumberStack.begin(), ElementIt = PencilUndoElementStack.begin();
        ElementIt != PencilUndoElementStack.end(), GuessIt != PencilUndoNumberStack.end(); ++GuessIt, ++ElementIt)
    {
        if ((*GuessIt == n) && (*ElementIt == SelectedCell))
        {
            PencilUndoNumberStack.erase(GuessIt);
            PencilUndoElementStack.erase(ElementIt);

            break;
        }
    }

    // Draw in guesses
    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);

    GuessCount--;
}

void Game::UndoNumber()
{
    if ((NumberCount == 0) || (EraserEnabled == true))
    {
        UndoClicked = false;
        return;
    }

    int ElementToRemove = UndoElementStack.back();
    UndoElementStack.pop_back();

    RedoElementStack.push_back(ElementToRemove);
    RedoNumberStack.push_back(GridElements[ElementToRemove]);

    GridElements[ElementToRemove] = -1;
    NumberCount--;

    // Draw in guesses
    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);
}

void Game::RedoNumber()
{
    if (((RedoElementStack.size()) == 0) || ((RedoNumberStack.size()) == 0)
         || (EraserEnabled == true))
    {
        RedoClicked = false;
        return;
    }

    int ElementToShow = RedoElementStack.back();
    int NumberToShow = RedoNumberStack.back();

    UndoElementStack.push_back(ElementToShow);

    RedoElementStack.pop_back();
    RedoNumberStack.pop_back();

    GridElements[ElementToShow] = NumberToShow;
    NumberCount++;

    // Draw in guesses
    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);
}


void Game::UndoGuess()
{
    if ((GuessCount == 0) || (EraserEnabled == true))
    {
        UndoClicked = false;
        return;
    }

    int cell = PencilUndoElementStack.back();
    int number = PencilUndoNumberStack.back();

    PencilRedoElementStack.push_back(cell);
    PencilRedoNumberStack.push_back(number);

    PencilUndoElementStack.pop_back();
    PencilUndoNumberStack.pop_back();

    // Draw in guesses
    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);

    GuessCount--;
}

void Game::RedoGuess()
{
    if (((PencilRedoElementStack.size()) == 0) || ((PencilRedoNumberStack.size()) == 0)
        || (EraserEnabled == true))
    {
        RedoClicked = false;
        return;
    }

    int cell = PencilRedoElementStack.back();
    int number = PencilRedoNumberStack.back();

    PencilUndoElementStack.push_back(cell);
    PencilUndoNumberStack.push_back(number);

    PencilRedoElementStack.pop_back();
    PencilRedoNumberStack.pop_back();

    ReloadGrid();
    DrawGuesses(Grid, PencilFont, PencilFontColour);

    GuessCount++;
}


void Game::UndoRedoRender()
{
    if (PencilMarks == true)
    {
        Surface::DrawSurface(Window, Tick, 880, 505);

        if (GuessCount == 0)
        {
            if (UndoButton != NULL)
            {
                SDL_FreeSurface(UndoButton);
                UndoButton = NULL;
            }

            if (UndoGreyed == NULL)
                UndoGreyed = Surface::LoadPNG((char*) "./gfx/UndoGreyed.png");

            Surface::DrawSurface(Window, UndoGreyed, 660, 55);
        }

        else
        {
            if (UndoGreyed != NULL)
            {
                SDL_FreeSurface(UndoGreyed);
                UndoGreyed = NULL;
            }

            if (UndoButton == NULL)
                UndoButton = Surface::LoadPNG((char*) "./gfx/Undo.png");

            Surface::DrawSurface(Window, UndoButton, 660, 55);
        }

        if (((PencilRedoElementStack.size()) == 0) || ((PencilRedoNumberStack.size()) == 0))
        {
            if (RedoButton != NULL)
            {
                SDL_FreeSurface(RedoButton);
                RedoButton = NULL;
            }

            if (RedoGreyed == NULL)
                RedoGreyed = Surface::LoadPNG((char*) "./gfx/RedoGreyed.png");

            Surface::DrawSurface(Window, RedoGreyed, 780, 55);
        }

        else
        {
            if (RedoGreyed != NULL)
            {
                RedoGreyed = NULL;
                SDL_FreeSurface(RedoGreyed);
            }

            if (RedoButton == NULL)
                RedoButton = Surface::LoadPNG((char*) "./gfx/Redo.png");

            Surface::DrawSurface(Window, RedoButton, 780, 55);
        }
    }

    else
    {
        if (NumberCount == 0)
        {
            if (UndoButton != NULL)
            {
                SDL_FreeSurface(UndoButton);
                UndoButton = NULL;
            }

            if (UndoGreyed == NULL)
                UndoGreyed = Surface::LoadPNG((char*) "./gfx/UndoGreyed.png");

            Surface::DrawSurface(Window, UndoGreyed, 660, 55);
        }

        else
        {
            if (UndoGreyed != NULL)
            {
                SDL_FreeSurface(UndoGreyed);
                UndoGreyed = NULL;
            }

            if (UndoButton == NULL)
                UndoButton = Surface::LoadPNG((char*) "./gfx/Undo.png");

            Surface::DrawSurface(Window, UndoButton, 660, 55);
        }

        if (((RedoElementStack.size()) == 0) || ((RedoNumberStack.size()) == 0))
        {
            if (RedoButton != NULL)
            {
                SDL_FreeSurface(RedoButton);
                RedoButton = NULL;
            }

            if (RedoGreyed == NULL)
                RedoGreyed = Surface::LoadPNG((char*) "./gfx/RedoGreyed.png");

            Surface::DrawSurface(Window, RedoGreyed, 780, 55);
        }

        else
        {
            if (RedoGreyed != NULL)
            {
                SDL_FreeSurface(RedoGreyed);
                RedoGreyed = NULL;
            }

            if (RedoButton == NULL)
                RedoButton = Surface::LoadPNG((char*) "./gfx/Redo.png");

            Surface::DrawSurface(Window, RedoButton, 780, 55);
        }
    }
}
