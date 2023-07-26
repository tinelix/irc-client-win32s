// appthreadtab.cpp : implementation file
//

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
	mainDlg.SendIRCMessage();
	
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
		chat_input->MoveWindow(6, 3, rect.Width() - 12, rect.Height() - 34);
		chat_output->MoveWindow(6, rect.Height() - 26, rect.Width() - 78, 23);
		chat_send_message->MoveWindow(rect.Width() - 68, rect.Height() - 27, 63, 24);
	}
	
}
