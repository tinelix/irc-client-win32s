//  MainDlg.h : header file
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
// CMainDlg dialog

#define WM_SOCKET_READ 0xAFFF;

class CMainDlg : public CDialog
{
// Construction
public:
	BOOL is_connected;

	void SendIRCMessage(CWnd* parent);

	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MAINDIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CFont font;
	void CreateTabs();
	void PrepareConnect(LPSTR address, int port);
	void PrepareConnect(int result);
	void ImportDllFunctions();
	void IdentificateConnection();
	void SendPing(CString ping_hexcode);
	CString ParseMessage(char* irc_packet);
	void LoadSettings(char* ini_filename);
	void LoadProfileSettings(char* ini_filename);
	void LoadProfileSettingsF(char* address);

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuHelpAbout();
	afx_msg void OpenConnectionManager();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnConnectionStatistics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CConnManDlg;
};
