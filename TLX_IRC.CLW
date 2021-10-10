; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SettingsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TLX_IRC.h"

ClassCount=9
Class1=IRCClient
Class2=MainWindow
Class3=CAboutDlg

ResourceCount=8
Resource1=IDR_MAINMENU
Resource2=IDR_MAINFRAME
Resource3=IDD_MAINWINDOW
Resource4=IDR_MENU1
Class4=ConnectionManagerDialog
Resource5=IDD_CONNMAN
Resource6=IDD_EDITTEXT
Class5=EnterTextDlg
Class6=ProfileMainPage
Class7=ProfileTabs
Class8=ProfileConnectionPage
Resource7=IDD_ABOUTBOX
Class9=SettingsDialog
Resource8=IDD_SETTINGS

[CLS:IRCClient]
Type=0
HeaderFile=TLX_IRC.h
ImplementationFile=TLX_IRC.cpp
Filter=N

[CLS:MainWindow]
Type=0
HeaderFile=mainwin.h
ImplementationFile=mainwin.cpp
Filter=D
LastObject=MainWindow
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=mainwin.h
ImplementationFile=mainwin.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_PROGRAM_NAME,static,1342308352
Control4=IDC_COPYRIGHT,static,1342308352
Control5=IDC_WIN32S_EDITION,static,1342308352
Control6=IDC_TECHINFO,button,1342177287
Control7=IDC_WINVER_LABEL,static,1342308352
Control8=IDC_WINVER,static,1342308352
Control9=IDC_LICENSE_NOTIFICATION,static,1342308353
Control10=IDC_GITHUB_REPO_LINK,static,1342308354

[MNU:IDR_MAINMENU]
Type=1
Command1=ID_FILE_CONNECT
Command2=ID_FILE_QUIT
Command3=ID_VIEW_SETTINGS
Command4=ID_HELP_ABOUT
CommandCount=4

[DLG:IDD_MAINWINDOW]
Type=1
Class=MainWindow
ControlCount=3
Control1=IDC_SOCKMSGS,edit,1352730692
Control2=IDC_MSGTEXT,edit,1484849280
Control3=IDC_SENDMSG,button,1476460544

[CLS:ConnectionManagerDialog]
Type=0
HeaderFile=cnmandlg.h
ImplementationFile=cnmandlg.cpp
Filter=D
LastObject=IDC_DELETE_PROFILE_BTn
VirtualFilter=dWC

[DLG:IDD_CONNMAN]
Type=1
Class=ConnectionManagerDialog
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LANGLABEL,static,1342308352
Control4=IDC_LANGCOMBO1,combobox,1344340227
Control5=IDC_PROFILES_GROUP,button,1342177287
Control6=IDC_PROFILELIST,listbox,1352728835
Control7=IDC_ADD_PROFILE_BTN,button,1342242816
Control8=IDC_CONNECT_PROFILE_BTN,button,1476460544
Control9=IDC_CHANGE_PROFILE_BTN,button,1476460544
Control10=IDC_DELETE_PROFILE_BTn,button,1476460544

[DLG:IDD_EDITTEXT]
Type=1
Class=EnterTextDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ENTERTEXTEDIT,edit,1350631552
Control4=IDC_ENTERTEXTLABEL,static,1342308352

[CLS:EnterTextDlg]
Type=0
HeaderFile=entertxt.h
ImplementationFile=entertxt.cpp
Filter=D
VirtualFilter=dWC
LastObject=EnterTextDlg

[CLS:ProfileMainPage]
Type=0
HeaderFile=profmnp.h
ImplementationFile=profmnp.cpp
Filter=D
LastObject=ProfileMainPage

[MNU:IDR_MENU1]
Type=1
Command1=ID_FILE_CONNECT
Command2=ID_FILE_QUIT
Command3=ID_HELP_ABOUT
CommandCount=3

[CLS:ProfileTabs]
Type=0
HeaderFile=proftabs.h
ImplementationFile=proftabs.cpp
Filter=W
LastObject=ProfileTabs

[CLS:ProfileConnectionPage]
Type=0
HeaderFile=profcnp.h
ImplementationFile=profcnp.cpp
Filter=D
LastObject=ProfileConnectionPage

[DLG:IDD_SETTINGS]
Type=1
Class=SettingsDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LANGLABEL,static,1342308352
Control4=IDC_LANGCOMBO1,combobox,1344340227
Control5=IDC_SAVE_MSG_HISTORY,button,1342242819
Control6=IDC_CHANGE_MSG_FONT,button,1342242816

[CLS:SettingsDialog]
Type=0
HeaderFile=setgdlg.h
ImplementationFile=setgdlg.cpp
Filter=D
LastObject=IDC_CHANGE_MSG_FONT
VirtualFilter=dWC

