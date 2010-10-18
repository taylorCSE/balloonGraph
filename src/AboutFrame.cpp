/**
 * \file AboutFrame.cpp
 * \brief Main Windows Class
 */
 
#include "AboutFrame.h"

BEGIN_EVENT_TABLE(AboutFrame,wxFrame)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

AboutFrame::AboutFrame()
: wxFrame() {
    CreateGUIControls();
    
    SetTransparent(245);
}

/** 
   Destructor for the Main form.
*/

AboutFrame::~AboutFrame() {
}

/**
   Creates all of the GUI controls on the main form.
*/
    
void AboutFrame::CreateGUIControls() {

    
    // Set window properties and title bar
    SetTitle(wxT("Device About"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
    info = new wxHtmlWindow(mainPanel);
    mainSizer->Add(info, 1, wxEXPAND | wxALL);

    info->SetPage(wxString::Format(wxT(""
        "<b>BalloonGraph</b>\n<br />"
        )));

}

/**
    Create a new status frame
*/

wxFrame* NewAboutFrame() {
    return (wxFrame*)(new AboutFrame());
}

