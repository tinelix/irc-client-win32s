#include <winsock.h> 
#include <string.h>
#include "IRCClnt.h"
#include "Globals.h"
#include "resource.h"

char nicknames[256];
char password[20];
char realname[256];
char server[256];
char port[5];
SOCKET sock;

void CreateConnectionSession(char server[256], char port[5], HWND hWnd) { 
    SOCKADDR_IN client_param;
    HOSTENT* host;
    int conn_status;
    int wsa_async_result; 
    char connection_status[512];
    int connection_status_count = 0;
    /*GetPrivateProfileString("Main", "Nicknames", "", nicknames, 256, ini_path);
    GetPrivateProfileString("Main", "Password", "", password, 20, ini_path);
    GetPrivateProfileString("Main", "Realname", "", realname, 256, ini_path);*/
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == SOCKET_ERROR) {
    	char error_msg_text[512];
    	int error_code = WSAGetLastError();
    	sprintf(error_msg_text, "Could not start WinSock with error code: %d", error_code);
    	MessageBox(NULL, error_msg_text, "Error", MB_OK|MB_ICONSTOP); 
    	return;
    }
                          
    client_param.sin_family = AF_INET;

    connection_status_count = sprintf(connection_status, "Connecting to %s:%s...\r\n", server, port);                                                   
    SetWindowText(GetDlgItem(hWnd, IDC_MSGINPUT_EDIT), connection_status);
                          
    host = gethostbyname(server);
    if(host == NULL) {
    	if(WSAGetLastError() != 0) {
	    	connection_status_count += sprintf(connection_status + connection_status_count, "Failed to get the IP for this hostname.\r\nError code: %d (%s)", 
	        WSAGetLastError(), strerror(WSAGetLastError()));                                                   
	    	SetWindowText(GetDlgItem(hWnd, IDC_MSGINPUT_EDIT), connection_status);
	    	MessageBox(NULL, "Failed to get the IP for this hostname.", "Error", MB_OK|MB_ICONSTOP);
	    	return;
    	}
    } else {
        client_param.sin_addr.s_addr = inet_addr((char*)inet_ntoa(**(IN_ADDR**)host->h_addr_list));
    }        
    client_param.sin_port = htons(atoi(port));
    conn_status = connect(sock, (PSOCKADDR)&client_param, sizeof(client_param));  
    if(conn_status == SOCKET_ERROR || conn_status == INVALID_SOCKET) {
        char error_msg_text[512];
    	int error_code = WSAGetLastError();
		if(error_code == 10060) {
	    	connection_status_count += sprintf(connection_status + connection_status_count, "Connection timed out.\r\n", server, port);                                                   
	    	sprintf(error_msg_text, "Connection timed out.");
	    } else {
	    	connection_status_count += sprintf(connection_status + connection_status_count, "Connection failed with error code: %d (%s)\r\n", error_code, strerror(error_code));                                                   
	    	sprintf(error_msg_text, "Connection failed with error code: %d (%s)", error_code, strerror(error_code));
	    }
	    SetWindowText(GetDlgItem(hWnd, IDC_MSGINPUT_EDIT), connection_status);
	    MessageBox(NULL, error_msg_text, "Error", MB_OK|MB_ICONSTOP);
		return;
	}
	wsa_async_result = WSAAsyncSelect(sock, hWnd, WM_SOCKMSG, FD_READ|FD_WRITE);
	if(wsa_async_result > 0) {
	   	char error_msg_text[512];
    	int error_code = WSAGetLastError();
    	if(error_code == 10060) {
    		connection_status_count += sprintf(connection_status + connection_status_count, "Connection timed out.\r\n", server, port);                                                   
    		sprintf(error_msg_text, "Connection timed out.");
    	} else {                                                                
    		connection_status_count += sprintf(connection_status + connection_status_count, "Could not start WinSock with error code: %d (%s)\r\n",
    		error_code, strerror(error_code));
    		sprintf(error_msg_text, "Could not start WinSock with error code: %d (%s)", error_code, strerror(error_code));
    	} 
    	SetWindowText(GetDlgItem(hWnd, IDC_MSGINPUT_EDIT), connection_status);
    	MessageBox(NULL, error_msg_text, "Error", MB_OK|MB_ICONSTOP);
	}
}
