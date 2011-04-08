/**
 * \file GraphFrame.h
 * \brief Graph frame header file
 */

#ifndef __GRAPHFRAME_h__
#define __GRAPHFRAME_h__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/frame.h>
#else
    #include <wx/wxprec.h>
#endif


#include <wx/timer.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/progdlg.h>
#include <wx/dcbuffer.h>
#include <wx/html/htmlwin.h>
                           
#include "MathPlot.h"
#include "BaseFrame.h"
#include "database.h"
#include "Graph.h"
#include "Plot.h"

class GraphFrame : public BaseFrame
{
    public:
        GraphFrame();
        virtual ~GraphFrame();

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();
        void UpdateBasicGraphs();
        void UpdateAnalogGraphs();
        void ClearGraphs();
        void FitAll(wxCommandEvent& event);
        void UpdateGraph(int num, Graph* graph);

        // Functions
        void Update();
        void CreateGUIControls();
        
        // wxWidgets gui objects
        wxPanel *mainPanel; 
        wxPanel *colPanel[3]; 
        wxGridSizer *mainSizer;
        wxBoxSizer *colSizer[3];
        
        Graph* graphs[18];
        
        int last_view;
        string lastFlightId;
        
    private:
        // ID's for GUI controls
        enum {
            ID_TEXT = 2000,
            ID_FLIPAXIS,
            ID_FITALL
        };
};

#endif
