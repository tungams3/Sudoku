/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include <vector>
#include <algorithm>
#include <functional>

/**
This class generates a solution, which is then copied into the grid and subsequently removed based on
the chosen difficulty level.
*/

using namespace std;

class Solution
{
    private:
    vector<int> RandomNumbers;          // Vector containing random numbers 1-9
    vector<int> :: iterator it;         // Cycles through RandomNumbers vector

    void GenerateRandomNumbers();
    void ReplenishNumbers(int, int**);
    bool CheckForConflict(int, int, int**);
    bool CheckSolution();

    int row;
    int column;
    int StartRow;
    int GridId;
    int RowNumber;
    int CurrentCell;

    protected:
    void ClearElements();

    public:
    Solution();

    void InitializeSolution();
    int** SolutionElements;
};

#endif // SOLUTION_H_INCLUDED
