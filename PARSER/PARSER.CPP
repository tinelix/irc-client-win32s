#include "parser.h"

extern "C" BOOL WINAPI DllMain(HINSTANCE const instance, DWORD const reason, LPVOID const reserved) {

	switch (reason) {
		case DLL_PROCESS_ATTACH:
			char dllinfo[192];
			int dllinfo_index;
			dllinfo_index = sprintf(dllinfo_index + dllinfo, "Tinelix IRC Parser ver. %s\r\n", version_number);
			dllinfo_index += sprintf(dllinfo_index + dllinfo, 
			"Source code: https://github.com/tinelix/irc-client-for-win32s or "
			"https://github.com/tinelix/irc-client-for-windows. Licensed "
			"under GNU GPL 3.0.\r\n\r\n");
			OutputDebugString(dllinfo);
			break;
	}
	return TRUE;	
};


extern "C" __declspec(dllexport) void ParseMessage(char* line, char* array[], char* output, BOOL debug) {
	char msg[32768];
	if (line == NULL || output == NULL) {
		exit;
	};
	char* token;
	char* new_token;
	//OutputDebugString(line);
	int index = 0;
	int points_index = 0;
	int string_index = 0;
	char tr[32768];
	char code;
	char privmsg_code[32768];
	char join_code[32768];
	char digit[32];
	token = strtok(line, " ");
	array[index] = token;
	//new_token = strtok(line, " ");										   
	while(token != NULL) {
		if(token[0] == ':' && index < 4) {
			array[index++] = token + 1;
		} else {
			array[index++] = token;
		};
		token = strtok(NULL, " ");
	};

	for (int i = 0; i < index; i++) {
		if(i < 2 && strlen(array[i]) < 4) {
			if(strcmp(array[1], "PRIVMSG") == 0) {
				sprintf(privmsg_code, "PRIVMSG"); 
			};
			if(strcmp(array[1], "JOIN") == 0) {
				sprintf(join_code, "Join"); 
			};
			if(isdigit(code) == 0) {
				sprintf(&code, "%s", array[i]);
			};
		};
		//sprintf(digit, "IsDigit: %d\r\n", isdigit(code));
		if (debug == TRUE) {
			OutputDebugString("WORD: [");
			OutputDebugString(array[i]);
			OutputDebugString("]\r\n");
			char index_str[40];
			char length_str[40];
			sprintf(index_str, "INDEX: %d\r\n", i); 
			sprintf(length_str, "LENGTH: %d\r\n", index); 
			OutputDebugString(index_str);
			OutputDebugString(length_str);
			OutputDebugString("\r\n");
		};
		if(i == 0 && strcmp(array[1], "PRIVMSG") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PRIVMSG.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			string_index += sprintf(output + string_index, "%s ", array[i]);
		} else if(i == 2 && strcmp(array[1], "PRIVMSG") == 0) {
			if(array[i][0] != '#') {
				string_index += sprintf(output + string_index, "(direct):");
			} else {
				string_index += sprintf(output + string_index, "(#%s):", array[i] + 1);
			};
		} else if(i == 0 && strcmp(array[1], "JOIN") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is JOIN.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			string_index += sprintf(output + string_index, "%s joined on the ", array[i]);
		} else if(i == 0 && strcmp(array[1], "QUIT") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is QUIT.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(strlen(array[i]) < 3) {
				string_index += sprintf(output + string_index, "%s quited.\r\n", array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s quited with reason: [", array[i]);
			};
		} else if(i >= 2 && strcmp(array[1], "QUIT") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is QUIT.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(i > index - 2) {
				string_index += sprintf(output + string_index, "%s].\r\n", array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s ", array[i]);
			};
		} else if(i == 0 && strcmp(array[1], "PART") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PART.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			
				string_index += sprintf(output + string_index, "%s left the ", array[i]);
		} else if(i >= 3 && strcmp(array[1], "PART") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PART.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			if(i > index - 2) {
				string_index += sprintf(output + string_index, "%s].\r\n", array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s ", array[i]);
			};
		} else if(i == 2 && strcmp(array[1], "PART") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PART.");
				OutputDebugString("\r\n");
			};
			if(index <= 4) {
				string_index += sprintf(output + string_index, "%s channel.\r\n", array[i]);
			} else {
				string_index += sprintf(output + string_index, "%s channel with reason: [", array[i]);
			};
		} else if(i == 2 && strcmp(array[1], "JOIN") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is JOIN.");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "%s channel.\r\n", array[i]);
		} else if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0 && strcmp(array[1], "372") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is MOTD (372).");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "MOTD:");
		} else if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0 && strcmp(array[1], "372") != 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is digit.");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "Code %s:", array[i]);
		} else if (i > index - 2 && strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "QUIT") != 0 
			&& strcmp(array[1], "PART") != 0) {
			if (debug == TRUE) {
				OutputDebugString("Code isn't digit. (i > index - 2)");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, " %s\r\n", array[i]);

		} else {
			if (i >= 1 && i <= index - 2) {
				if ((strcmp(array[1], "PRIVMSG") == 0) && i == 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"PRIVMSG\") == 0) && i == 3)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if ((strcmp(array[1], "PRIVMSG") == 0) && i >= 4) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"PRIVMSG\") == 0) && i >= 4)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if ((strcmp(array[1], "372") == 0) && i == 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"372\") == 0) && i == 3)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if ((strcmp(array[1], "372") == 0) && i >= 4) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"372\") == 0) && i >= 4)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if (strcmp(array[1], "JOIN") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"JOIN\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "QUIT") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"QUIT\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if (strcmp(array[1], "PART") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"PART\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} else if ((i == 1 && isdigit(code) == 0) && strcmp(array[1], "PRIVMSG") != 0 
						&& strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "QUIT") != 0 && 
						strcmp(array[1], "PART") != 0 && strcmp(array[1], "372") != 0) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (i == 1 && isdigit(code) == 0 && strcmp(array[1], \"PRIVMSG\")\r\n"
						"!= 0 && strcmp(array[1], \"JOIN\") != 0 && strcmp(array[1], \"QUIT\") != 0 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, "%s", array[i]);
				} else if ((i > 1 && isdigit(code) == 0 && strcmp(array[1], "PRIVMSG") != 0 
					&& strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "QUIT") != 0 
					&& strcmp(array[1], "PART") != 0 && strcmp(array[1], "372") != 0)) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (i > 1 && isdigit(code) == 0 && strcmp(array[1], \"PRIVMSG\") != 0\r\n"
						"&& strcmp(array[1], \"JOIN\") != 0 && strcmp(array[1], \"QUIT\") != 0 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} else if (isdigit(code) > 0 && i >= 3 && strcmp(array[1], "372") != 0) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (isdigit(code) > 0 && i >= 3 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				};		
			};
		};
	};


	//try {
		//output = tr;
	//} catch(...) {

	//};
	
};

extern "C" __declspec(dllexport) void ParseNamesMessage(char* line, char* array[], char* owners_array[], 
char* operators_array[], char* members_array[], BOOL debug) {					  
	int owners_index = 0;
	int operators_index = 0;
	int members_index = 0;
	for (int index = 5; index < 32768; index++) {
		if(array[index] == "\0" || array[index] == NULL) {
			
		} else if(array[index][0] == ':' && array[index][1] == '~') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if owner): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			owners_array[owners_index++] = array[index] + 2;
		} else if(array[index][0] == ':' && array[index][1] == '@') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if operator): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			operators_array[operators_index++] = array[index] + 2;
		} else if(array[index][0] == '~') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if owner without \":\" mask): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			owners_array[owners_index++] = array[index] + 1;
		} else if(array[index][0] == '@') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if operator without \":\" mask): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			operators_array[operators_index++] = array[index] + 1;
		} else if(array[index][0] == ':') {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if member): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			members_array[members_index++] = array[index] + 1;
		} else {
			if (debug == TRUE) {
				OutputDebugString("Parsing NAMES messages (if member without \":\" mask): ");
				OutputDebugString(array[index]);
				OutputDebugString("\r\n");
			};
			members_array[members_index++] = array[index];
		};
	};
};

extern "C" __declspec(dllexport) void FreeArray() {

};
