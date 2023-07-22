; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tinelix IRC.h"

ClassCount=3
Class1=CIRCApplication
Class2=CMainDlg

ResourceCount=11
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_TINELIXIRC_DIALOG
Resource4=IDD_ABOUTBOX
Resource5=IDR_MAINMENU
Resource6=IDR_MAINMENU (English (U.S.))
Resource7=IDD_TABCHAT (English (U.S.))
Resource8=IDD_TABTHREAD
Resource9=IDD_TABCHAT
Resource10=IDD_TABTHREAD (English (U.S.))
Class3=CAboutDlg
Resource11=IDD_MAINDIALOG (English (U.S.))

[CLS:CIRCApplication]
Type=0
HeaderFile=Tinelix IRC.h
ImplementationFile=Tinelix IRC.cpp
Filter=N

[CLS:CMainDlg]
Type=0
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
Filter=D
LastObject=CMainDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TINELIXIRC_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMainDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINMENU (English (U.S.))]
Type=1
Command1=ID_FILE_CONNECT
Command2=ID_FILE_QUIT
Command3=ID_CHANNEL_JOIN
Command4=ID_CHANNEL_LEAVE
Command5=ID_HELP_ABOUT
CommandCount=5

[MNU:IDR_MAINMENU]
Type=1
Command1=ID_FILE_CONNECT
Command2=ID_FILE_QUIT
Command3=ID_CHANNEL_JOIN
Command4=ID_CHANNEL_LEAVE
Command5=ID_HELP_ABOUT
CommandCount=5

[DLG:IDD_MAINDIALOG (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_MAINDLG_TABS,SysTabControl32,1342177280

[DLG:IDD_TABTHREAD]
Type=1
ControlCount=3
Control1=IDC_THREAD_INPUT,edit,1352728644
Control2=IDC_THREAD_OUTPUT,edit,1350631424
Control3=IDC_THREAD_SEND_MSG,button,1342242816

[DLG:IDD_TABTHREAD (English (U.S.))]
Type=1
ControlCount=3
Control1=IDC_THREAD_INPUT,edit,1352728644
Control2=IDC_THREAD_OUTPUT,edit,1350631424
Control3=IDC_THREAD_SEND_MSG,button,1342242816

[DLG:IDD_TABCHAT]
Type=1
ControlCount=4
Control1=IDC_CHAT_INPUT,edit,1352728644
Control2=IDC_CHAT_OUTPUT,edit,1350631424
Control3=IDC_CHAT_SEND_MSG,button,1342242816
Control4=IDC_CHAT_MEMBERS,listbox,1352728835

[DLG:IDD_TABCHAT (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_CHAT_INPUT,edit,1352728644
Control2=IDC_CHAT_OUTPUT,edit,1350631424
Control3=IDC_CHAT_SEND_MSG,button,1342242816
Control4=IDC_CHAT_MEMBERS,listbox,1352728835

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg

