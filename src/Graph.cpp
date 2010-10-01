/**
 * \file Graph.cpp
 * \brief Graphs Class
 */
 
#include "Graph.h"

Graph::Graph(wxPanel* panel, char* name, char* table, int flight_id, char* col) {
    /**
    *   Constructor for the Main frame.
    */
	wxFont windowFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    window = new mpWindow(panel, -1, wxPoint(0,0), wxSize(1,1), wxSUNKEN_BORDER);
	
    this->name = name;
    this->db_table = table;
    this->db_col = col;
    this->flightId = flight_id;
    
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

    mpScaleX* xaxis = new mpScaleX(x_label, mpALIGN_BOTTOM, true, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(y_label, mpALIGN_LEFT, true);
    xaxis->SetFont(windowFont);
    yaxis->SetFont(windowFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);
	xaxis->SetLabelFormat(wxT("%.1f"));
	yaxis->SetLabelFormat(wxT("%.1f"));
    window->SetMargins(30, 30, 50, 100);
    window->AddLayer(     xaxis );
    window->AddLayer(     yaxis );
	window->AddLayer(     vectorLayer );
    window->AddLayer(     new mpText(y_label + wxT(" vs ") + x_label, 60, 5) );
    mpInfoLegend* leg;
    window->AddLayer( leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH)); //&hatch2));
    leg->SetVisible(true);
    
    window->Fit();
}

Graph::~Graph() {
    /** 
    *   Destructor for the Main form.
    */
    
    delete window;
}

void Graph::Update(int flight_id) {
    if(flight_id > 0) flightId = flight_id;
    
    mpFXYVector * vectorLayer = (mpFXYVector*)window->GetLayer(2);
    data = GetData();

    string y_label = wxT("Altitude");
    string x_label = wxT(name);
    
	// Create a mpFXYVector layer
	vectorLayer->SetData(data.altitude, data.data);
	vectorLayer->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	vectorLayer->SetPen(vectorpen);
	vectorLayer->SetDrawOutsideMargins(false);
	
	window->UpdateAll();
}

Plot Graph::GetData() {
    return DB_getPlotData((char*)db_table.c_str(),(char*)db_col.c_str(),flightId);
}

void Graph::Fit() {
    window->Fit();
}
