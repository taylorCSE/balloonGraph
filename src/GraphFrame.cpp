/**
 * \file GraphFrame.cpp
 * \brief Main Windows Class
 */
 
#include "GraphFrame.h"

BEGIN_EVENT_TABLE(GraphFrame,BaseFrame)
    EVT_MENU(ID_FITALL, GraphFrame::FitAll)
END_EVENT_TABLE()

GraphFrame::GraphFrame()
: BaseFrame() {
    /**
    *   Constructor for the Main frame.
    */
    flightId = "Please select a device from the menu.";
    
    last_view = view;
    
    CreateGUIControls();
    
}

GraphFrame::~GraphFrame() {
    /** 
    *   Destructor for the Main form.
    */
    ClearGraphs();
}

void GraphFrame::Update() {
    /**
     * Updates the GUI with new database information
     */
    if(last_view != view) ClearGraphs();
    last_view = view;
     
    CreateMenu();
    
    wxMenu *graph_menu = new wxMenu;
    
    menubar->Append(graph_menu, wxT("&Graphs"));
    
    graph_menu->Append(ID_FITALL, wxT("Fit All"));
    
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

void GraphFrame::UpdateBasicGraphs() {
    mainSizer->SetCols(1);
	UpdateGraph(0, new Graph(mainPanel,"Altitude","gps",flightId,"Altitude"));
	UpdateGraph(1, new Graph(mainPanel,"Speed","gps",flightId,"Spd"));
	UpdateGraph(2, new Graph(mainPanel,"Climb","gps",flightId,"Rate"));
}

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

void GraphFrame::CreateGUIControls() {
   /**
    *   Creates all of the GUI controls on the main form.
    */
    
    SetTitle(wxT("Device Graphs"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxGridSizer(3);
    mainPanel->SetSizer(mainSizer);
    
    for(int i = 0; i < 18; i++) graphs[i] = 0x00;
    
    ClearGraphs();

    Update();
}

void GraphFrame::FitAll( wxCommandEvent& event ) {
    for(int i = 0; i < 18; i++) {
        if(graphs[i]) {
            graphs[i]->Fit();
        }
    }
}

void GraphFrame::ClearGraphs() {
    for(int i = 0; i<18; i++) {
        if(graphs[i]) mainSizer->Remove(graphs[i]);
        delete graphs[i];
        graphs[i] = 0x00;
    }
}

wxFrame* NewGraphFrame() {
    return (wxFrame*)(new GraphFrame());
}
