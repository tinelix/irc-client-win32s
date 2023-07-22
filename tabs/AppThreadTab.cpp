// appthreadtab.cpp : implementation file
//

#include "stdafx.h"
#include "..\Tinelix IRC.h"
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
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppThreadTab message handlers
