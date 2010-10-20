/**
 * \file SingleGraphFrame.cpp
 * \brief Frame for single graphs
 */
 
#include "SingleGraphFrame.h"

BEGIN_EVENT_TABLE(SingleGraphFrame,BaseFrame)
    EVT_MENU(-1, SingleGraphFrame::SetData)
END_EVENT_TABLE()

/**
   Constructor for the Main frame.
*/

SingleGraphFrame::SingleGraphFrame(Graph* graph)
: BaseFrame() {
    this->graph = graph;
    
    flightId = string(graph->flightId);
    
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
    CreateMenu(false, false, true, false,true);
    
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

    flightId = graph->flightId;
    Update();
    graph->Fit();
}

/**
    OnMenu event handler
    
    This overloads the method in baseframe to capture the data events.
*/

void SingleGraphFrame::SetData( wxCommandEvent& event ) {
    int id = event.GetId();
    
    if(id > 9000 && id <= 9018) {
        /// We're selecting a dataset
        string db_col = wxString::Format("A%d",id - 9000).c_str();
        graph->Update(flightId,db_col);
    }
    
    if(id == ID_ALTITUDE) {
        graph->Update(flightId,"Altitude");
    }

    if(id == ID_SPEED) {
        graph->Update(flightId,"Spd");
    }

    if(id == ID_CLIMB) {
        graph->Update(flightId,"Rate");
    }

    if(id == ID_BEARING) {
        graph->Update(flightId,"Hdg");
    }

    if(id > 10000) {
        /// We're selecting a device
        flightId = flightIds[id - 10000];
    }    
    
    Update();
}

wxFrame* NewSingleGraphFrame(Graph* graph) {
    return (wxFrame*)(new SingleGraphFrame(graph));
}
