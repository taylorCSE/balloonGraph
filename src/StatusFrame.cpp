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
    view_menu->Append(VIEW_VALVE, wxT("Valve"));
    view_menu->Append(VIEW_REEL_DOWN, wxT("Reel Down"));
    view_menu->Append(VIEW_AIR_SAMPLE, wxT("Air Sampler"));
    view_menu->Append(VIEW_MET_AIRBORNE, wxT("MET Airborne"));
    view_menu->Append(VIEW_MET_GROUND, wxT("MET Ground"));
    view_menu->Append(VIEW_BEACON, wxT("BEACON"));
    
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

    if(view == VIEW_VALVE) {
        vector<string> analog_data = DB_getMostRecentAnalog(flightId);

        if(analog_data.size() < 19) {
            info = info + wxString("Data not available.");
        } else {
            info = wxString::Format(wxT(""
                "<b>Valve Status</b>\n<br />"
                "Battery Voltage: %s\n<br />"
                "Current Altitude (M): %s\n<br />"
                "Current Rate (M/M): %s\n<br />"
                "GPS Status: %s\n<br />"
                "Valve Status: %s\n<br />"
                "Cut Down Status: %s\n<br />"
                "Abort Count Down (M): %s\n<br />"
                "Target Altitude (M): %s\n<br />"
                "Target Abort Time (M): %s\n<br />"
                "Evelope Air Temp. C: %s\n<br />"
                "Evelope Surface Temp. C: %s\n<br />"
                "Evelope Diff. Presure HPA: %s\n<br />"
                "Gas Flow  (M/S): %s\n<br />"
                ),
                ColorString(DB_asVoltage(analog_data[1])).c_str(),
                ColorString(analog_data[2]).c_str(),
                ColorString(DB_asRate(analog_data[3])).c_str(),
                ColorString(DB_asGPSStatus(analog_data[4])).c_str(),
                ColorString(DB_asValveStatus(analog_data[5])).c_str(),
                ColorString(DB_asCutDownStatus(analog_data[6])).c_str(),
                ColorString(analog_data[7]).c_str(),
                ColorString(analog_data[8]).c_str(),
                ColorString(analog_data[9]).c_str(),
                ColorString(DB_asAirTemp(analog_data[10])).c_str(),
                ColorString(DB_asSurfaceTemp(analog_data[11])).c_str(),
                ColorString(analog_data[12]).c_str(),
                ColorString(analog_data[13]).c_str()
                );
        }
    }
        
    if(view == VIEW_REEL_DOWN) {
        vector<string> analog_data = DB_getMostRecentAnalog(flightId);

        if(analog_data.size() < 19) {
            info = info + wxString("Data not available.");
        } else {
            info = wxString::Format(wxT(""
                "<b>Reel Down Status</b>\n<br />"
                "Battery Voltage: %s\n<br />"
                "GPS Status: %s\n<br />"
                "Current Altitude (M): %s\n<br />"
                "Line Deploy (M): %s\n<br />"
                "Deploy Time (M): %s\n<br />"
                "Reeling: %s\n<br />"
                "Target Reel Down Altitude (M): %s\n<br />"
                "Target Reel Up Altitude (M): %s\n<br />"
                "Target Down Time (M): %s\n<br />"
                ),
                ColorString(DB_asVoltage(analog_data[1])).c_str(),
                ColorString(DB_asGPSStatus(analog_data[2])).c_str(),
                ColorString(analog_data[3]).c_str(),
                ColorString(analog_data[4]).c_str(),
                ColorString(analog_data[5]).c_str(),
                ColorString(DB_asReeling(analog_data[6])).c_str(),
                ColorString(analog_data[7]).c_str(),
                ColorString(analog_data[8]).c_str(),
                ColorString(analog_data[9]).c_str()
                );
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

