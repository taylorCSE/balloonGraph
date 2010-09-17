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

    mainSizer->Layout();
}

void GraphFrame::UpdateGraph(int num, Graph* graph) {
    if(!graphs[num]) {
	    graphs[num] = graph;
        mainSizer->Add(graphs[num]->window, 1, wxEXPAND | wxALL);
    }
    graphs[num]->Update(atoi(deviceId.c_str()));
}

void GraphFrame::UpdateBasicGraphs() {
    mainSizer->SetCols(1);
	UpdateGraph(0, new Graph(mainPanel,"Altitude","gps",atoi(deviceId.c_str()),"Altitude"));
	UpdateGraph(1, new Graph(mainPanel,"Speed","gps",atoi(deviceId.c_str()),"Spd"));
	UpdateGraph(2, new Graph(mainPanel,"Climb","gps",atoi(deviceId.c_str()),"Rate"));
}

void GraphFrame::UpdateAnalogGraphs() {
	char name[4];
	
    mainSizer->SetCols(3);
	for(int i = 0; i<18; i++) {
        name[0] = 'A';
        name[1] = 0x00;
        sprintf(name,"%s%d",name,i+1);
        UpdateGraph(i, new Graph(mainPanel,name,"aip",atoi(deviceId.c_str()),name));
	}
}

void GraphFrame::CreateGUIControls() {
   /**
    *   Creates all of the GUI controls on the main form.
    */
    
    SetTitle(wxT("Device Graphs"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxGridSizer(3);
    mainPanel->SetSizer(mainSizer);
    
    ClearGraphs();

    Update();
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
        ClearGraphs();
    }
    
    if(id == VIEW_BASIC) {
        ClearGraphs();
        view = VIEW_BASIC;
    }
    if(id == VIEW_ANALOG) {
        ClearGraphs();
        view = VIEW_ANALOG;
    }
    
    Update();
}

void GraphFrame::ClearGraphs() {
    for(int i = 0; i<18; i++) {
        if(graphs[i]) mainSizer->Remove(graphs[i]->window);
        delete graphs[i];
        graphs[i] = 0x00;
    }
}

void GraphFrame::NewStatusWindow( wxCommandEvent& event ) {
    /** 
     * Launches a new status window
     */
     
    GraphFrame* frame = new GraphFrame(NULL);
    frame->Show();     
}

