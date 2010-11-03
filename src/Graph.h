/**
 * \file Graph.h
 * \brief Main window header file
 */

#ifndef __GRAPH_h__
#define __GRAPH_h__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/frame.h>
#else
    #include <wx/wxprec.h>
#endif

#include <wx/panel.h>
#include <wx/event.h>

#include "mathplot.h"
#include "database.h"
#include "Plot.h"

class SingleGraphFrame;

class Graph: public mpWindow {
    public:
        Graph();
        Graph(wxPanel* panel, string name, string table, 
                              string flight_id, string col);
        virtual ~Graph();
        void Update(string flight_id = "", string db_col = "");
        Plot GetData();
        void OpenSingleGraph(wxMouseEvent& event);
        
        Plot data;
        
        mpScaleX* xaxis;
        mpScaleY* yaxis;
        mpText* title;

        bool byAltitude;

        string name;
        string db_table;
        string db_col;
        string flightId;
        string lastFlightId;

    private:
        DECLARE_EVENT_TABLE();
};

extern wxFrame* NewSingleGraphFrame(Graph*);

#endif
