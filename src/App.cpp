/**
 * \file App.cpp
 * \brief Main Application Code
 */

#include "App.h"
#include "StatusFrame.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
    /**
    *   Creates the main frame and shows it
    */
    StatusFrame* frame = new StatusFrame(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int App::OnExit()
{
    /**
    *   Closes the application
    */
    return 0;
}
