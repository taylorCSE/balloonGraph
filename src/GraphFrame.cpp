/**
 * \file GraphFrame.cpp
 * \brief Main Windows Class
 */
 
#include "GraphFrame.h"

BEGIN_EVENT_TABLE(GraphFrame,BaseFrame)
    EVT_MENU(ID_FITALL, GraphFrame::FitAll)
    EVT_MENU(ID_FLIPAXIS, GraphFrame::FlipAxis)
    EVT_MENU(ID_FLIPALTITUDE, GraphFrame::FlipAltitude)
END_EVENT_TABLE()

/**
    Constructor
*/

GraphFrame::GraphFrame()
: BaseFrame() {
    flightId = "Please select a device from the menu.";
    
    last_view = view;
    
    CreateGUIControls();
    
}

/**
    Deconstructor
*/

GraphFrame::~GraphFrame() {
    ClearGraphs();
}

/**
    Update the GUI with new information
*/

void GraphFrame::Update() {
    if(last_view != view) ClearGraphs();
    last_view = view;
     
    CreateMenu();
    
    view_menu->Append(ID_FLIPALTITUDE, wxT("Time/Altitude"));
    view_menu->Append(ID_FLIPAXIS, wxT("Flip Axis"));
    view_menu->Append(ID_FITALL, wxT("Fit All"));
    
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
    
    /// TODO: I'm sure there is a cleaner way to perform this call.
    wxCommandEvent e;
    if(lastFlightId != flightId) FitAll(e);
    lastFlightId = flightId;
}

/**
    Update a specified graph
*/

void GraphFrame::UpdateGraph(int num, Graph* graph) {
    /// TODO: This function should not be sent a graph pointer.
    /// It should actually get a set of string that define the graph
    /// and then it should decide whether to create a graph or not.
    if(!graphs[num]) {
	    graphs[num] = graph;
        mainSizer->Add(graphs[num], 1, wxEXPAND | wxALL);
    } else {
        delete graph;
    }
    graphs[num]->Update(flightId);
}

/**
    Update the basic graphs
*/

void GraphFrame::UpdateBasicGraphs() {
    mainSizer->SetCols(1);
	UpdateGraph(0, new Graph(mainPanel,"Altitude","gps",flightId,"Altitude"));
	UpdateGraph(1, new Graph(mainPanel,"Speed","gps",flightId,"Spd"));
	UpdateGraph(2, new Graph(mainPanel,"Climb","gps",flightId,"Rate"));
}

/**
    Update the analog graphs
    
    This loops through all 18 of the analog items and displays them
*/

void GraphFrame::UpdateAnalogGraphs() {
	char name[4];
	
    mainSizer->SetCols(3);
	for(int i = 0; i<18; i++) {
        name[0] = 'A';
        name[1] = 0x00;
        sprintf(name,"%s%d",name,i+1);
        UpdateGraph(i, new Graph(mainPanel,name,"aip",flightId,name));
	}
}

/**
    Create the GUI controls
*/

void GraphFrame::CreateGUIControls() {
    SetTitle(wxT("Device Graphs"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxGridSizer(3);
    mainPanel->SetSizer(mainSizer);
    
    for(int i = 0; i < 18; i++) graphs[i] = 0x00;
    
    ClearGraphs();

    Update();
}
    
/**
    Fit all graphs

    This simply calls Fit() on each of the graphs that are active.    
*/

void GraphFrame::FitAll( wxCommandEvent& event ) {
    for(int i = 0; i < 18; i++) {
        if(graphs[i]) {
            graphs[i]->Fit();
        }
    }
}

/**
    Flip the x and y axis

    This simply calls FlipAxis() on each of the graphs that are active.    
*/

void GraphFrame::FlipAxis( wxCommandEvent& event ) {
    for(int i = 0; i < 18; i++) {
        if(graphs[i]) {
            graphs[i]->FlipAxis();
        }
    }
}

/**
    Switch between time and altitude

    This simply alternates byAltitude on each of the graphs that are active.    
*/

void GraphFrame::FlipAltitude( wxCommandEvent& event ) {
    for(int i = 0; i < 18; i++) {
        if(graphs[i]) {
            graphs[i]->byAltitude = !(graphs[i]->byAltitude);
            graphs[i]->Update();
            graphs[i]->Fit();
        }
    }
}

/**
    Clears all graphs
    
    This removes all existing graphs from the sizer and deletes them from
    memory.
*/

void GraphFrame::ClearGraphs() {
    for(int i = 0; i<18; i++) {
        if(graphs[i]) { 
            mainSizer->Remove(graphs[i]);
            graphs[i]->Destroy();
            graphs[i] = 0x00;
        }
    }
}

/**
    Create a new graph frame.
    
    This function allows for the creation of new graph frame from classes
    that don't know about all of the details of the class. This is used
    by BaseFrame to create a new GraphFrame from the menu.
*/

wxFrame* NewGraphFrame() {
    return (wxFrame*)(new GraphFrame());
}
