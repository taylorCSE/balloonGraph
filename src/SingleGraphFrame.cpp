/**
 * \file SingleGraphFrame.cpp
 * \brief Frame for single graphs
 */
 
#include "SingleGraphFrame.h"

BEGIN_EVENT_TABLE(SingleGraphFrame,BaseFrame)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

SingleGraphFrame::SingleGraphFrame(Graph* graph)
: BaseFrame() {
    flightId = "Please select a device from the menu.";
    
    this->graph = graph;
    
    CreateGUIControls();
    
    SetTransparent(245);
}

/** 
   Destructor for the Main frame.
*/

SingleGraphFrame::~SingleGraphFrame() {
}

/**
    Updates the GUI with new database information
*/

void SingleGraphFrame::Update() {
    CreateMenu(false, false, true, false);
    
    graph->Update(flightId);
}

/**
   Creates all of the GUI controls on the frame.
*/
    
void SingleGraphFrame::CreateGUIControls() {
    // Set window properties and title bar
    SetTitle(wxT("Graph"));
    SetIcon(wxNullIcon);
    
    mainPanel = new wxPanel(this, wxID_ANY);
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainPanel->SetSizer(mainSizer);
    
    graph = new Graph(mainPanel,
                      graph->name,
                      graph->db_table,
                      graph->flightId,
                      graph->db_col);     
    mainSizer->Add(graph, 1, wxEXPAND | wxALL);

    Update();
}

wxFrame* NewSingleGraphFrame(Graph* graph) {
    return (wxFrame*)(new SingleGraphFrame(graph));
}

