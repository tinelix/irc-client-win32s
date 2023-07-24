#include <windows.h>
#include <stdio.h>
#include "IRCParser.h"

BOOL is_win32s;
int MAX_WORDS_COUNT = 512;

int WINAPI DllMain(HINSTANCE hInst, DWORD fdReas, PVOID pvRes) {
	switch(fdReas) {
		case DLL_PROCESS_ATTACH:
			// Checking if it's Win32s
			if(GetVersion() & 0x80000000 && (GetVersion() & 0xFF) == 3) {
				is_win32s = TRUE;
			} else {
				is_win32s = FALSE;
			}
			if(!is_win32s) {
				OutputDebugString("\r\nTinelix IRC Parser - Win32 DLL"
				"\r\nCopyright © 2023 Dmitry Tretyakov (aka. Tinelix)."
				"\r\nLicensed as part of Tinelix IRC under GPLv3."
				"\r\nSource code: "
				"https://github.com/tinelix/irc-client-win32s/tree/alpha/libs/IRCParser\r\n");
			}
			break;
		case DLL_PROCESS_DETACH:
			if(!is_win32s) {
				OutputDebugString("\r\nIRC Parser is shutting down...\r\n");
			}
			break;

	}
	
	return TRUE;
}

EXPORT char* CALLBACK ParseLine(char* original_line) {
	char* line = original_line;
	char* parsed_line = "";
	char* debug_parsed_line = "";
	try {
		char prefix[256], command[12], params[40], body[512];
		sscanf(line, "%255s", prefix);
		if(prefix == "ERROR") {
			sscanf(line, "%*s %511[^\n]", body);
			sprintf(debug_parsed_line, "\r\n[IRC Parser] [%s] %s", prefix, body);
			sprintf(parsed_line, "[%s] %s\r\n", prefix, body);
		} else {
			sscanf(line, "%*s %11s %39s :%511[^\n]", command, params, body);
			sprintf(debug_parsed_line, "\r\n[IRC Parser] [%s] %s", command, body);
			sprintf(parsed_line, "[%s] %s\r\n", command, body);
		}
		return parsed_line;
	} catch(...) {
		sprintf(line, "[Parsing error]");
		return line;
	}
}

EXPORT char* CALLBACK ParsePacket(char* packet) {
	if(!is_win32s) {
		OutputDebugString("\r\n[IRC Parser] Parsing IRC packet...");
	}
	char* line = "";
	char* token = "";
	char* debug_parsed_line = "";
	int lines_count = 0;
	int line_index = 0;
	char* lines[80];
	char* parsed_packet = "";
	char* token_s = "";

	if(packet != NULL && packet[0] >= 0) {
		token = strtok(packet, "\n");

		while(token != NULL) {
			sprintf(token_s, "%s\r\n", token);
			lines[lines_count++] = ParseLine(token_s);
			token = strtok(NULL, "\n");
		}
		
		for(int i = 0; i < lines_count - 1; i++) {
			line_index += sprintf(parsed_packet + line_index, "%s", lines[i]);
		}
		if(!is_win32s) {
			sprintf(debug_parsed_line, "\r\n[IRC Parser] Parsed!"
				"\r\n[IRC Parser] Before: [%s]"
				"\r\n[IRC Parser] After: [%s]", packet, parsed_packet); 
			OutputDebugString(debug_parsed_line);
		}
	} else {
		parsed_packet = "[IRC Parser] Parsing Error\r\n";
	}
	return parsed_packet;
}
