/**
 * \file BaseFrame.h
 * \brief Main window header file
 */
#ifndef __BASEFRAME_h__
#define __BASEFRAME_h__

#ifdef __BORLANDC__
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/frame.h>
#else
    #include <wx/wxprec.h>
#endif

#include <wx/menu.h>

#include "database.h"
#include "version.h"

#undef BaseFrame_STYLE
#define BaseFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class GraphFrame;
class StatusFrame;
class SettingsFrame;

extern wxFrame* NewGraphFrame();
extern wxFrame* NewStatusFrame();
extern wxFrame* NewSettingsFrame();

class BaseFrame : public wxFrame
{
    public:
        BaseFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AppName"), const wxPoint& pos = wxDefaultPosition, const wxSize &size = wxSize(360,600), long style = BaseFrame_STYLE);
        void NewStatusWindow(wxCommandEvent& event);
        void NewGraphWindow(wxCommandEvent& event);
        void NewSettingsWindow(wxCommandEvent& event);
        virtual ~BaseFrame();
        void CreateMenu();
        void SelectDevice(wxCommandEvent& event );
        void OnTimer(wxTimerEvent& event);
        void OnClose(wxCloseEvent& event);

        virtual void Update() = 0;

        wxMenuBar *menubar;
        wxMenu *devices_menu;
        wxMenu *view_menu;
        wxMenu *window_menu;
        vector<string> deviceIds;
        string deviceId;
        
        wxTimer* updateTimer;
        
        int view;
        
    private:
        DECLARE_EVENT_TABLE();
        // Enumeration for GUI controls
        enum {
            ////GUI Enum Control ID Start
            ID_TEXT = 1000,
            VIEW_BASIC,
            VIEW_ANALOG,
            VIEW_SETTINGS,
            UPDATE_TIMER,
            ID_NEWSTATUS,
            ID_NEWSETTINGS,
            ID_NEWGRAPH
        };
};
#endif
