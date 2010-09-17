/**
 * \file BaseFrame.cpp
 * \brief Base frame Class
 */
 
#include "BaseFrame.h"

BEGIN_EVENT_TABLE(BaseFrame,wxFrame)
    EVT_MENU(ID_NEWSTATUS, BaseFrame::NewStatusWindow)
    EVT_MENU(ID_NEWGRAPH, BaseFrame::NewGraphWindow)
END_EVENT_TABLE()

BaseFrame::BaseFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
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
    
    SetMenuBar(menubar);
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
