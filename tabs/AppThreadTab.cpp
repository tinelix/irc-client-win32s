//  appthreadtab.cpp : implementation file
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
#include "..\dialogs\MainDlg.h"
#include "AppThreadTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppThreadTab dialog


CAppThreadTab::CAppThreadTab(CWnd* pParent /*=NULL*/)
	: CDialog(CAppThreadTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppThreadTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAppThreadTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppThreadTab)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppThreadTab, CDialog)
	//{{AFX_MSG_MAP(CAppThreadTab)
	ON_BN_CLICKED(IDC_CHAT_SEND_MSG, OnChatSendMsg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppThreadTab message handlers

void CAppThreadTab::OnChatSendMsg() 
{
	CMainDlg mainDlg;
	CEdit* chat_output = (CEdit*)GetDlgItem(IDC_CHAT_OUTPUT);
	CString message;
	chat_output->GetWindowText(message);
	if(message.GetLength() > 0) {
		mainDlg.SendIRCMessage();
	}
	
}

void CAppThreadTab::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect rect;

	GetWindowRect(&rect);

	CEdit* chat_input = (CEdit*)GetDlgItem(IDC_CHAT_INPUT);
	CEdit* chat_output = (CEdit*)GetDlgItem(IDC_CHAT_OUTPUT);
	CButton* chat_send_message = (CButton*)GetDlgItem(IDC_CHAT_SEND_MSG);
	if(chat_input != NULL) {
		chat_input->MoveWindow(6, 5, rect.Width() - 12, rect.Height() - 38);
		chat_output->MoveWindow(6, rect.Height() - 28, rect.Width() - 78, 23);
		chat_send_message->MoveWindow(rect.Width() - 68, rect.Height() - 29, 63, 24);
	}
	
}

void CAppThreadTab::OnOK() 
{
	OnChatSendMsg();
	
	//CDialog::OnOK();
}

void CAppThreadTab::OnCancel() 
{
	
	//CDialog::OnCancel();
}
