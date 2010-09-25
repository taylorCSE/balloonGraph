/**
 * \file SettingsFrame.cpp
 * \brief Main Settings Class
 */
 
#include "SettingsFrame.h"

BEGIN_EVENT_TABLE(SettingsFrame,BaseFrame)
    EVT_BUTTON(ID_OK,  SettingsFrame::OnOk)
    EVT_BUTTON(ID_CANCEL,  SettingsFrame::OnCancel)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

SettingsFrame::SettingsFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: BaseFrame(parent, id, title, position, size, style) {
    deviceId = "Please select a device from the menu.";
    
    CreateGUIControls();
    
    SetTransparent(245);
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
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    mainPanel->SetSizer(mainSizer);
    
    dbHost = new wxTextCtrl(mainPanel,-1,DB_HOST);
    dbName = new wxTextCtrl(mainPanel,-1,DB_NAME);
    dbUser = new wxTextCtrl(mainPanel,-1,DB_USER);
    dbPass = new wxTextCtrl(mainPanel,-1,DB_PASS);
    
    wxStaticText* db_host_label = new wxStaticText(mainPanel,-1,wxT("Database Hostname"));
    wxStaticText* db_name_label = new wxStaticText(mainPanel,-1,wxT("Database Name"));
    wxStaticText* db_user_label = new wxStaticText(mainPanel,-1,wxT("Database Username"));
    wxStaticText* db_pass_label = new wxStaticText(mainPanel,-1,wxT("Database Password"));
    
    wxButton* ok_button = new wxButton(mainPanel,ID_OK,wxT("Ok"));
    wxButton* cancel_button = new wxButton(mainPanel,ID_CANCEL,wxT("Cancel"));
    
    mainSizer->Add(db_host_label, 0);
    mainSizer->Add(dbHost,       0);
    mainSizer->Add(db_name_label, 0);
    mainSizer->Add(dbName,       0);
    mainSizer->Add(db_user_label, 0);
    mainSizer->Add(dbUser,       0);
    mainSizer->Add(db_pass_label, 0);
    mainSizer->Add(dbPass,       0);
    mainSizer->Add(buttonSizer,       0);
    buttonSizer->Add(ok_button,       0);
    buttonSizer->Add(cancel_button,       0);

    Update();
}

void SettingsFrame::Update() {
}

void SettingsFrame::OnOk( wxCommandEvent& event ) {
    DB_HOST = dbHost->GetValue();
    DB_NAME = dbName->GetValue();
    DB_USER = dbUser->GetValue();
    DB_PASS = dbPass->GetValue();

    DB_connect();

    wxCloseEvent close_event;
    OnClose(close_event);
}

void SettingsFrame::OnCancel( wxCommandEvent& event ) {
    wxCloseEvent close_event;
    OnClose(close_event);
}

wxFrame* NewSettingsFrame() {
    return (wxFrame*)(new SettingsFrame(NULL));
}

