/**
 * \file Graph.cpp
 * \brief Graphs Class
 */
 
#include "Graph.h"

BEGIN_EVENT_TABLE(Graph,mpWindow)
    EVT_LEFT_DCLICK(Graph::OpenSingleGraph)
END_EVENT_TABLE()

/**
   Constructor
*/
    
Graph::Graph(wxPanel* panel, string name, string table, 
                             string flight_id, string col)
    : mpWindow(panel, -1, wxPoint(0,0), wxSize(1,1), wxSUNKEN_BORDER) {

    this->name = name;
    this->db_table = table;
    this->db_col = col;
    this->flightId = flight_id;
    this->lastFlightId = "";
    
    // Set up the font    
    wxFont windowFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, 
                          wxFONTWEIGHT_NORMAL);
    // Get the data for the graph
    Plot data = GetData();

    string y_label = wxT("Altitude");
    string x_label = wxT(name);
    
	// Create a mpFXYVector layer
	mpFXYVector* vectorLayer = new mpFXYVector(_(""));
	vectorLayer->SetData(data.altitude, data.data);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);

	// Set up the axis
    xaxis = new mpScaleX(x_label, mpALIGN_BOTTOM, true, mpX_NORMAL);
    yaxis = new mpScaleY(y_label, mpALIGN_LEFT, true);
    xaxis->SetFont(windowFont);
    yaxis->SetFont(windowFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);
	xaxis->SetLabelFormat(wxT("%.1f"));
	yaxis->SetLabelFormat(wxT("%.1f"));
    SetMargins(30, 30, 50, 70);
    
    // Set up the legend
    mpInfoLegend* leg;
    leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH);
    leg->SetVisible(true);

    // Create the title
   	title = new mpText(y_label + wxT(" vs ") + x_label, 60, 5);
    
    // Add all the layers
    AddLayer(xaxis);
    AddLayer(yaxis);
	AddLayer(vectorLayer);
    AddLayer(title);
    AddLayer(leg);

    // Lay items out nicely
    Fit();
}

/**
    Destructor
*/

Graph::~Graph() {
}

/**
    Update the graph with new data
*/

void Graph::Update(string flight_id, string db_col) {
    /// TODO: graphs need to fit when changing data flight
    if(flight_id != "") flightId = flight_id;
    if(db_col != "") {
        this->db_col = db_col;
        this->name = db_col;
        // TODO: database code could completely handle the tables
        if(db_col.c_str()[0] == 'A') this->db_table = "aip";
        
        // Flag flight ID as changed so that the graph will auto fit
        lastFlightId = "";
    }
    
    mpFXYVector * vectorLayer = (mpFXYVector*)this->GetLayer(2);
    data = GetData();

    // Update labels
    string y_label = wxT("Altitude");
    string x_label = wxT(name);

    xaxis->SetName(x_label);
    yaxis->SetName(y_label);
    title->SetName(y_label + wxT(" vs ") + x_label);

	// Create a mpFXYVector layer
	vectorLayer->SetData(data.altitude, data.data);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);
	
	UpdateAll();
	
	if(flightId != lastFlightId) {
	    lastFlightId = flightId;
	    Fit();
	}
}

/**
    Get new data from the database
*/

Plot Graph::GetData() {
    Plot result = DB_getPlotData(db_col,flightId);
    return result;
}

/**
    Open a single frame version of this graph
    
    This event handlers fires on a double click.
*/

void Graph::OpenSingleGraph(wxMouseEvent& event) {
    wxFrame* frame = NewSingleGraphFrame(this);
    frame->Show();     
}
