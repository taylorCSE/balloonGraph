/**
 * \file GraphFrame.cpp
 * \brief Main Windows Class
 */
 
#include "GraphFrame.h"

BEGIN_EVENT_TABLE(GraphFrame,wxFrame)
    EVT_MENU(ID_NEWWINDOW, GraphFrame::NewStatusWindow)
    EVT_MENU(-1, GraphFrame::SelectDevice)
    EVT_CLOSE(GraphFrame::OnClose)
    EVT_TIMER(UPDATE_TIMER, GraphFrame::OnTimer)
END_EVENT_TABLE()

GraphFrame::GraphFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style) {
    /**
    *   Constructor for the Main frame.
    */
    deviceId = "Please select a device from the menu.";
    
    view = VIEW_BASIC;
    
    CreateGUIControls();
    
    updateTimer = new wxTimer(this, UPDATE_TIMER);
    updateTimer->Start(5000);
}

GraphFrame::~GraphFrame() {
    /** 
    *   Destructor for the Main form.
    */
}

void GraphFrame::OnTimer(wxTimerEvent& event) {
    Update();
}

void GraphFrame::Update() {
    /**
     * Updates the GUI with new database information
     */
    wxMenuBar *menubar = new wxMenuBar;
    wxMenu *devices_menu = new wxMenu;
    wxMenu *view_menu = new wxMenu;
    
    deviceIds = DB_getAllDevices();
    
    menubar->Append(devices_menu, wxT("&Devices"));

    for(unsigned int i = 0; i < deviceIds.size(); i++) {
        devices_menu->Append(10000+i, deviceIds[i]);
    }

    menubar->Append(view_menu, wxT("&View"));
    
    view_menu->Append(VIEW_BASIC, wxT("Basic"));
    view_menu->Append(VIEW_ANALOG, wxT("Analog Channels"));

    SetMenuBar(menubar);
    
    switch(view) {
        case VIEW_ANALOG:   
            UpdateAnalogGraphs();
            break;
        case VIEW_BASIC:
            UpdateBasicGraphs();
            break;
        default:
            UpdateBasicGraphs();
            break;
    }
}

void GraphFrame::UpdateBasicGraphs() {
	Plot speed = DB_getPlotData("gps","Spd",atoi(deviceId.c_str()));
	Plot altitude = DB_getPlotData("gps","Altitude",atoi(deviceId.c_str()));
	Plot climb = DB_getPlotData("gps","Rate",atoi(deviceId.c_str()));
	
	SetNumGraphs(3);
	
	ReplaceGraph(0, createGraphFromData(wxT("Time"),altitude.time,
	                                    wxT("Altitude"),altitude.data));

	ReplaceGraph(1, createGraphFromData(wxT("Speed"),speed.data,
	                                    wxT("Altitude"),speed.altitude));

	ReplaceGraph(2, createGraphFromData(wxT("Climb"),climb.data,
	                                    wxT("Altitude"),climb.altitude));

    mainSizer->Layout();
}

void GraphFrame::UpdateAnalogGraphs() {
	Plot speed = DB_getPlotData("gps","Spd",atoi(deviceId.c_str()));
	Plot altitude = DB_getPlotData("gps","Altitude",atoi(deviceId.c_str()));
	Plot climb = DB_getPlotData("gps","Rate",atoi(deviceId.c_str()));
	mpWindow* tmp_graph[18];
	char name[4];
	
    mainSizer->Layout();

	for(int i = 0; i<18; i++) {
	    if(!graphs[i]) {
	        name[0] = 'A';
	        name[1] = 0x00;
	        sprintf(name,"%s%d",name,i+1);
	        graphs[i] = new Graph(name,"aip",atoi(deviceId.c_str()),name);
	        mainSizer->Add(graphs[i]->window, 1, wxEXPAND | wxALL);
	    }
	    //graphs[i]->Update();
        mainSizer->Layout();
	}

    mainSizer->Layout();
}

void GraphFrame::ReplaceGraph(int graph_num, mpWindow* new_graph) {
	mainSizer->Replace(graphs[graph_num], new_graph);
	delete graphs[graph_num];
	graphs[graph_num] = new_graph;
}

void GraphFrame::SetNumGraphs(int num) {
    mainSizer->SetCols((num-1)/6 + 1);

	for(int i = 0; i < num; i++) {
        if(!graphs[i]) {
            graphs[i] = new mpWindow( mainPanel, -1, wxPoint(0,0), wxSize(1,1), wxSUNKEN_BORDER );
            mainSizer->Add(graphs[i], 1, wxEXPAND | wxALL);
        }
	}

	for(int i = num; i < 18; i++) {
	    if(graphs[i]) {
	        delete graphs[i];
	        mainSizer->Remove(graphs[i]);
	        graphs[i] = 0x00;
	    }
	}
}

void GraphFrame::CreateGUIControls() {
   /**
    *   Creates all of the GUI controls on the main form.
    */
    
    // Set window properties and title bar
    SetTitle(wxT("Device Graphs"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxGridSizer(3);
    mainPanel->SetSizer(mainSizer);
    
    for(int i = 0; i < 18; i++) {
        graphs[i] = 0x00;
    }

    Update();
}

mpWindow* GraphFrame::createGraphFromData(wxString x_label, vector<double> x_data,
                                  wxString y_label, vector<double> y_data) {
    mpWindow* graph;
	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    graph = new mpWindow( mainPanel, -1, wxPoint(0,0), wxSize(1,1), wxSUNKEN_BORDER );

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

void GraphFrame::UpdateGraphFromData(int num, vector<double> x_data, vector<double> y_data) {
	mpFXYVector* vectorLayer = (mpFXYVector*)graphs[num]->GetLayer(3);
	
	vectorLayer->SetData(x_data, y_data);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);
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
    
    if(id == VIEW_BASIC) { 
        SetNumGraphs(0);
        view = VIEW_BASIC;
    }
    if(id == VIEW_ANALOG) {
        SetNumGraphs(0);
        view = VIEW_ANALOG;
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

