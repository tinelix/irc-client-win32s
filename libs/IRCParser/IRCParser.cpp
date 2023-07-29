//  Copyright © 2023 Dmitry Tretyakov (aka. Tinelix)
//  
//	Tinelix IRC Parser files is part of Tinelix IRC Client.
//
//  Tinelix IRC Client is free software: you can redistribute it and/or modify it under 
//  the terms of the GNU General Public License as published by the Free Software Foundation, 
//  either version 3 of the License, or (at your option) any later version.
//  Tinelix IRC Client is distributed in the hope that it will be useful, but WITHOUT ANY 
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
//  PARTICULAR PURPOSE.
//  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along with this
//  program. If not, see https://www.gnu.org/licenses/.
//
//  Source code: https://github.com/tinelix/irc-client-win32s

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
				"\r\nLicensed as part of Tinelix IRC Client under GPLv3."
				"\r\nSource code: "
				"https://github.com/tinelix/irc-client-win32s\r\n");
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
	char words[512][512];
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
				if(original_line[0] == ':') {
					sprintf(body, original_line + 
						strlen(prefix) + strlen(command) + strlen(params) + 5);
				} else {
					sprintf(body, original_line + 
						strlen(prefix) + strlen(command) + strlen(params) + 4);
				}
				sprintf(parsed_line, "[MOTD] %s\r\n", body);
			} else if(strcmp(command, "396") == 0) {
				sprintf(parsed_line, "[396] %s@%s\r\n", params, body);
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
				sprintf(parsed_line, "---------------------------------------------------\r\n");
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
			sprintf(parsed_line, "[Parsing error | "
				"Size: %d chars / %d spaces]\r\n", strlen(original_line), spaces);
		}
		return parsed_line;
	} catch(...) {
		sprintf(parsed_line, "[Parsing error]\r\n");
		return parsed_line;
	}
}

EXPORT char* CALLBACK ParsePacket(char original_packet[4096]) {
	char* packet = "";
	char* line = "";
	char* token = "";
	char debug_parsed_line[800];
	int lines_count = 0;
	int lines_index = 0;
	int parsed_lines_count = 0;
	char lines[64][4096];
	char parsed_lines[64][4096];
	char parsed_packet[4096];
	char* token_s = "";

	for(int i = 0; i < strlen(original_packet); i++) {
		if(original_packet[i] == '\r') {
			lines_count++;
			lines_index = 0;
		} else if(original_packet[i] == '\n') {
			
		} else {
			lines[lines_count][lines_index] = original_packet[i];
			lines_index++;
		}
	}

	for(int line_index = 0; line_index < lines_count; line_index++) {
		char* line = "";
		line = lines[line_index];
		if(line != NULL) {
			parsed_lines_count += 
				sprintf(parsed_packet + parsed_lines_count, 
				ParseLine(line));
		}
	}
	return parsed_packet;
}

EXPORT char* CALLBACK ParseSendingMessage(char* message, char* channel) {
	char line[4096];
	strcpy(line, message);
	char parsed_line[4096];
	char debug_parsed_line[4096];
	char words[512][256];
	if(message != NULL && message[0] >= 0) {
		try {
			char command[60];
			char params[4096];
			char body[4096];
			char* token = strtok(line, " ");
			int spaces = 0;
			int body_index;
			while(token != NULL) {
				if(spaces == 0) {
					sprintf(command, words[spaces]);
				} else if(spaces == 1) {
					sprintf(params, words[spaces]);
				} else if(spaces == 2) {
					sprintf(body, words[spaces]);
					body_index = strlen(body);
				} else {
					body_index += sprintf(body + body_index, " %s", words[spaces]);
				}
				token = strtok(NULL, " ");
				spaces++;
			}
			if(spaces > 2) {
				if(strcmp(command, "/join") == 0 || strcmp(command, "/JOIN") == 0) {
					sprintf(parsed_line, "JOIN %s\r\n", params);
				} else if(strcmp(command, "/privmsg") == 0 
					|| strcmp(command, "/PRIVMSG") == 0) {
					sprintf(parsed_line, "PRIVMSG %s :%s\r\n", params, body);
				}
			} else {
				if(strlen(channel) > 0 && channel[0] >= 0) {
					sprintf(parsed_line, "PRIVMSG %s :%s\r\n", channel, message);
				} else {
					sprintf(parsed_line, "%s\r\n", message + 1);
				}
			}
		
		} catch(...) {

		}
	}
	return parsed_line;
}
