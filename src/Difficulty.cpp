/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Difficulty.h"

using namespace std;

Difficulty::Difficulty()
{
    SelectedLevel = 0;
}

void Difficulty::DetermineDifficulty(int GridElements[])
{

    int givens = DetermineGivens();
    int LowerBound = DetermineLowerBound();

    int NumberToRemove = (81 - givens) / 2;        // Number of givens to remove - givens
                                                    // are removed symmetrically
    int counter = 0;

    int rc = 0;
    int TotalRow = 0;
    int TotalCol = 0;
    int row = 0;
    int column = 0;
    bool RemoveOK = false;                       // Is the number ok to remove
    bool RemoveSuccess = false;                 // Has the number been successfully removed?

    while (counter <= NumberToRemove)
    {
        rc = rand() % 71 + 9;
        TotalRow = 0;
        TotalCol = 0;

        RemoveOK = false;
        RemoveSuccess = false;

        // Get row and column of cell
        row = (int) rc/9;
        column = rc % 9;

        for (int i = (9 * row); i < ((9 * row) + 8); ++i)
        {
            if (GridElements[i] != -1)
                TotalRow++;
        }

        for (int i = column; i < (column + (9 * row)); ++i)
        {
            if (GridElements[i] != -1)
                TotalCol++;
        }

        if ((TotalRow >= LowerBound) || (TotalCol >= LowerBound))
            RemoveOK = true;

        if ((RemoveOK == true) && (GridElements[rc] != -1) && (GridElements[rc-10] != -1))
        {
            GridElements[rc] = -1;
            GridElements[rc-10] = -1;

            RemoveSuccess = true;
        }

        else
            RemoveSuccess = false;

        if (RemoveSuccess == true)
            counter++;
    }
}


int Difficulty::DetermineGivens()
{
    int r = 0;      // Random Number that will determine amount of givens

    switch (SelectedLevel)
    {
        default: break;     // Ignore compiler warnings

        case 1:     // Easy

        r = rand() % 7 + 29;
        break;

        case 2:     // Medium

        r = rand() % 5 + 23;
        break;

        case 3:     // Difficult

        r = rand() % 4 + 18;
        break;
    }

    return r;
}

int Difficulty::DetermineLowerBound()
{
    int LowerBound = 0;

    switch (SelectedLevel)
    {
        default: break;

        case 1:
        LowerBound = 4;

        break;

        case 2:
        LowerBound = 2;

        break;

        case 3:
        LowerBound = 0;
    }

    return LowerBound;
}
