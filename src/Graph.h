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

#include "mathplot.h"
#include "database.h"
#include "Plot.h"

class Graph {
    public:
        Graph(wxPanel* panel, char* name, char* table, int device_id, char* col);
        virtual ~Graph();
        void Update(int device_id = 0);
        Plot GetData();
        void Fit();
        mpWindow* window;
        
        Plot data;
        
    private:
        string name;
        string db_table;
        string db_col;
        string deviceId;
};

#endif
