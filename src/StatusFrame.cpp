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

StatusFrame::StatusFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    /**
    *   Constructor for the Main frame.
    */
    deviceId = "Please select a device from the menu.";
    
    CreateGUIControls();
}

StatusFrame::~StatusFrame() {
    /** 
    *   Destructor for the Main form.
    */
}

void StatusFrame::Update() {
    /**
     * Updates the GUI with new database information
     */
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
        "<b>Device: %s</b>\n"
        "<hr>\n"
        "<b>Location</b>\n<br />"
        "Latitude: %s\n<br />"
        "Longitude: %s\n<br />"
        "Altitude (M): %s\n<br />"
        "Altitude (Ft): %s\n<br />"
        "Speed (Knots): %s\n<br />"
        "Speed (M/S): %s\n<br />"
        "Bearing: %s\n<br />"
        "Climb: %s\n<br />"
        "GPS Status: %s\n"
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
        ),
        deviceId.c_str(),
        gps_info["Latitude"].c_str(),
        gps_info["Longitude"].c_str(),
        gps_info["Altitude_m"].c_str(),
        gps_info["Altitude_ft"].c_str(),
        gps_info["Spd_knots"].c_str(),
        gps_info["Spd_mps"].c_str(),
        gps_info["Rate_mps"].c_str(),
        gps_info["Hdg"].c_str(),
        gps_info["Status"].c_str()
        );
    
    deviceInfo->SetPage(info);
}

void StatusFrame::CreateGUIControls() {
   /**
    *   Creates all of the GUI controls on the main form.
    */
    
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

void StatusFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    Destroy();
}

void StatusFrame::SelectDevice( wxCommandEvent& event ) {
    /** 
     * Selects a device from the menu
     *
     * This is a catchall menu event handler becasue I couldn't think 
     * of a better way to do this because the menu is dynamic
     */
     
    int id = event.GetId();
    
    if(id > 10000) {
        /// We're selecting a device
        deviceId = deviceIds[id - 10000];
    }
    
    Update();
}


void StatusFrame::NewStatusWindow( wxCommandEvent& event ) {
    /** 
     * Launches a new status window
     */
     
    StatusFrame* frame = new StatusFrame(NULL);
    frame->Show();     
}

void StatusFrame::NewGraphWindow( wxCommandEvent& event ) {
    /** 
     * Launches a new graph window
     */
     
    GraphFrame* frame = new GraphFrame(NULL);
    frame->Show();     
}
