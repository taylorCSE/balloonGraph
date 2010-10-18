/**
 * \file BaseFrame.h
 * \brief Main frame header file
 *
 * All of the frame classes extend this one. It provides basic menus, 
 * flight selections, and an update timer.
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

class GraphFrame;
class StatusFrame;
class SettingsFrame;
class AboutFrame;

extern wxFrame* NewGraphFrame();
extern wxFrame* NewStatusFrame();
extern wxFrame* NewSettingsFrame();
extern wxFrame* NewAboutFrame();

class BaseFrame : public wxFrame
{
    public:
        BaseFrame();
        void NewStatusWindow(wxCommandEvent& event);
        void NewGraphWindow(wxCommandEvent& event);
        void NewSettingsWindow(wxCommandEvent& event);
        void NewAboutWindow(wxCommandEvent& event);
        virtual ~BaseFrame();
        void CreateMenu(bool show_view = true, 
                        bool show_window = true, 
                        bool show_flights = true,
                        bool show_help = true);
        void OnMenu(wxCommandEvent& event );
        void OnTimer(wxTimerEvent& event);
        void OnClose(wxCloseEvent& event);

        virtual void Update() = 0;

        wxMenuBar *menubar;
        wxMenu *flight_menu;
        wxMenu *view_menu;
        wxMenu *window_menu;
        wxMenu *help_menu;
        vector<string> flightIds;
        string flightId;
        
        wxTimer* updateTimer;
        
        int view;
        
    private:
        DECLARE_EVENT_TABLE();
        /// IDs for various controls
        enum {
            ID_TEXT = 1000,
            VIEW_BASIC,
            VIEW_ANALOG,
            VIEW_SETTINGS,
            UPDATE_TIMER,
            ID_NEWSTATUS,
            ID_NEWSETTINGS,
            ID_NEWGRAPH,
            ID_ABOUT,
        };
};
#endif
