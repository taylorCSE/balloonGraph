/**
 * \file SingleGraphFrame.h
 * \brief SingleGraphFrame header file
 */

#ifndef __SINGLEFRAME_h__
#define __SINGLEGRAPHFRAME_h__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/frame.h>
#else
    #include <wx/wxprec.h>
#endif

#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/sizer.h>
                           
#include "GraphFrame.h"
#include "Graph.h"
#include "mathplot.h"
#include "database.h"
#include "BaseFrame.h"

class SingleGraphFrame : public BaseFrame
{
    public:
        SingleGraphFrame(Graph* graph);
        virtual ~SingleGraphFrame();
        void SetData(wxCommandEvent& event );
        void InitialFit(wxTimerEvent& event);

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();

        // Functions
        void Update();

        // wxWidgets gui objects
        wxPanel *mainPanel; 
        wxBoxSizer *mainSizer;

        Graph* graph;
        
        wxTimer* fitTimer;
        
    private:
        // IDs for GUI elements
        enum {
            ID_TEXT = 2000,
            ID_FLIPAXIS,
            FIT_TIMER,
        };
};

#endif
