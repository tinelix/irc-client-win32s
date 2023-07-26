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
				"\r\nCopyright � 2023 Dmitry Tretyakov (aka. Tinelix)."
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
		char prefix[80];
		char command[60];
		char params[256];
		char body[1536];
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
			if(strcmp(command, "372") == 0) {
				sprintf(parsed_line, "[MOTD] %s\r\n", body);
			} else if(strcmp(command, "396") == 0) {
				sprintf(parsed_line, "[396] **%s** %s\r\n", params, body);
			} else if(strcmp(command, "001") == 0) {
				sprintf(parsed_line, "[001] %s\r\n", body);
			} else if(strcmp(command, "002") == 0) {
				sprintf(parsed_line, "[002] %s\r\n", body);
			} else if(strcmp(command, "003") == 0) {
				sprintf(parsed_line, "[003] %s\r\n", body);
			} else if(strcmp(command, "004") == 0) {
				sprintf(parsed_line, "[004] %s\r\n", body);
			} else if(strcmp(command, "005") == 0) {
				sprintf(parsed_line, "[005] %s\r\n", body);
			} else if(strcmp(command, "End") == 0) {
				sprintf(parsed_line, "-------------------------------\r\n");
			} else if(strcmp(prefix, "ERROR") == 0) {
				sprintf(parsed_line, "[%s] %s %s\r\n", prefix, command, body);
			} else if(strlen(command) == 3 && isdigit(command[0]) != 0 
				&& isdigit(command[1]) != 0 && isdigit(command[2]) != 0) {
				sprintf(parsed_line, "[%s] %s %s\r\n", command, params, body);
			} else {
				sprintf(parsed_line, "[%s] %s\r\n", command, body);
			} 
		} else if(spaces > 0) {
			sprintf(parsed_line, "[RAW] [%s]\r\n", original_line);
		} else {
			sprintf(parsed_line, "[Parsing error | Size: %d]\r\n", spaces);
		}
		return parsed_line;
	} catch(...) {
		sprintf(parsed_line, "[Parsing error]\r\n");
		return parsed_line;
	}
}

EXPORT char* CALLBACK ParsePacket(char* packet) {
	char* line = "";
	char* token = "";
	char* debug_parsed_line = "";
	int lines_count = 0;
	int line_index = 0;
	char* lines[80];
	char parsed_packet[8192];
	char* token_s = "";

	if(packet != NULL && packet[0] >= 0) {
		token = strtok(packet, "\r\n");

		while(token != NULL) {
			lines[lines_count++] = ParseLine(token);
			token = strtok(NULL, "\r\n");
		}
		
		for(int i = 0; i < lines_count; i++) {
			if(line_index == 0) {
				line_index = sprintf(parsed_packet, lines[i]);
			} else {
				line_index += sprintf(parsed_packet + line_index, lines[i]);
			}
		}
	} else {
		sprintf(parsed_packet, "[IRC Parser] Parsing Error\r\n");
	}
	return parsed_packet;
}