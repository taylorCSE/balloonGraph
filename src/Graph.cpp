/**
 * \file Graph.cpp
 * \brief Graphs Class
 */
 
#include "Graph.h"

Graph::Graph(char* name, char* table, int device_id, char* col) {
    /**
    *   Constructor for the Main frame.
    */
	wxFont windowFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    window = new mpWindow( mainPanel, -1, wxPoint(0,0), wxSize(1,1), wxSUNKEN_BORDER );

    Plot data = GetData();
    
	// Create a mpFXYVector layer
	mpFXYVector* vectorLayer = new mpFXYVector(_(""));
	vectorLayer->SetData(data.alitude, data.data);
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
    return window;    
}

Graph::~Graph() {
    /** 
    *   Destructor for the Main form.
    */
}

Plot Graph::GetData() {
    return DB_getPlotData(table,db_col,device_id);
}