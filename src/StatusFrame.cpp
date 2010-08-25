/**
 * \file StatusFrame.cpp
 * \brief Main Windows Class
 */
 
#include "StatusFrame.h"

BEGIN_EVENT_TABLE(StatusFrame,wxFrame)
    EVT_MENU(ID_NEWWINDOW, StatusFrame::NewStatusWindow)
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
    
    view->Append(ID_NEWWINDOW, "New Window");

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
        "Altitude (Ft): \n<br />"
        "Speed (Knots): %s\n<br />"
        "Speed (M/S): \n<br />"
        "Bearing: %s\n<br />"
        "Climb: \n<br />"
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
        gps_info["Altitude"].c_str(),
        gps_info["Spd"].c_str(),
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
    
    //wxComboBox *device_dropdown = new wxComboBox(panel, wxID_ANY, wxT("Device"), wxDefaultPosition, wxDefaultSize);
    //sizer->Add(device_dropdown, 1, wxEXPAND | wxALL);

    /*
	// Create a mpFXYVector layer
	mpFXYVector* vectorLayer = new mpFXYVector(_(""));
	// Create two vectors for x,y and fill them with data
	std::vector<double> vectorx, vectory;
	double xcoord;
	for (unsigned int p = 0; p < 100; p++) {
		xcoord = (double)(p*1000.0);
		vectorx.push_back(25-0.001*pow(xcoord/1000, 2));
		vectory.push_back(xcoord);
	}
	vectorLayer->SetData(vectorx, vectory);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    m_plot = new mpWindow( this, -1, wxPoint(0,0), wxSize(100,100), wxSUNKEN_BORDER );
    mpScaleX* xaxis = new mpScaleX(wxT("Temperature"), mpALIGN_BOTTOM, true, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Altitude"), mpALIGN_LEFT, true);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);
	xaxis->SetLabelFormat(wxT("%.2f"));
	yaxis->SetLabelFormat(wxT("%.1f"));
    m_plot->SetMargins(30, 30, 50, 100);
    m_plot->AddLayer(     xaxis );
    m_plot->AddLayer(     yaxis );
	m_plot->AddLayer(     vectorLayer );
    //m_plot->AddLayer(     new mpText(wxT("Altitude vs Temperature"), 10, 10) );
    mpInfoLegend* leg;
    m_plot->AddLayer( leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH)); //&hatch2));
    leg->SetVisible(true);
    
    m_plot->Fit();
    */
}

void StatusFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    Close();
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

