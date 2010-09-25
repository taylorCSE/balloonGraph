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
    
    wxTextCtrl* db_host = new wxTextCtrl(mainPanel,-1,DB_HOST);
    wxTextCtrl* db_name = new wxTextCtrl(mainPanel,-1,DB_NAME);
    wxTextCtrl* db_user = new wxTextCtrl(mainPanel,-1,DB_USER);
    wxTextCtrl* db_pass = new wxTextCtrl(mainPanel,-1,DB_PASS);
    
    wxStaticText* db_host_label = new wxStaticText(mainPanel,-1,wxT("Database Hostname"));
    wxStaticText* db_name_label = new wxStaticText(mainPanel,-1,wxT("Database Name"));
    wxStaticText* db_user_label = new wxStaticText(mainPanel,-1,wxT("Database Username"));
    wxStaticText* db_pass_label = new wxStaticText(mainPanel,-1,wxT("Database Password"));
    
    mainSizer->Add(db_host_label, 0);
    mainSizer->Add(db_host,       0);
    mainSizer->Add(db_name_label, 0);
    mainSizer->Add(db_name,       0);
    mainSizer->Add(db_user_label, 0);
    mainSizer->Add(db_user,       0);
    mainSizer->Add(db_pass_label, 0);
    mainSizer->Add(db_pass,       0);

    Update();
}

void SettingsFrame::Update() {
}

wxFrame* NewSettingsFrame() {
    return (wxFrame*)(new SettingsFrame(NULL));
}

