// Tinelix IRC Client for Win32s (Windows 3.1x / Windows 9x / Windows NT)
// Licensed by GPLv3.

// TLX_IRC.h : main header file for the TLX_IRC application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// IRCClient:
// See TLX_IRC.cpp for the implementation of this class
//

class IRCClient : public CWinApp
{
public:
	IRCClient();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IRCClient)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(IRCClient)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class ConnectionManagerDialog;
};


/////////////////////////////////////////////////////////////////////////////
