/**
 * \file GraphFrame.cpp
 * \brief Main Windows Class
 */
 
#include "GraphFrame.h"

BEGIN_EVENT_TABLE(GraphFrame,wxFrame)
    EVT_MENU(ID_NEWWINDOW, GraphFrame::NewStatusWindow)
    EVT_MENU(-1, GraphFrame::SelectDevice)
    EVT_CLOSE(GraphFrame::OnClose)
END_EVENT_TABLE()

GraphFrame::GraphFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    /**
    *   Constructor for the Main frame.
    */
    deviceId = "Please select a device from the menu.";
    
    CreateGUIControls();
}

GraphFrame::~GraphFrame() {
    /** 
    *   Destructor for the Main form.
    */
}

void GraphFrame::Update() {
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
    
	Plot speed = DB_getPlotData("gps","Spd",atoi(deviceId.c_str()));
	Plot altitude = DB_getPlotData("gps","Altitude",atoi(deviceId.c_str()));
	Plot climb = DB_getPlotData("gps","Rate",atoi(deviceId.c_str()));
	
	ReplaceGraph(&altitudeGraph, createGraphFromData(wxT("Time"),altitude.time,
	                                    wxT("Altitude"),altitude.data));

	ReplaceGraph(&speedGraph, createGraphFromData(wxT("Time"),speed.time,
	                                    wxT("Speed"),speed.data));

	ReplaceGraph(&climbGraph, createGraphFromData(wxT("Time"),climb.time,
	                                    wxT("Climb"),climb.data));

    mainSizer->Layout();
}

void GraphFrame::ReplaceGraph(mpWindow** old_graph, mpWindow* new_graph) {
	mainSizer->Replace(*old_graph, new_graph);
	delete *old_graph;
	*old_graph = new_graph;
}

void GraphFrame::CreateGUIControls() {
   /**
    *   Creates all of the GUI controls on the main form.
    */
    
    // Set window properties and title bar
    SetTitle(wxT("Device Status"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
	altitudeGraph = createGraphFromData(wxT("Time"),vector<double>(),
	                                    wxT("Altitude"),vector<double>());   
    mainSizer->Add(altitudeGraph, 1, wxEXPAND | wxALL);

	speedGraph = createGraphFromData(wxT("Time"),vector<double>(),
	                                    wxT("Speed"),vector<double>());   
    mainSizer->Add(speedGraph, 1, wxEXPAND | wxALL);

	climbGraph = createGraphFromData(wxT("Time"),vector<double>(),
	                                    wxT("Climb"),vector<double>());   
    mainSizer->Add(climbGraph, 1, wxEXPAND | wxALL);

    Update();
}

mpWindow* GraphFrame::createGraphFromData(wxString x_label, vector<double> x_data,
                                  wxString y_label, vector<double> y_data) {
    mpWindow* graph;
	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    graph = new mpWindow( mainPanel, -1, wxPoint(0,0), wxSize(500,500), wxSUNKEN_BORDER );

	// Create a mpFXYVector layer
	mpFXYVector* vectorLayer = new mpFXYVector(_(""));
	vectorLayer->SetData(x_data, y_data);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);

    mpScaleX* xaxis = new mpScaleX(x_label, mpALIGN_BOTTOM, true, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(y_label, mpALIGN_LEFT, true);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);
	xaxis->SetLabelFormat(wxT("%.1f"));
	yaxis->SetLabelFormat(wxT("%.1f"));
    graph->SetMargins(30, 30, 50, 100);
    graph->AddLayer(     xaxis );
    graph->AddLayer(     yaxis );
	graph->AddLayer(     vectorLayer );
    graph->AddLayer(     new mpText(y_label + wxT(" vs ") + x_label, 60, 5) );
    mpInfoLegend* leg;
    graph->AddLayer( leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH)); //&hatch2));
    leg->SetVisible(true);
    
    graph->Fit();
    return graph;
}

void GraphFrame::OnClose(wxCloseEvent& event) {
    /**
    *   Event handler for the form closing event
    *   Exit the ChaosConnect Program
    */
    Destroy();
}

void GraphFrame::SelectDevice( wxCommandEvent& event ) {
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


void GraphFrame::NewStatusWindow( wxCommandEvent& event ) {
    /** 
     * Launches a new status window
     */
     
    GraphFrame* frame = new GraphFrame(NULL);
    frame->Show();     
}

