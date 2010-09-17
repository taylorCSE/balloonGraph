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

#undef StatusFrame_STYLE
#define StatusFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class StatusFrame : public BaseFrame
{
    public:
        StatusFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AppName"), const wxPoint& pos = wxDefaultPosition, const wxSize &size = wxSize(360,600), long style = StatusFrame_STYLE);
        virtual ~StatusFrame();

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();
        void SelectDevice(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);

        // Functions
        void Update();
        void CreateGUIControls();
        
        // wxWidgets gui objects
        wxPanel *mainPanel; 
        wxBoxSizer *mainSizer;
        wxHtmlWindow *deviceInfo;
        
        vector<string> deviceIds;
        string deviceId;
        
    private:
        // Enumeration for GUI controls
        enum {
            ////GUI Enum Control ID Start
            ID_TEXT = 2000,
        };
};

#endif
