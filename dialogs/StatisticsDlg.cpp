// StatisticsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\Tinelix IRC.h"
#include "MainDlg.h"
#include "StatisticsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

HINSTANCE wsaWrapper;
struct NetworkStatistics {
		int packets_read;
		int packets_sent;
		int total_bytes_sent;
		int total_bytes_read;
	} NetworkStats;
typedef NetworkStatistics (WINAPI *GetNetworkStatistics) ();
NetworkStatistics stats;
GetNetworkStatistics GetNetworkStats;


/////////////////////////////////////////////////////////////////////////////
// CStatisticsDlg message handlers

BOOL CStatisticsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticsDlg::SetWSAWrapper(HINSTANCE wrapper) {
	wsaWrapper = wrapper;
	if(wsaWrapper) {
		GetNetworkStats = (GetNetworkStatistics)GetProcAddress(wsaWrapper, MAKEINTRESOURCE(21));
		stats = (NetworkStatistics)(*GetNetworkStats)();
		SetStatisticsData(stats);
		SetTimer(0x8A001, 1000, (TIMERPROC)NULL);
	}
}

void CStatisticsDlg::SetStatisticsData(NetworkStatistics stats) {
	CWnd* packets_sent_counter = (CWnd*)GetDlgItem(IDC_PACKETS_SENT_VALUE);
	CWnd* packets_read_counter = (CWnd*)GetDlgItem(IDC_PACKETS_READ_VALUE);

	CWnd* bytes_sent_counter = (CWnd*)GetDlgItem(IDC_BYTES_SENT_VALUE);
	CWnd* bytes_read_counter = (CWnd*)GetDlgItem(IDC_BYTES_READ_VALUE);
	CWnd* total_bytes_counter = (CWnd*)GetDlgItem(IDC_TOTAL_BYTES_VALUE);

	CString packets_sent = CString("");
	CString packets_read = CString("");
	CString bytes_sent = CString("");
	CString bytes_read = CString("");
	CString total_bytes = CString("");

	packets_sent.Format("%d packet(s)", stats.packets_sent);
	packets_read.Format("%d packet(s)", stats.packets_read);
	
	if(stats.total_bytes_sent > 1024 || stats.total_bytes_read > 1024) {
		bytes_sent.Format("%.2f kB", (float)(stats.total_bytes_sent / 1024));
		bytes_read.Format("%.2f kB", (float)(stats.total_bytes_read / 1024));
		total_bytes.Format("%.2f kB", (float)((stats.total_bytes_sent + stats.total_bytes_read) / 1024));
	} else {
		bytes_sent.Format("%d bytes", stats.total_bytes_sent);
		bytes_read.Format("%d bytes", stats.total_bytes_read);
		total_bytes.Format("%d bytes", stats.total_bytes_sent + stats.total_bytes_read);
	}

	packets_sent_counter->SetWindowText(packets_sent);
	packets_read_counter->SetWindowText(packets_read);
	
	bytes_read_counter->SetWindowText(bytes_read);
	bytes_sent_counter->SetWindowText(bytes_sent);
	total_bytes_counter->SetWindowText(total_bytes);
}

void CStatisticsDlg::SetConnectionQuality(int ping_value) {
	CString quality_percent = CString("");
	int reserve_value = 10000 - ping_value;
	if(reserve_value < 0) {
		reserve_value = -reserve_value;
		TRACE("Value: %d", reserve_value);
	}
	int ping_strength = reserve_value / 100;
	CProgressCtrl* ping_strength_progress = (CProgressCtrl*)GetDlgItem(IDC_PING_STRENGTH);
	ping_strength_progress->SetPos(ping_strength);
	CWnd* ping_strength_counter = GetDlgItem(IDC_CONNQUALITY_VALUE);
	quality_percent.Format("%d%%", ping_strength);
	ping_strength_counter->SetWindowText(quality_percent);

}

void CStatisticsDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 0x8A001) {
		if(wsaWrapper) {
			GetNetworkStats = (GetNetworkStatistics)GetProcAddress(wsaWrapper, MAKEINTRESOURCE(21));
			stats = (NetworkStatistics)(*GetNetworkStats)();
			SetStatisticsData(stats);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}
