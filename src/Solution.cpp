/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#include "Solution.h"

using namespace std;

ptrdiff_t random (ptrdiff_t i) {
    return rand() % i;
}

ptrdiff_t (*p_random)(ptrdiff_t) = random;      // Pointer object to random number function

int Differences[] = {0, 1, 2, 9, 10, 11, 18, 19, 20};       // Possible differences in cell numbers in a subgrid
int GridIds[] = {0, 3, 6, 27, 30, 33, 54, 57, 60};          // Top left cell in each subgrid

/* This algorithm works by filling in each cell as it loops through the grid. Before
* filling a cell, it checks whether the numbers within its row and column are the same
* as the proposed number, and if it is it tries another. If it gets to the end of the list,
* then no number is suitable so it backtracks to the previous cells and checks whether it
* can swap the numbers.
*/

Solution::Solution()
{
    row = 0;
    column = 0;
    StartRow = 0;
    GridId = 0;
    CurrentCell = 0;
}

void Solution::InitializeSolution()
{
    bool CellFilled = false;

    row = 0;
    column = 0;
    StartRow = 0;
    GridId = 0;
    CurrentCell = 0;

    SolutionElements = new int* [80];       // Create array for solution data
    for(int i = 0; i <= 80; ++i)
        SolutionElements[i] = new int[10];

    for (int i = 0; i <= 80; ++i)
    {
        SolutionElements[i][0] = -1;        // The official number

        // The following values change to -1 if the corresponding number cannot be placed in the cell
        SolutionElements[i][1] = 1;
        SolutionElements[i][2] = 2;
        SolutionElements[i][3] = 3;
        SolutionElements[i][4] = 4;
        SolutionElements[i][5] = 5;
        SolutionElements[i][6] = 6;
        SolutionElements[i][7] = 7;
        SolutionElements[i][8] = 8;
        SolutionElements[i][9] = 9;
    }

    for (int i = 0; i <= 80; ++i)
    {
        if (RandomNumbers.size() != 0)
            RandomNumbers.clear();

        for (int j = 1; j <= 9; ++j)
        {
            if (SolutionElements[i][j] != -1)
                RandomNumbers.push_back(SolutionElements[i][j]);
        }


        if (RandomNumbers.size() != 0)
        {
            GenerateRandomNumbers();

            for (it = RandomNumbers.begin(); it != RandomNumbers.end(); ++it)
            {
                if ((CheckForConflict(*it, i, SolutionElements)) == true)
                    SolutionElements[i][*it] = -1;

                else
                {
                    SolutionElements[i][0] = *it;
                    CellFilled = true;

                    break;
                }
            }

            if (CellFilled != true)
            {
                ReplenishNumbers(i, SolutionElements);
                i -= 2;
            }

            else
                CellFilled = false;
        }

        else {
            ReplenishNumbers(i, SolutionElements);
            i -= 2;
        }
    }
}

void Solution::ReplenishNumbers(int cell, int **SolutionElements)
{
    for (int i = 0; i <= 9; ++i)
    {
        SolutionElements[cell][0] = -1;
        SolutionElements[cell][1] = 1;
        SolutionElements[cell][2] = 2;
        SolutionElements[cell][3] = 3;
        SolutionElements[cell][4] = 4;
        SolutionElements[cell][5] = 5;
        SolutionElements[cell][6] = 6;
        SolutionElements[cell][7] = 7;
        SolutionElements[cell][8] = 8;
        SolutionElements[cell][9] = 9;
    }
}

void Solution::GenerateRandomNumbers()
{
    if (RandomNumbers.size() != 0)
        RandomNumbers.clear();

    for (int i = 1; i <= 9; ++i)
        RandomNumbers.push_back(i);

    random_shuffle(RandomNumbers.begin(), RandomNumbers.end());
    random_shuffle(RandomNumbers.begin(), RandomNumbers.end(), p_random);
}

// Check if there would be a conflict if the number was placed in this cell
bool Solution::CheckForConflict(int number, int cell, int **SolutionElements)
{
    StartRow = 0;
    GridId = 0;

    row = (int) (cell/9);
    column = cell % 9;

    StartRow = (9 * row);

    for (int i = StartRow; i < StartRow + 8; ++i)       // If any number in the row equals the number proposed
    {
        if (SolutionElements[i][0] == number)
            return true;
    }

    for (int i = column; i < column + StartRow; i += 9)     // If any number in the column equals the number proposed
    {
        if (SolutionElements[i][0] == number)
            return true;
    }

    // Now find the grid in which this number lies

    for (int i = 0; i <= 8; ++i)
    {
        for (int j = 0; j <= 8; ++j)
        {
            if ((cell - Differences[j]) == GridIds[i])
            {
                GridId = GridIds[i];

                break;
            }
        }

        if (GridId != 0)
            break;
    }

    int i = GridId;

    // Now check if any number in the grid equals the proposed number
    while (i <= (GridId + 20))
    {
        if (SolutionElements[i][0] == number)
            return true;

        if (i == (GridId + 2))
            i = GridId + 8;

        else if (i == (GridId + 11))
            i = GridId + 17;

        i++;
    }

    return false;       // If we've gotten this far, the number doesn't conflict
}


bool Solution::CheckSolution()
{
    int i = 0;
    int row = 0;
    int column = 0;
    int RunningTotal = 0;
    int GridId = 0;

    while (i <= 80)
    {
        RunningTotal += SolutionElements[i][0];

        if (i == ((row * 9) + 8))
        {
            if (RunningTotal != 45)
                return false;

            else {
                row++;
                RunningTotal = 0;
            }
        }

        i++;
    }

    i = 0;
    row = 0;
    RunningTotal = 0;

    while (i <= 80)
    {
        RunningTotal += SolutionElements[i][0];

        if (row == 8)
        {
            if (RunningTotal != 45)
                return false;

            else {
                row = -1;
                column++;

                i = column;
                RunningTotal = 0;
            }
        }

        i += 9;
        row++;
    }

    i = 0;
    RunningTotal = 0;

    while (i <= 80)
    {
        RunningTotal += SolutionElements[i][0];

        if ((i == (GridId + 2)) || (i == (GridId + 11)))
            i += 6;

        else if (i == (GridId + 20))
        {
            if (RunningTotal != 45)
                return false;

            else {
                if ((GridId == 6) || (GridId == 33))
                    GridId += 21;

                else
                    GridId += 3;

                RunningTotal = 0;

                i = GridId - 1;
            }
        }

        i++;
    }

    return true;
}

void Solution::ClearElements()
{
    for (int i = 0; i <= 80; ++i)
        delete [] SolutionElements[i];

    delete [] SolutionElements;
}
