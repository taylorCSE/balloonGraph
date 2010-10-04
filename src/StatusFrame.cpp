/**
 * \file StatusFrame.cpp
 * \brief Main Windows Class
 */
 
#include "StatusFrame.h"

BEGIN_EVENT_TABLE(StatusFrame,BaseFrame)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

StatusFrame::StatusFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: BaseFrame(parent, id, title, position, size, style) {
    flightId = "Please select a device from the menu.";
    
    CreateGUIControls();
    
    SetTransparent(245);
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
    CreateMenu();

    map<string, string> gps_info; 
    wxString head,info,tail;
    
    head = wxString::Format(wxT(""
            "<body bgcolor=black text=white>"
            "<b>Flight: <font color=#33ff33>%s</font></b>\n"
            "<hr>\n"),flightId.c_str());

    tail = wxString::Format(wxT(""
            "</body>"));
    
    if(view == VIEW_BASIC) {    
        gps_info = DB_getMostRecentGPS(flightId);

        info = wxString::Format(wxT(""
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
            ),
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
    }
    if(view == VIEW_ANALOG) {
        info = wxString("<b>Analog Channels</b>\n<br />");

        for(int i = 1; i <= 18; i++) {
            info = info + wxString::Format(wxT(""
                "A%d: <font color=#33ff33>%s</font>\n<br />"
                ),i,"test");
        }
    }    
    deviceInfo->SetPage(head+info+tail);
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

wxFrame* NewStatusFrame() {
    return (wxFrame*)(new StatusFrame(NULL));
}

