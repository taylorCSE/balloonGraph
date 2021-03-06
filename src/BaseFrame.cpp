/**
 * \file BaseFrame.cpp
 * \brief Base frame Class
 */
 
#include "BaseFrame.h"

BEGIN_EVENT_TABLE(BaseFrame,wxFrame)
    EVT_MENU(ID_NEWSTATUS, BaseFrame::NewStatusWindow)
    EVT_MENU(ID_NEWGRAPH, BaseFrame::NewGraphWindow)
    EVT_MENU(ID_NEWSINGLEGRAPH, BaseFrame::NewSingleGraphWindow)
    EVT_MENU(ID_NEWSETTINGS, BaseFrame::NewSettingsWindow)
    EVT_MENU(ID_ABOUT, BaseFrame::NewAboutWindow)
    EVT_TIMER(UPDATE_TIMER, BaseFrame::OnTimer)
    EVT_MENU(-1, BaseFrame::OnMenu)
    EVT_CLOSE(BaseFrame::OnClose)
END_EVENT_TABLE()

/**
    Constructor
*/

BaseFrame::BaseFrame()
: wxFrame(NULL, -1, wxT("AppName"), wxDefaultPosition, wxSize(360,600), 
          wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | 
          wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX) {
    flightId = "";

    SetIcon(wxIcon(wxT("icon.xpm")));
    
    updateTimer = new wxTimer(this, UPDATE_TIMER);
    updateTimer->Start(5000);
    
    // Nullify the pointers
    menubar = 0x00;
    flight_menu = 0x00;
    view_menu = 0x00;
    window_menu = 0x00;

    view = VIEW_BASIC;
}

/**
    Deconstructor
*/

BaseFrame::~BaseFrame() {
}

/**
    Creates the default menus
    
    Options can be provided to disable specific menus.
*/

void BaseFrame::CreateMenu(bool show_view, 
                           bool show_window, 
                           bool show_flights,
                           bool show_help,
                           bool show_data) {
    wxMenuBar* old_menubar = menubar;
    
    menubar = new wxMenuBar;
    
    if(show_flights) {
        flight_menu = new wxMenu;
        flightIds = DB_getAllFlights();
        
        menubar->Append(flight_menu, wxT("&Flights"));
    
        for(unsigned int i = 0; i < flightIds.size(); i++) {
            flight_menu->Append(10000+i, flightIds[i]);
        }
    }
    
    if(show_view) {
        view_menu = new wxMenu;
        menubar->Append(view_menu, wxT("&View"));
        
        view_menu->Append(VIEW_BASIC, wxT("Basic"));
        view_menu->Append(VIEW_ANALOG, wxT("Analog Channels"));
    }

    if(show_window) {
        window_menu = new wxMenu;
        menubar->Append(window_menu, wxT("&Window"));
        
        window_menu->Append(ID_NEWSTATUS, "New Status Window");
        window_menu->Append(ID_NEWGRAPH, "New Graph Window");    
        window_menu->Append(ID_NEWSINGLEGRAPH, "New Single Graph Window");    
        window_menu->Append(ID_NEWSETTINGS, wxT("Settings"));
    }
    
    if(show_data) {
        data_menu = new wxMenu;
        menubar->Append(data_menu, wxT("&Data"));
        
        data_menu->Append(ID_VSALTITUDE, "vs Altitude");
        data_menu->Append(ID_VSTIME, "vs Time");

        data_menu->Append(ID_ALTITUDE, "Altitude");
        data_menu->Append(ID_SPEED, "Speed");
        data_menu->Append(ID_BEARING, "Bearing");
        data_menu->Append(ID_CLIMB, "Climb");
        for(int i = 1; i <= 18; i++) {
            data_menu->Append(9000+i, wxString::Format(wxT("A%d"),i));
        }
    }

    if(show_help) {
        help_menu = new wxMenu;
        menubar->Append(help_menu, wxT("&Help"));
        
        help_menu->Append(ID_ABOUT, "About");
    }
    
    SetMenuBar(menubar);

    if(old_menubar) delete old_menubar;

    CreateStatusBar(2);
    SetStatusText(wxString(DB_STATUS), 0);
    SetStatusText(wxString("Version:")+wxString(VERSION), 1);
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
    Launches a new single graph window
*/
     
void BaseFrame::NewSingleGraphWindow( wxCommandEvent& event ) {
    wxFrame* frame = NewSingleGraphFrame();
    frame->Show();     
}

/** 
    Launches a new settings window
*/
     
void BaseFrame::NewSettingsWindow( wxCommandEvent& event ) {
    wxFrame* frame = NewSettingsFrame();
    frame->Show();     
}

/** 
    Launches a new about window
*/
     
void BaseFrame::NewAboutWindow( wxCommandEvent& event ) {
    wxFrame* frame = NewAboutFrame();
    frame->Show();     
}

/**
    Handles new flight selection event
*/

void BaseFrame::OnMenu( wxCommandEvent& event ) {
    int id = event.GetId();
    
    if(id >= 10000) {
        /// We're selecting a device
        flightId = flightIds[id - 10000];
    }

    if(id >= VIEW_BASIC && id <= VIEW_BEACON) {
        view = id;
    }
    
    Update();
}

/**
    Handles timer firing
*/

void BaseFrame::OnTimer(wxTimerEvent& event) {
    Update();
}


/**
   Exit the Program
*/

void BaseFrame::OnClose(wxCloseEvent& event) {
    if(updateTimer) {
        delete updateTimer;
        updateTimer = 0x00;
    }
    Destroy();
}
