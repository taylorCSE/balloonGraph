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

class Graph: public mpWindow {
    public:
        Graph(wxPanel* panel, char* name, char* table, string flight_id, char* col);
        virtual ~Graph();
        void Update(string flight_id = "");
        Plot GetData();
        void OpenSingleGraph(wxMouseEvent& event);
        
        Plot data;
        
    private:
        DECLARE_EVENT_TABLE();

        string name;
        string db_table;
        string db_col;
        string flightId;
};

#endif
