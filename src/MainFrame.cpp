/**
 * \file MainFrame.cpp
 * \brief Main Windows Class
 */
 
#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
    EVT_MENU(-1, MainFrame::SelectDevice)
    EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    /**
    *   Constructor for the Main frame.
    */
    deviceId = "Please select a device from the menu.";
    
    CreateGUIControls();
    
    //wxMessageBox(devices[0]);

    /*
    DB_query("select * from gps where DeviceId=5001 order by Timestamp desc limit 1;");
    
    wxMessageBox(DB_resultAsText());
    */
}

MainFrame::~MainFrame() {
    /** 
    *   Destructor for the Main form.
    */
}

void MainFrame::Update() {
    /**
     * Updates the GUI with new database information
     */
    wxMenuBar *menubar = new wxMenuBar;
    wxMenu *devices = new wxMenu;
    
    deviceIds = DB_getAllDevices();
    
    menubar->Append(devices, wxT("&Devices"));

    for(unsigned int i = 0; i < deviceIds.size(); i++) {
        devices->Append(10000+i, deviceIds[i]);
    }
    SetMenuBar(menubar);
    
    map<const char*, string> gps_info; 
    gps_info = DB_getMostRecentGPS(atoi(deviceId.c_str()));
    
    fprintf(DB_log,"\nAltitude:%s\n", gps_info["Altitude"].c_str());
    fprintf(DB_log,"\n1:%s\n", pair<const char*, string>(*gps_info.begin()).first);
    fprintf(DB_log,"\n2:%s\n", pair<const char*, string>(*gps_info.begin()).second.c_str());
    
    wxString info = wxString::Format(wxT(""
        "Device: %s\n"
        "Location\n"
        "Latitude: \n"
        "Longitude: \n"
        "Altitude (M): %s\n"
        "Altitude (Ft): \n"
        "Speed (Knots): \n"
        "Speed (M/S): \n"
        "Bearing: \n"
        "Climb: \n"
        "GPS Status: \n"
        "\n"
        "Status \n"
        "Battery 1 (V): \n"
        "Battery 2 (V): \n"
        "Buss (V): \n"
        "Signal (%%): \n"
        "Temperature Int. (c): \n"
        "Temperature Ext. (c): \n"
        "Pressure (HPA): \n"
        "RH (%%): \n"
        "\n"
        ),
        deviceId.c_str(),
        gps_info["Altitude"].c_str());
    
    deviceInfo->SetLabel(info);
}

void MainFrame::CreateGUIControls() {
   /**
    *   Creates all of the GUI controls on the main form.
    */
    
    // Set window properties and title bar
    SetTitle(wxT("HawkEye"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
    deviceInfo = new wxStaticText(mainPanel, wxID_ANY, deviceId);
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

void MainFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    exit(0);
}

void MainFrame::SelectDevice( wxCommandEvent& event ) {
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
