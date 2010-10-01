/**
 * \file BaseFrame.cpp
 * \brief Base frame Class
 */
 
#include "BaseFrame.h"

BEGIN_EVENT_TABLE(BaseFrame,wxFrame)
    EVT_MENU(ID_NEWSTATUS, BaseFrame::NewStatusWindow)
    EVT_MENU(ID_NEWGRAPH, BaseFrame::NewGraphWindow)
    EVT_MENU(ID_NEWSETTINGS, BaseFrame::NewSettingsWindow)
    EVT_TIMER(UPDATE_TIMER, BaseFrame::OnTimer)
    EVT_MENU(-1, BaseFrame::SelectDevice)
    EVT_CLOSE(BaseFrame::OnClose)
END_EVENT_TABLE()

BaseFrame::BaseFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    updateTimer = new wxTimer(this, UPDATE_TIMER);
    updateTimer->Start(5000);

    view = VIEW_BASIC;
}

BaseFrame::~BaseFrame() {
}

void BaseFrame::CreateMenu() {
    menubar = new wxMenuBar;
    wxMenu *devices_menu = new wxMenu;
    wxMenu *view_menu = new wxMenu;
    wxMenu *window_menu = new wxMenu;
    
    deviceIds = DB_getAllDevices();
    
    menubar->Append(devices_menu, wxT("&Devices"));

    for(unsigned int i = 0; i < deviceIds.size(); i++) {
        devices_menu->Append(10000+i, deviceIds[i]);
    }

    menubar->Append(view_menu, wxT("&View"));
    
    view_menu->Append(VIEW_BASIC, wxT("Basic"));
    view_menu->Append(VIEW_ANALOG, wxT("Analog Channels"));

    menubar->Append(window_menu, wxT("&Window"));
    
    window_menu->Append(ID_NEWSTATUS, "New Status Window");
    window_menu->Append(ID_NEWGRAPH, "New Graph Window");    
    window_menu->Append(ID_NEWSETTINGS, wxT("Settings"));
    
    SetMenuBar(menubar);
    
    CreateStatusBar(2);
    SetStatusText(wxString("Commit:")+wxString(VERSION_COMMIT), 0);
    SetStatusText(wxString("Build:")+wxString(VERSION_BUILD), 1);
}


/** 
    Launches a new status window
*/

void BaseFrame::NewStatusWindow( wxCommandEvent& event ) {
    wxFrame* frame = NewStatusFrame();
    frame->Show();
}

/** 
    Launches a new graph window
*/
     
void BaseFrame::NewGraphWindow( wxCommandEvent& event ) {
    wxFrame* frame = NewGraphFrame();
    frame->Show();     
}

/** 
    Launches a new settings window
*/
     
void BaseFrame::NewSettingsWindow( wxCommandEvent& event ) {
    wxFrame* frame = NewSettingsFrame();
    frame->Show();     
}

void BaseFrame::SelectDevice( wxCommandEvent& event ) {
    int id = event.GetId();
    
    if(id > 10000) {
        /// We're selecting a device
        deviceId = deviceIds[id - 10000];
    }

    if(id == VIEW_BASIC) {
        view = VIEW_BASIC;
    }
    if(id == VIEW_ANALOG) {
        view = VIEW_ANALOG;
    }
    
    Update();
}

void BaseFrame::OnTimer(wxTimerEvent& event) {
    Update();
}


void BaseFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    Destroy();
}
