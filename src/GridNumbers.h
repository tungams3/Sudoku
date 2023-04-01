/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#ifndef DRAWRANDOMNUMBERS_H_INCLUDED
#define DRAWRANDOMNUMBERS_H_INCLUDED


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <sstream>
#include <vector>

#include "Surface.h"

/**
This class contains functions that are needed for the grid. E.g finding which cell has been clicked,
drawing a selected number in the grid, control the memory stacks for undo and redo operations etc
*/

using namespace std;

class GridNumbers
{
    private:

    SDL_Surface* SetNumber;     // Number to draw into grid
    SDL_Surface* ChosenNumber;  // Number chosen by user

    int r;

    int GuessPosition;      // The next cell position to place a guess

    protected:
    int GridElements[81];       // Holds numbers currently in the grid

    vector<int> UndoElementStack;       // Contains cells containing a number that was drawn/erased by undo()
    vector<int> RedoNumberStack;        // Contains the numbers drawn/erased by the redo function
    vector<int> RedoElementStack;       // Contains the cells drawn/erased by the redo function

    vector<int> PencilUndoElementStack;     // Contains cells containing a guess drawn/erased
    vector<int> PencilUndoNumberStack;      // Contains guesses drawn/erased

    vector<int> PencilRedoElementStack;     // As above
    vector<int> PencilRedoNumberStack;

    vector<int> :: iterator GuessIt;            // Cycles through guesses placed in grid
    vector<int> :: iterator ElementIt;          // Cycles through grid cells containing

    vector<int> SolutionCells;      // Cells that can't be erased (part of solution)

    int GuessX, GuessY;
    int SelectedCell;       // Cell currently selected by user

    int e;          // Element in GridElements array
    int n;         // Number pressed by user
    int x, y;      // Coordinates of cell chosen by user

    int FindSelectedCell();
    void FindGuessPosition();
    int DrawChosenNumber(SDL_Surface*, TTF_Font*, SDL_Color);
    void DrawGridNumbers(SDL_Surface*, TTF_Font*, SDL_Color);
    void DrawGuesses(SDL_Surface*, TTF_Font*, SDL_Color);

    void GetChosenNumber(SDLKey);
    void ClearStacks();

    public:
    GridNumbers();
};

#endif // DRAWRANDOMNUMBERS_H_INCLUDED
