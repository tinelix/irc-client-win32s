// StatisticsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\Tinelix IRC.h"
#include "StatisticsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef NetworkStatistics (WINAPI *GetNetworkStatistics) ();

GetNetworkStatistics GetNetworkStats;

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDlg dialog


CStatisticsDlg::CStatisticsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticsDlg, CDialog)
	//{{AFX_MSG_MAP(CStatisticsDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HINSTANCE wsaWrap;

/////////////////////////////////////////////////////////////////////////////
// CStatisticsDlg message handlers

BOOL CStatisticsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();


	SetTimer(0x8A001, 1000, (TIMERPROC)NULL);

	GetNetworkStats = (GetNetworkStatistics)GetProcAddress(wsaWrap, MAKEINTRESOURCE(21));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticsDlg::SetWSAWrapper(HINSTANCE wrapper) {
	wsaWrap = wrapper;
}

void CStatisticsDlg::SetStatisticsData(NetworkStatistics stats) {
	CWnd* packets_sent_counter = (CWnd*)GetDlgItem(IDC_PACKETS_SENT_VALUE);
	CWnd* packets_read_counter = (CWnd*)GetDlgItem(IDC_PACKETS_READ_VALUE);

	CWnd* bytes_sent_counter = (CWnd*)GetDlgItem(IDC_BYTES_READ_VALUE);
	CWnd* bytes_read_counter = (CWnd*)GetDlgItem(IDC_BYTES_SEND_VALUE);
	CWnd* total_bytes_counter = (CWnd*)GetDlgItem(IDC_TOTAL_BYTES_VALUE);

	CString packets_sent = CString("");
	CString packets_read = CString("");
	CString bytes_sent = CString("");
	CString bytes_read = CString("");
	CString total_bytes = CString("");

	packets_sent.Format("%d", stats.packets_sent);
	packets_read.Format("%d", stats.packets_read);
	bytes_sent.Format("%d", stats.total_send_bytes);
	bytes_read.Format("%d", stats.total_read_bytes);
	total_bytes.Format("%d", stats.total_send_bytes + stats.total_read_bytes);

	bytes_sent_counter->SetWindowText(packets_sent);
	bytes_read_counter->SetWindowText(packets_read);
	
	bytes_read_counter->SetWindowText(bytes_read);
	bytes_sent_counter->SetWindowText(bytes_sent);
	total_bytes_counter->SetWindowText(total_bytes);
}

void CStatisticsDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 0x8A001) {
		if(wsaWrap) {
			NetworkStatistics stats;
			stats = (NetworkStatistics)(*GetNetworkStats)();
			SetStatisticsData(stats);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}
