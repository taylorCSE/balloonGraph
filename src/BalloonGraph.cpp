/**
 * \file BalloonGraph.cpp
 * \brief Main Application Code
 *
 * This is the entry point for the application.
 */

#include "BalloonGraph.h"
#include "StatusFrame.h"

IMPLEMENT_APP(BalloonGraph)

/**
    Creates the main frame and shows it
*/

bool BalloonGraph::OnInit() {
    StatusFrame* frame = new StatusFrame();
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
/**
   Closes the application
*/

int BalloonGraph::OnExit() {
    return 0;
}
