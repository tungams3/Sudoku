/**Copyright (C) 2013 Scott McGregor

You may use, distribute or modify all of the code in this zipfile under the terms of the
GNU General Public License as published by the Free Software Foundation.
**/

#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include <SDL/SDL.h>

/**
This class holds details of all possible events and determines what has been clicked
on the screen */

class Event
{
    private:
    int Xc, Yc;

    protected:
    bool Running;
    bool MousePressed;
    bool KeyPressed;
    bool GridClicked;
    bool UndoClicked;
    bool RedoClicked;
    bool ResetClicked;
    bool SolutionClicked;
    bool PencilClicked;
    bool EraserClicked;
    bool EraserEnabled;
    bool PencilMarks;
    bool DifficultyChosen;

    int drawn;      // Numbers that have been drawn into grid according to difficulty

    SDLKey key;

    void HandleMouseClick();

    public:
    Event();

    void HandleEvents(SDL_Event*);
};

#endif // EVENTS_H_INCLUDED
