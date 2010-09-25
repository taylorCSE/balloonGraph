/**
 * \file SettingsFrame.cpp
 * \brief Main Settings Class
 */
 
#include "SettingsFrame.h"

BEGIN_EVENT_TABLE(SettingsFrame,BaseFrame)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

SettingsFrame::SettingsFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: BaseFrame(parent, id, title, position, size, style) {
    deviceId = "Please select a device from the menu.";
    
    CreateGUIControls();
    
    SetTransparent(225);
}

/** 
   Destructor for the Main form.
*/

SettingsFrame::~SettingsFrame() {
}

/**
   Creates all of the GUI controls on the main form.
*/
    
void SettingsFrame::CreateGUIControls() {

    
    // Set window properties and title bar
    SetTitle(wxT("Device Settings"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
    deviceInfo = new wxHtmlWindow(mainPanel);
    mainSizer->Add(deviceInfo, 1, wxEXPAND | wxALL);

    Update();

}

void SettingsFrame::Update() {
}

wxFrame* NewSettingsFrame() {
    return (wxFrame*)(new SettingsFrame(NULL));
}

