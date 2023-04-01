/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#ifndef DIFFICULTY_H_INCLUDED
#define DIFFICULTY_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <string>

/**
This class contains functions that removes numbers from the grid after the solution has
been initialized. The amount of numbers removed depends on the selected level */

using namespace std;

class Difficulty
{
    private:
    int DetermineGivens();     // Determine amount of given cells based on chosen
                                 // difficulty level
    int DetermineLowerBound(); // As above

    public:
    Difficulty();

    int SelectedLevel;
    void DetermineDifficulty(int []);
};

#endif // DIFFICULTY_H_INCLUDED
