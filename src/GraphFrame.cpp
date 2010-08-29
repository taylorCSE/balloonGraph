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
    
	// Create two vectors for x,y and fill them with data
	std::vector<double> vectorx, vectory;
	double xcoord;
	for (unsigned int p = 0; p < 100; p++) {
		xcoord = (double)(p*1000.0);
		vectorx.push_back(25-0.001*pow(xcoord/1000, 2));
		vectory.push_back(xcoord);
	}
	
	altitudeGraph = createGraph(wxT("Temperature"),vectorx,wxT("Altitude"),vectory);   
    mainSizer->Add(altitudeGraph, 1, wxEXPAND | wxALL);
    
    Update();
}

mpWindow* GraphFrame::createGraph(wxString x_label, vector<double> x_data,
                                  wxString y_label, vector<double> y_data) {
    mpWindow* graph;
	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    graph = new mpWindow( mainPanel, -1, wxPoint(0,0), wxSize(100,100), wxSUNKEN_BORDER );

	// Create a mpFXYVector layer
	mpFXYVector* vectorLayer = new mpFXYVector(_(""));
	vectorLayer->SetData(x_data, y_data);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);

    mpScaleX* xaxis = new mpScaleX(wxT("Temperature"), mpALIGN_BOTTOM, true, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Altitude"), mpALIGN_LEFT, true);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);
	xaxis->SetLabelFormat(wxT("%.2f"));
	yaxis->SetLabelFormat(wxT("%.1f"));
    graph->SetMargins(30, 30, 50, 100);
    graph->AddLayer(     xaxis );
    graph->AddLayer(     yaxis );
	graph->AddLayer(     vectorLayer );
    graph->AddLayer(     new mpText(wxT("Altitude vs Temperature"), 60, 5) );
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
