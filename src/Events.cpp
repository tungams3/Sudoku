/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/
#include "Events.h"

Event::Event()      // Initialize variables
{
    Xc = 0;
    Yc = 0;
    drawn = 0;

    Running = true;
    MousePressed = false;
    KeyPressed = false;
    UndoClicked = false;
    RedoClicked = false;
    GridClicked = false;
    ResetClicked = false;
    SolutionClicked = false;
    PencilClicked = false;
    EraserClicked = false;
    EraserEnabled = false;
    PencilMarks = false;
    DifficultyChosen = false;
}

void Event::HandleEvents(SDL_Event* event)
{
    if (event->type == SDL_QUIT)
        Running = false;

    else if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        MousePressed = true;
        KeyPressed = false;

        HandleMouseClick();
    }

    else if (event->type == SDL_MOUSEBUTTONUP)
    {
        MousePressed = false;
        KeyPressed = false;

        HandleMouseClick();
    }

    else if (event->type == SDL_KEYDOWN)
    {
        KeyPressed = true;
        key = event->key.keysym.sym;
    }
}

void Event::HandleMouseClick()
{
    SDL_GetMouseState(&Xc, &Yc);        // Get coordinates of where user has clicked

    if ((Xc >= 53) && (Xc <= 647) && (Yc >= 53) && (Yc <= 647))
        GridClicked = true;

    if ((MousePressed == true) && (DifficultyChosen == true))
    {
        if ((Xc >= 660) && (Xc <= 750) && (Yc >= 55) && (Yc <= 145))
            UndoClicked = true;

        else if ((Xc >= 780) && (Xc <= 870) && (Yc >= 55) && (Yc <= 145))
            RedoClicked = true;

        else if ((Xc >= 660) && (Xc <= 860) && (Yc >= 190) && (Yc <= 280))
            ResetClicked = true;

        else if ((Xc >= 660) && (Xc <= 930) && (Yc >= 325) && (Yc <= 415))
            SolutionClicked = true;

        else if ((Xc >= 660) && (Xc <= 860) && (Yc >= 460) && (Yc <= 550))
            PencilClicked = true;

        else if ((Xc >= 660) && (Xc <= 860) && (Yc >= 575) && (Yc <= 640))
            EraserClicked = true;
    }
}
