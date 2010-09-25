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
    SetTitle(wxT("Settings"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
    dbHost = new wxTextCtrl(mainPanel,-1,DB_HOST);
    dbName = new wxTextCtrl(mainPanel,-1,DB_NAME);
    dbUser = new wxTextCtrl(mainPanel,-1,DB_USER);
    dbPass = new wxTextCtrl(mainPanel,-1,DB_PASS);
    
    wxStaticText* db_host_label = new wxStaticText(mainPanel,-1,wxT("Database Hostname"));
    wxStaticText* db_name_label = new wxStaticText(mainPanel,-1,wxT("Database Name"));
    wxStaticText* db_user_label = new wxStaticText(mainPanel,-1,wxT("Database Username"));
    wxStaticText* db_pass_label = new wxStaticText(mainPanel,-1,wxT("Database Password"));
    
    wxButton* ok_button = new wxButton(mainPanel,-1,wxT("Ok"));
    wxButton* cancel_button = new wxButton(mainPanel,-1,wxT("Cancel"));
    
    mainSizer->Add(db_host_label, 0);
    mainSizer->Add(dbHost,       0);
    mainSizer->Add(db_name_label, 0);
    mainSizer->Add(dbName,       0);
    mainSizer->Add(db_user_label, 0);
    mainSizer->Add(dbUser,       0);
    mainSizer->Add(db_pass_label, 0);
    mainSizer->Add(dbPass,       0);
    mainSizer->Add(ok_button,       0);
    mainSizer->Add(cancel_button,       0);

    Update();
}

void SettingsFrame::Update() {
}

wxFrame* NewSettingsFrame() {
    return (wxFrame*)(new SettingsFrame(NULL));
}

