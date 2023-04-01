/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/
#include "GridNumbers.h"

using namespace std;

GridNumbers::GridNumbers()
{
    SetNumber = NULL;
    ChosenNumber = NULL;

    x = 0;
    y = 0;
    n = 1;
    e = 0;
    r = 0;
    GuessPosition = 0;
    SelectedCell = 0;
}

void GridNumbers::DrawGridNumbers(SDL_Surface* grid, TTF_Font *font, SDL_Color colour)
{
    for(int i = 0; i <= 80; ++i)        // Cycle through 81 cells in the grid
    {
        if (GridElements[i] != -1)       // If cell hasn't yet been filled
        {
            if (SetNumber != NULL)      // Free memory and temporary initialize surface
            {
                SDL_FreeSurface(SetNumber);
                SetNumber = NULL;
            }

            // Get correct coordinates of the cell
            int x1 = 21 + ((i % 9) * 66);
            int y1 = ((i / 9) * 66);

            // Convert random number in the cell to string format
            stringstream RandomNumberStream;
            RandomNumberStream << GridElements[i];

            // Display random number
            SetNumber = TTF_RenderText_Solid(font, RandomNumberStream.str().c_str(), colour);
            Surface::DrawSurface(grid, SetNumber, x1, y1);
        }
    }

    return;
}

int GridNumbers::FindSelectedCell()
{
    // Coordinates of cursor
    int Xc = 0;
    int Yc = 0;

    // Coordinates rendered by DrawGridNumbers
    x = 0;
    y = 0;

    int i = 0;          // Loops through the cells
    int cell = 1;       // Keeps track of which cell we're at

    SDL_GetMouseState(&Xc, &Yc);

    // Cycle through the midpoints of the cells, by arithmetic series.
    // This process converts the cursor coordinates into the coordinates
    // used in the DrawGridNumbers function

    while (i < (86 + (8 * 66)))
    {
        i = 86 + ((cell - 1) * 66);

        if ((Xc - i) < 33) {
            x = i - 65;
            break;
        }

        cell++;
    }

    i = 0;
    cell = 1;

    while (i < (86 + (8 * 66)))
    {
        i = 86 + ((cell - 1) * 66);


        if ((Yc - i) < 33) {
            y = i - 86;
            break;
        }

        cell++;
    }

    // Now that we have the converted coordinates, we need to find which cell in
    // the range 1-80 in which the coordinates lie. So we rearrange the formulas
    // given in DrawGridNumbers for x and y in terms of e (or 'i' as DrawGridNumbers)

    int e1 = (9 * y) / 66.0;
    int e2 = ((x-21) * (1 % 9)) / 66.0;     // Using modular multiplicative inverse formula

    e = e1 + e2;        // Equivalent to 'i' given in DrawGridNumbers
    return e;
}

// Get the number that was pressed by user
void GridNumbers::GetChosenNumber(SDLKey key)
{
    switch (key)
    {
        default:
            n = 0;
            break;

        case SDLK_1:
            n = 1;
            break;

        case SDLK_2:
            n = 2;
            break;

        case SDLK_3:
            n = 3;
            break;

        case SDLK_4:
            n = 4;
            break;

        case SDLK_5:
            n = 5;
            break;

        case SDLK_6:
            n = 6;
            break;

        case SDLK_7:
            n = 7;
            break;

        case SDLK_8:
            n = 8;
            break;

        case SDLK_9:
            n = 9;
            break;
    }
}

void GridNumbers::FindGuessPosition()       // Find where to draw the chosen guess into cell
{
        // Reduce x and y coordinates to top corner of chosen cell
        x -= 14;
        y -= 8.5;

        x += ((n - 1) % 3) * 22;        // Where n = chosen guess value
        y += ((n - 1) / 3) * 22;

        y += 8;
}


int GridNumbers::DrawChosenNumber(SDL_Surface *Grid, TTF_Font* font, SDL_Color colour)
{
    if (GridElements[e] != -1)      // If cell has already been filled
        return 1;

    if (n == 0)     // If no number has been chosen
        return 1;

    // Free the memory from the previous number
    SDL_FreeSurface(ChosenNumber);
    ChosenNumber = NULL;

    // Perform same operation as DrawNumbers()

    std::stringstream NumberStream;
    NumberStream << n;

    ChosenNumber = TTF_RenderText_Solid(font, NumberStream.str().c_str(), colour);
    Surface::DrawSurface(Grid, ChosenNumber, x, y);

    return 0;
}

void GridNumbers::DrawGuesses(SDL_Surface *Grid, TTF_Font *PencilFont, SDL_Color PencilFontColour)
{
    for(GuessIt = PencilUndoNumberStack.begin(), ElementIt = PencilUndoElementStack.begin();
        ElementIt != PencilUndoElementStack.end(), GuessIt != PencilUndoNumberStack.end();
        ++ElementIt, ++GuessIt)
    {
        x = 21 + ((*ElementIt % 9) * 66);
        y = ((*ElementIt / 9) * 66);
        n = *GuessIt;

        FindGuessPosition();
        DrawChosenNumber(Grid, PencilFont, PencilFontColour);
    }

    return;
}

void GridNumbers::ClearStacks()     // Clear all undo/redo memory stacks
{
        UndoElementStack.clear();
        RedoNumberStack.clear();
        RedoElementStack.clear();

        PencilUndoElementStack.clear();
        PencilUndoNumberStack.clear();

        PencilRedoElementStack.clear();
        PencilRedoNumberStack.clear();

        return;
}
