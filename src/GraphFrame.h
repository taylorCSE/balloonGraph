/**
 * \file GraphFrame.h
 * \brief Main window header file
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

#undef GraphFrame_STYLE
#define GraphFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class GraphFrame : public BaseFrame
{
    public:
        GraphFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AppName"), const wxPoint& pos = wxDefaultPosition, const wxSize &size = wxSize(360,600), long style = GraphFrame_STYLE);
        virtual ~GraphFrame();

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();
        void SelectDevice(wxCommandEvent& event);
        void UpdateBasicGraphs();
        void UpdateAnalogGraphs();
        void ClearGraphs();
        void UpdateGraph(int num, Graph* graph);
        void OnClose(wxCloseEvent& event);

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
        
    private:
        // Enumeration for GUI controls
        enum {
            ////GUI Enum Control ID Start
            ID_TEXT = 2000,
            UPDATE_TIMER
        };
};

#endif
