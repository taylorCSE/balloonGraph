/**
 * \file StatusFrame.cpp
 * \brief Main Windows Class
 */
 
#include "StatusFrame.h"

BEGIN_EVENT_TABLE(StatusFrame,wxFrame)
    EVT_MENU(ID_NEWSTATUS, StatusFrame::NewStatusWindow)
    EVT_MENU(ID_NEWGRAPH, StatusFrame::NewGraphWindow)
    EVT_MENU(-1, StatusFrame::SelectDevice)
    EVT_CLOSE(StatusFrame::OnClose)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

StatusFrame::StatusFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: BaseFrame(parent, id, title, position, size, style) {
    deviceId = "Please select a device from the menu.";
    
    CreateGUIControls();
    
    SetTransparent(225);
}

/** 
   Destructor for the Main form.
*/

StatusFrame::~StatusFrame() {
}

/**
    Updates the GUI with new database information
*/

void StatusFrame::Update() {
    wxMenuBar *menubar = new wxMenuBar;
    wxMenu *devices = new wxMenu;
    wxMenu *view = new wxMenu;
    
    deviceIds = DB_getAllDevices();
    
    menubar->Append(devices, wxT("&Devices"));

    for(unsigned int i = 0; i < deviceIds.size(); i++) {
        devices->Append(10000+i, deviceIds[i]);
    }

    menubar->Append(view, wxT("&View"));
    
    view->Append(ID_NEWSTATUS, "New Status Window");
    view->Append(ID_NEWGRAPH, "New Graph Window");

    SetMenuBar(menubar);
    
    map<string, string> gps_info; 
    gps_info = DB_getMostRecentGPS(atoi(deviceId.c_str()));
    
    wxString info = wxString::Format(wxT(""
        "<body bgcolor=black text=white>"
        "<b>Device: <font color=#33ff33>%s</font></b>\n"
        "<hr>\n"
        "<b>Location</b>\n<br />"
        "Latitude: <font color=#33ff33>%s</font>\n<br />"
        "Longitude: <font color=#33ff33>%s</font>\n<br />"
        "Altitude (M): <font color=#33ff33>%s</font>\n<br />"
        "Altitude (Ft): <font color=#33ff33>%s</font>\n<br />"
        "Speed (Knots): <font color=#33ff33>%s</font>\n<br />"
        "Speed (M/S): <font color=#33ff33>%s</font>\n<br />"
        "Bearing: <font color=#33ff33>%s</font>\n<br />"
        "Climb: <font color=#33ff33>%s</font>\n<br />"
        "GPS Status: <font color=#33ff33>%s</font>\n"
        "\n<hr>"
        "<b>Status</b>\n<br />"
        "Battery 1 (V): \n<br />"
        "Battery 2 (V): \n<br />"
        "Buss (V): \n<br />"
        "Signal (%%): \n<br />"
        "Temperature Int. (c): \n<br />"
        "Temperature Ext. (c): \n<br />"
        "Pressure (HPA): \n<br />"
        "RH (%%): \n"
        "</body>"
        ),
        deviceId.c_str(),
        gps_info["Latitude"].c_str(),
        gps_info["Longitude"].c_str(),
        gps_info["Altitude_m"].c_str(),
        gps_info["Altitude_ft"].c_str(),
        gps_info["Spd_knots"].c_str(),
        gps_info["Spd_mps"].c_str(),
        gps_info["Hdg"].c_str(),
        gps_info["Rate_mps"].c_str(),
        gps_info["Status"].c_str()
        );
    
    deviceInfo->SetPage(info);
}

/**
   Creates all of the GUI controls on the main form.
*/
    
void StatusFrame::CreateGUIControls() {

    
    // Set window properties and title bar
    SetTitle(wxT("Device Status"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
    deviceInfo = new wxHtmlWindow(mainPanel);
    mainSizer->Add(deviceInfo, 1, wxEXPAND | wxALL);

    Update();

}

/**
    Event handler for the form closing event
    Exit the ChaosConnect Program
*/

void StatusFrame::OnClose(wxCloseEvent& event) {
    Destroy();
}

/** 
    Selects a device from the menu
    
    This is a catchall menu event handler becasue I couldn't think 
    of a better way to do this because the menu is dynamic
*/
     
void StatusFrame::SelectDevice( wxCommandEvent& event ) {

     
    int id = event.GetId();
    
    if(id > 10000) {
        /// We're selecting a device
        deviceId = deviceIds[id - 10000];
    }
    
    Update();
}

/** 
    Launches a new status window
*/
     
void StatusFrame::NewStatusWindow( wxCommandEvent& event ) {

     
    StatusFrame* frame = new StatusFrame(NULL);
    frame->Show();     
}

/** 
    Launches a new graph window
*/
     
void StatusFrame::NewGraphWindow( wxCommandEvent& event ) {

     
    GraphFrame* frame = new GraphFrame(NULL);
    frame->Show();     
}
