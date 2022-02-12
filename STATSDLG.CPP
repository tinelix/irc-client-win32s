// statsdlg.cpp : implementation file
//

#include "stdafx.h"
#include "TLX_IRC.h"
#include "statsdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StatisticsDialog dialog


StatisticsDialog::StatisticsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(StatisticsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(StatisticsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void StatisticsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StatisticsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StatisticsDialog, CDialog)
	//{{AFX_MSG_MAP(StatisticsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// StatisticsDialog message handlers

void StatisticsDialog::delsymbs(char *str, int begin, int lng)
{
	for(begin; begin < strlen(str); begin++) {
		*(str + begin) = 0;	
	};
};

BOOL StatisticsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	sended_bytes_count = 0;
	recieved_bytes_count = 0;
	
	char exe_path[MAX_PATH] = {0};
	char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

	GetModuleFileName(NULL, exe_path, MAX_PATH);  

	*(strrchr(exe_path, '\\')+1)='\0';

	strcat(exe_path, "settings.ini");	// add settings filename

	char language_string[MAX_PATH] = {0};
	GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
	CString lng_selitemtext_2(language_string);
	char sended_bytes_value[128];
	char recieved_bytes_value[128];
	char total_bytes_value[128];
	int total_bytes_count;
	total_bytes_count = sended_bytes_count + recieved_bytes_count;
	mainfont.CreateFont(8, 0, 0, 0, FW_REGULAR, FALSE, FALSE, 0, DEFAULT_CHARSET, 0, 0, 
	0, 0, "MS Sans Serif");
	GetDlgItem(IDC_TRAFFIC_GROUP)->SetFont(&mainfont);
	GetDlgItem(IDC_SENDED_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_RECIEVED_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_TOTAL_LABEL)->SetFont(&mainfont);
	GetDlgItem(IDC_SENDED_LABEL2)->SetFont(&mainfont);
	GetDlgItem(IDC_RECIEVED_LABEL2)->SetFont(&mainfont);
	GetDlgItem(IDC_TOTAL_LABEL2)->SetFont(&mainfont);
	GetDlgItem(IDOK)->SetFont(&mainfont);
	mainfont.Detach();
	if(lng_selitemtext_2 == "Russian") {
		SetWindowText("Статистика");
		GetDlgItem(IDC_TRAFFIC_GROUP)->SetWindowText("Трафик");
		GetDlgItem(IDC_SENDED_LABEL)->SetWindowText("Отправлено:");
		GetDlgItem(IDC_RECIEVED_LABEL)->SetWindowText("Получено:");
		GetDlgItem(IDC_TOTAL_LABEL)->SetWindowText("Итого:");
		sprintf(sended_bytes_value, "%d байт", sended_bytes_count);
		sprintf(recieved_bytes_value, "%d байт", recieved_bytes_count);
		sprintf(total_bytes_value, "%d байт", total_bytes_count);
	} else {
		SetWindowText("Statistics");
		GetDlgItem(IDC_TRAFFIC_GROUP)->SetWindowText("Traffic");
		GetDlgItem(IDC_SENDED_LABEL)->SetWindowText("Sended:");
		GetDlgItem(IDC_RECIEVED_LABEL)->SetWindowText("Recieved:");
		GetDlgItem(IDC_TOTAL_LABEL)->SetWindowText("Total:");
		sprintf(sended_bytes_value, "%d bytes", sended_bytes_count);
		sprintf(recieved_bytes_value, "%d bytes", recieved_bytes_count);	
		sprintf(total_bytes_value, "%d bytes", total_bytes_count);
	};

	GetDlgItem(IDC_SENDED_LABEL2)->SetWindowText(sended_bytes_value);
	GetDlgItem(IDC_RECIEVED_LABEL2)->SetWindowText(recieved_bytes_value);
	GetDlgItem(IDC_TOTAL_LABEL2)->SetWindowText(total_bytes_value);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT StatisticsDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_UPDATING_STATISTICS) {
		IRC_STATS* irc_stats = (IRC_STATS*)lParam;
		sended_bytes_count = sended_bytes_count + irc_stats->sended_bytes;
		recieved_bytes_count = recieved_bytes_count + irc_stats->recieved_bytes;
		char exe_path[MAX_PATH] = {0};
		char exe_name[MAX_PATH] = "TLX_IRC.EXE"; // EXE filename

		GetModuleFileName(NULL, exe_path, MAX_PATH);  

		*(strrchr(exe_path, '\\')+1)='\0';

		strcat(exe_path, "settings.ini");	// add settings filename

		char language_string[MAX_PATH] = {0};
		GetPrivateProfileString("Main", "Language", "English", language_string, MAX_PATH, exe_path);
		CString lng_selitemtext_2(language_string);
		char sended_bytes_value[128];
		char recieved_bytes_value[128];
		char total_bytes_value[128];
		int total_bytes_count;
		total_bytes_count = irc_stats->sended_bytes + irc_stats->recieved_bytes;
		if(lng_selitemtext_2 == "Russian") {
			SetWindowText("Статистика");
			GetDlgItem(IDC_TRAFFIC_GROUP)->SetWindowText("Трафик");
			GetDlgItem(IDC_SENDED_LABEL)->SetWindowText("Отправлено:");
			GetDlgItem(IDC_RECIEVED_LABEL)->SetWindowText("Получено:");
			GetDlgItem(IDC_TOTAL_LABEL)->SetWindowText("Итого:");
			if(irc_stats->sended_bytes >= 1048576) {
				sprintf(sended_bytes_value, "%.2f МБ", (double)irc_stats->sended_bytes / 1048576);
			} else if(irc_stats->sended_bytes >= 1024) {
				sprintf(sended_bytes_value, "%.2f кБ", (double)irc_stats->sended_bytes / 1024);
			} else {
				sprintf(sended_bytes_value, "%d байт", sended_bytes_count);
			};
			if(irc_stats->recieved_bytes >= 1048576) {
				sprintf(recieved_bytes_value, "%.2f МБ", (double)irc_stats->recieved_bytes / 1048576);
			} else if(irc_stats->recieved_bytes >= 1024) {
				sprintf(recieved_bytes_value, "%.2f кБ", (double)irc_stats->recieved_bytes / 1024);
			} else {
				sprintf(recieved_bytes_value, "%d байт", irc_stats->recieved_bytes);
			};
			if(total_bytes_count >= 1048576) {
				sprintf(total_bytes_value, "%.2f МБ", (double)total_bytes_count / 1048576);
			} else if(total_bytes_count >= 1024) {
				sprintf(total_bytes_value, "%.2f кБ", (double)total_bytes_count / 1024);
			} else {
				sprintf(total_bytes_value, "%d байт", total_bytes_count);
			};
		} else {
			SetWindowText("Statistics");
			GetDlgItem(IDC_TRAFFIC_GROUP)->SetWindowText("Traffic");
			GetDlgItem(IDC_SENDED_LABEL)->SetWindowText("Sended:");
			GetDlgItem(IDC_RECIEVED_LABEL)->SetWindowText("Recieved:");
			GetDlgItem(IDC_TOTAL_LABEL)->SetWindowText("Total:");
			if(irc_stats->sended_bytes >= 1048576) {
				sprintf(sended_bytes_value, "%.2f MB", (double)irc_stats->sended_bytes / 1048576);
			} else if(irc_stats->sended_bytes >= 1024) {
				sprintf(sended_bytes_value, "%.2f kB", (double)irc_stats->sended_bytes / 1024);
			} else {
				sprintf(sended_bytes_value, "%d bytes", irc_stats->sended_bytes);
			};
			if(irc_stats->recieved_bytes >= 1048576) {
				sprintf(recieved_bytes_value, "%.2f MB", (double)irc_stats->recieved_bytes / 1048576);
			} else if(irc_stats->recieved_bytes >= 1024) {
				sprintf(recieved_bytes_value, "%.2f kB", (double)irc_stats->recieved_bytes / 1024);
			} else {
				sprintf(recieved_bytes_value, "%d bytes", irc_stats->recieved_bytes);	
			};
			if(total_bytes_count >= 1048576) {
				sprintf(total_bytes_value, "%.2f MB", (double)total_bytes_count / 1048576);
			} else if(total_bytes_count >= 1024) {
				sprintf(total_bytes_value, "%.2f kB", (double)total_bytes_count / 1024);
			} else {
				sprintf(total_bytes_value, "%d bytes", total_bytes_count);
			};
		};
		GetDlgItem(IDC_SENDED_LABEL2)->SetWindowText(sended_bytes_value);
		GetDlgItem(IDC_RECIEVED_LABEL2)->SetWindowText(recieved_bytes_value);
		GetDlgItem(IDC_TOTAL_LABEL2)->SetWindowText(total_bytes_value);
	};
	
	return CDialog::WindowProc(message, wParam, lParam);
}
