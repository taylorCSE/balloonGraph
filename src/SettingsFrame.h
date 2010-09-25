/**
 * \file SettingsFrame.h
 * \brief Main window header file
 */

#ifndef __SETTINGSFRAME_h__
#define __SETTINGSFRAME_h__

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

#undef SettingsFrame_STYLE
#define SettingsFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class SettingsFrame : public BaseFrame
{
    public:
        SettingsFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AppName"), const wxPoint& pos = wxDefaultPosition, const wxSize &size = wxSize(360,600), long style = SettingsFrame_STYLE);
        virtual ~SettingsFrame();

    private:
        // Event handlers
        DECLARE_EVENT_TABLE();

        // Functions
        void CreateGUIControls();
        void Update();
        void OnOk( wxCommandEvent& event );
        void OnCancel( wxCommandEvent& event );
        
        // wxWidgets gui objects
        wxPanel *mainPanel; 
        wxBoxSizer *mainSizer;
        
        wxTextCtrl* dbHost;
        wxTextCtrl* dbName;
        wxTextCtrl* dbUser;
        wxTextCtrl* dbPass;
        
    private:
        // Enumeration for GUI controls
        enum {
            ////GUI Enum Control ID Start
            ID_OK = 2000,
            ID_CANCEL,
        };
};

#endif