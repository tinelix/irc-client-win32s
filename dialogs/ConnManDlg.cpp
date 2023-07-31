//  ConnManDlg.cpp : implementation file
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

#include "stdafx.h"
#include "..\Tinelix IRC.h"
#include "MainDlg.h"
#include "ConnManDlg.h"
#include "TextBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

WIN32_FIND_DATA ffd;

int dir_error_code;

/////////////////////////////////////////////////////////////////////////////
// CConnManDlg dialog


CConnManDlg::CConnManDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnManDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnManDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConnManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnManDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnManDlg, CDialog)
	//{{AFX_MSG_MAP(CConnManDlg)
	ON_BN_CLICKED(IDC_CREATE_PROFILE, OnCreateProfileBtn)
	ON_LBN_SELCHANGE(IDC_PROFILE_LIST, OnProfileListSelection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnManDlg message handlers

BOOL CConnManDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadProfileList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnManDlg::OnOK() 
{
	char* server = "";
	CListBox* profileList = (CListBox*)GetDlgItem(IDC_PROFILE_LIST);
	CMainDlg* parent = (CMainDlg*)AfxGetMainWnd();
	char profile[256];
	profileList->GetText(profileList->GetCurSel(), profile);
	if(dir_error_code == 0 && profileList->GetCount() > 0) {
		CDialog::OnOK();
		parent->LoadProfileSettings(profile);
		return;
	} else {
		char dir_path[460];
		CIRCApplication* app = (CIRCApplication*)app;
		sprintf(dir_path, app->GetAppPath());
		if(app->CheckIsWin32s() == TRUE) {
			strcat(dir_path, "\\PROFILES");
		} else {
			strcat(dir_path, "\\profiles");
		}
		char address[640] = {0};
		OPENFILENAME ofna = {0};
		ofna.lStructSize = sizeof(OPENFILENAME);
		ofna.lpstrInitialDir = dir_path;
		ofna.lpstrFile = address;
		ofna.nMaxFile = 640;
		ofna.lpstrFilter = "Config files (*.ini, *.cfg)\0*.ini;*.cfg\0All files\0*.*";
		ofna.Flags |= OFN_FILEMUSTEXIST;
		if(GetOpenFileName(&ofna)) {
			sprintf(address, ofna.lpstrFile);
			parent->LoadProfileSettingsF(address);	
		}
	}
	CDialog::OnOK();
}

void CConnManDlg::LoadProfileList() {
	char dir_path[460];
	char error_msg[1024];
	CIRCApplication* app = (CIRCApplication*)app;
	sprintf(dir_path, app->GetAppPath());
	if(app->CheckIsWin32s() == TRUE) {
		strcat(dir_path, "\\PROFILES");
	} else {
		strcat(dir_path, "\\profiles");
	}
	if(CreateDirectory(dir_path, NULL) > 0 || GetLastError() == ERROR_ALREADY_EXISTS) {
		CListBox* profileList = (CListBox*)GetDlgItem(IDC_PROFILE_LIST);
		HANDLE hFindProfiles = INVALID_HANDLE_VALUE;
		char folder_list_path[460];
		sprintf(folder_list_path, "%s\\*.ini", dir_path);
		hFindProfiles = FindFirstFile(folder_list_path, &ffd);
		CString strText = "";
		int items_count;
		if(hFindProfiles != INVALID_HANDLE_VALUE) {
			try {
				items_count++;
				do {
					if(strText.GetLength() > 4) {
						strText.Format("%s", ffd.cFileName);
						profileList->AddString(strText.Left(strText.GetLength() - 4));
						items_count++;
					}
				} while (FindNextFile(hFindProfiles, &ffd) != 0);
				FindClose(hFindProfiles);
			} catch(...) {

			}
		}
		if(profileList->GetCount() > 0) {
			CButton* ok_btn = (CButton*)GetDlgItem(IDOK);
			ok_btn->EnableWindow(FALSE);
		}
	} else {
		dir_error_code = GetLastError();
		sprintf(error_msg, "Invalid directory path.\r\n\r\nPath: %s\r\nError code: %d", 
			dir_path, dir_error_code);
		MessageBox(error_msg, "Error", MB_OK|MB_ICONSTOP);
	}
	
}

void CConnManDlg::OnCreateProfileBtn() 
{
	CTextBoxDlg textBoxDlg;
	textBoxDlg.SetAction(0);
	textBoxDlg.DoModal();
}

void CConnManDlg::OnProfileListSelection() 
{
	CButton* ok_btn = (CButton*)GetDlgItem(IDOK);
	ok_btn->EnableWindow(TRUE);
}
