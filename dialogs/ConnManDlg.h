//  ConnManDlg.h : header file
//
//  Copyright © 2023 Dmitry Tretyakov (aka. Tinelix)
//  
//	This file is part of Tinelix IRC Client.
//
//  Tinelix IRC Client is free software: you can redistribute it and/or modify it under 
//  the terms of the GNU General Public License as published by the Free Software Foundation, 
//  either version 3 of the License, or (at your option) any later version.
//  Tinelix IRC Client is distributed in the hope that it will be useful, but WITHOUT ANY 
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
//  PARTICULAR PURPOSE.
//  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along with this
//  program. If not, see https://www.gnu.org/licenses/.
//
//  Source code: https://github.com/tinelix/irc-client-win32s

/////////////////////////////////////////////////////////////////////////////
// CConnManDlg dialog

class CConnManDlg : public CDialog
{
// Construction
public:
	CConnManDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnManDlg)
	enum { IDD = IDD_CONNMANDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnManDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	typedef struct _LV_ITEMA {
		UINT mask;
		int iItem;
		int iSubItem;
		UINT state;
		UINT stateMask;
		LPTSTR pszText;
		int cchTextMax;
		int iImage;
		LPARAM lParam;
		#if(_WIN32_IE >= 0x0300)
			int iIndent;
		#endif
	} LVITEM, FAR *LPLVITEM;
	void LoadProfileList();
	// Generated message map functions
	//{{AFX_MSG(CConnManDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateProfileBtn();
	afx_msg void OnProfileListSelection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
