/**
 * \file App.h
 * \brief Main Application Header File
 */

#ifndef __BALLOONGRAPH_h__
#define __BALLOONGRAPH_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

#define APP_NAME "BalloonGraph"

class BalloonGraph : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
