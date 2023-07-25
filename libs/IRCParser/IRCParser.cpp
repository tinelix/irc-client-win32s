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
	char line[4096];
	strcpy(line, original_line);
	char parsed_line[4096];
	char debug_parsed_line[4096];
	char words[512][256];
	try {
		char prefix[60];
		char command[60];
		char params[256];
		char body[1024];
		char* token = strtok(line, " ");
		int spaces = 0;
		int body_index;
		while(token != NULL) {
			if(token[0] == ':') {
				sprintf(words[spaces], token + 1);
			} else {
				sprintf(words[spaces], token);
			}
			if(spaces == 0) {
				sprintf(prefix, words[spaces]);
			} else if(spaces == 1) {
				sprintf(command, words[spaces]);
			} else if(spaces == 2) {
				sprintf(params, words[spaces]);
			} else if(spaces == 3) {
				sprintf(body, words[spaces]);
				body_index = strlen(body);
			} else {
				body_index += sprintf(body + body_index, " %s", words[spaces]);
			}
			token = strtok(NULL, " ");
			spaces++;
		}
		if(spaces > 2) {
			sprintf(parsed_line, "[%s] %s\r\n", command, body);
		} else {
			sprintf(parsed_line, "[Parsing error]\r\n");
		}
		return parsed_line;
	} catch(...) {
		sprintf(parsed_line, "[Parsing error]\r\n");
		return parsed_line;
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
		token = strtok(packet, "\r\n");

		while(token != NULL) {
			lines[lines_count++] = ParseLine(token);
			token = strtok(NULL, "\r\n");
		}
		
		for(int i = 0; i < lines_count; i++) {
			if(line_index == 0) {
				parsed_packet = lines[i];
				line_index = strlen(parsed_packet);
			} else {
				strcpy(lines[i], parsed_packet);
			}
		}
	} else {
		parsed_packet = "[IRC Parser] Parsing Error\r\n";
	}
	return parsed_packet;
}
