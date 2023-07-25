// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\Tinelix IRC.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

void CProgressDlg::SetStatus(CString status) {
	CWnd* status_label = (CWnd*)GetDlgItem(IDC_STATUS);
	status_label->SetWindowText(status);
}

void CProgressDlg::SetProgress(int value) {
	CProgressCtrl* status_label = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
	status_label->SetPos(value);
}

void CProgressDlg::OnOK() 
{
	//CDialog::OnOK();
}

void CProgressDlg::Close() {
	CDialog::OnOK();
}

void CProgressDlg::OnCancel() 
{	
	//CDialog::OnCancel();
}

BOOL CProgressDlg::DestroyWindow() 
{	
	return CDialog::DestroyWindow();
}

void CProgressDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);	
}

void CProgressDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}
