/**
 * \file BalloonGraph.cpp
 * \brief Main Application Code
 */

#include "BalloonGraph.h"
#include "StatusFrame.h"

IMPLEMENT_APP(BalloonGraph)

bool BalloonGraph::OnInit()
{
    /**
    *   Creates the main frame and shows it
    */
    StatusFrame* frame = new StatusFrame(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int BalloonGraph::OnExit()
{
    /**
    *   Closes the application
    */
    return 0;
}
