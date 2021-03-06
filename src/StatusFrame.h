/**
 * \file StatusFrame.h
 * \brief Main window header file
 */

#ifndef __STATUSFRAME_h__
#define __STATUSFRAME_h__

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
                           
#include "GraphFrame.h"
#include "mathplot.h"
#include "database.h"
#include "BaseFrame.h"

class StatusFrame : public BaseFrame
{
    public:
        StatusFrame();
        virtual ~StatusFrame();

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();

        // Functions
        string ColorString(string input, string true_value = "");
        void Update();
        void CreateGUIControls();
        
        // wxWidgets gui objects
        wxPanel *mainPanel; 
        wxBoxSizer *mainSizer;
        wxHtmlWindow *deviceInfo;
        
    private:
        // IDs for GUI elements
        enum {
            ID_TEXT = 2000,
        };
};

#endif
