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

StatusFrame::StatusFrame()
: BaseFrame() {
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
    Colors a string based on parameters
*/

string StatusFrame::ColorString(string input, string true_value) {
    string color = "#33ff33";
    
    if(true_value != "" && input != true_value) {
        color = "#ff3333";
    }
    
    string output = "<font color=" + color + ">" + input + "</font>";
    
    return output;
}

/**
    Updates the GUI with new database information
*/

void StatusFrame::Update() {
    CreateMenu();

    wxString head,info,tail;
    
    head = wxString::Format(wxT(""
            "<body bgcolor=black text=white>"
            "<b>Flight: <font color=#33ff33>%s</font></b>\n"
            "<hr>\n"),flightId.c_str());

    tail = wxString::Format(wxT(""
            "</body>"));
    
    if(view == VIEW_BASIC) {    
        map<string, string> gps_info = DB_getMostRecentGPS(flightId);

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
            ColorString(gps_info["Latitude"]).c_str(),
            ColorString(gps_info["Longitude"]).c_str(),
            ColorString(gps_info["Altitude_m"]).c_str(),
            ColorString(gps_info["Altitude_ft"]).c_str(),
            ColorString(gps_info["Spd_knots"]).c_str(),
            ColorString(gps_info["Spd_mps"]).c_str(),
            ColorString(gps_info["Hdg"]).c_str(),
            ColorString(gps_info["Rate_mps"]).c_str(),
            ColorString(gps_info["Status"],"1").c_str()
            );
    }
    if(view == VIEW_ANALOG) {
        vector<string> analog_data = DB_getMostRecentAnalog(flightId);
        
        info = wxString("<b>Analog Channels</b>\n<br />");

        if(analog_data.size() < 19) {
            info = info + wxString("Data not available.");
        } else {
            for(int i = 1; i <= 18; i++) {
                info = info + wxString::Format(wxT(""
                    "A%d: <font color=#33ff33>%s</font>\n<br />"
                    ),i,analog_data[i].c_str());
            }
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

/**
    Create a new status frame
*/

wxFrame* NewStatusFrame() {
    return (wxFrame*)(new StatusFrame());
}

