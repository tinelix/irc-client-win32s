// ConnManDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\Tinelix IRC.h"
#include "MainDlg.h"
#include "ConnManDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnManDlg message handlers

void CConnManDlg::OnOK() 
{
	CMainDlg mainDlg;
	mainDlg.PrepareConnect("irc.tinelix.ru", 6667);
	
	CDialog::OnOK();
}
