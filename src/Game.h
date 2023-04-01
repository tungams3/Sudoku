/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Surface.h"
#include "Events.h"
#include "GridNumbers.h"
#include "Solution.h"
#include "Difficulty.h"

/**
This class inherits from all other classes and controls the main game loop
*/

class Game : public Event, public GridNumbers, public Solution,
                public Difficulty
{
    private:

    // Surfaces, fonts etc

    SDL_Surface* Window;
    SDL_Surface* DifficultyWindow;
    SDL_Surface* Star;
    SDL_Surface* Background;
    SDL_Surface* UndoButton;
    SDL_Surface* UndoGreyed;
    SDL_Surface* RedoGreyed;
    SDL_Surface* RedoButton;
    SDL_Surface* ResetButton;
    SDL_Surface* SolutionButton;
    SDL_Surface* PencilButton;
    SDL_Surface* EraserButton;
    SDL_Surface* Grid;
    SDL_Surface* Tick;

    TTF_Font* Font;
    TTF_Font* PencilFont;

    SDL_Color FontColour;
    SDL_Color PencilFontColour;

    SDL_Rect WindowRect;

    bool SolutionInitialized;
    bool ShowSolution;

    int NumberCount;        // Increased when a number is drawn and vice versa
    int GuessCount;         // As above for guesses

    void ReloadGrid();
    void HandleClickedEvents();

    // Drawing, erasing and undo functions
    void DrawNumber();
    void EraseNumber();
    void EraseGuess();
    void DrawGuess();
    void UndoGuess();
    void UndoNumber();
    void RedoGuess();
    void RedoNumber();

    void UndoRedoRender();      // Toggles greyed out and non-greyed out undo/redo buttons

    public:
    Game();

    int Execute();          // Controls game loop

    bool Init();
    void Logic();
    void Render();
    void Cleanup();
};



#endif // GAME_H_INCLUDED
