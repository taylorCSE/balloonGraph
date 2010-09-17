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
        Plot GetData();
        
    private:
        char* name;
        char* db_table;
        char* db_col;
        int deviceId;
        mpWindow* window;
};

#endif