#include "parser.h"


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
	
	OutputDebugString("Parsing...\r\n");

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
			sprintf(index_str, "INDEX: %d\r\n", i); 
			OutputDebugString(index_str);
			OutputDebugString("\r\n");
		};
		if(i == 0 && strcmp(array[1], "PRIVMSG") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is PRIVMSG.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			string_index += sprintf(output + string_index, "%s ", array[i] + 1);
		} if(i == 2 && strcmp(array[1], "PRIVMSG") == 0) {
			string_index += sprintf(output + string_index, "(#%s):", array[i] + 1);
		} if (i > index - 2 && index == 4 && strcmp(array[1], "PRIVMSG") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code isn't digit. (i > index - 2 && index == 4)");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, " %s\r\n", array[i]);
		} if(i == 0 && strcmp(array[1], "JOIN") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is JOIN.");
				OutputDebugString("\r\n");
			};
			strtok(array[i], "!");
			string_index += sprintf(output + string_index, "%s joined on the ", array[i]);
		} if(i == 2 && strcmp(array[1], "JOIN") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is JOIN.");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "%s channel.\r\n", array[i] + 1);
		} if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0 && strcmp(array[1], "372") == 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is MOTD (372).");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "MOTD:");
		} if(i < 3 && strlen(array[i]) < 4 && isdigit(code) != 0 && strcmp(array[1], "372") != 0) {
			if (debug == TRUE) {
				OutputDebugString("Code is digit.");
				OutputDebugString("\r\n");
			};
			string_index += sprintf(output + string_index, "Code %s:", array[i]);
		} if (i > index - 2 && strcmp(array[1], "JOIN") != 0) {
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
				} if ((strcmp(array[1], "PRIVMSG") == 0) && i >= 4) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"PRIVMSG\") == 0) && i >= 4)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} if ((strcmp(array[1], "372") == 0) && i == 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"372\") == 0) && i == 3)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} if ((strcmp(array[1], "372") == 0) && i >= 4) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages ((strcmp(array[1], \"372\") == 0) && i >= 4)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} if (strcmp(array[1], "JOIN") == 0 && i >= 3) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (strcmp(array[1], \"JOIN\") == 0 && i >= 3)");
						OutputDebugString("\r\n");
					};
				} if (i == 1 && isdigit(code) == 0 && strcmp(array[1], "PRIVMSG") != 0
				  	  && strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "372") != 0) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (i == 1 && isdigit(code) == 0 && strcmp(array[1], \"PRIVMSG\")\r\n"
						"!= 0 && strcmp(array[1], \"JOIN\") != 0 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, "%s", array[i]);
				} if (i > 1 && isdigit(code) == 0 && strcmp(array[1], "PRIVMSG") != 0 
				  	  && strcmp(array[1], "JOIN") != 0 && strcmp(array[1], "372") != 0) {
					if (debug == TRUE) {
						OutputDebugString("Parsing messages (i > 1 && isdigit(code) == 0 && strcmp(array[1], \"PRIVMSG\") != 0\r\n"
						"&& strcmp(array[1], \"JOIN\") != 0 && strcmp(array[1], \"372\") != 0)");
						OutputDebugString("\r\n");
					};
					string_index += sprintf(output + string_index, " %s", array[i]);
				} if (isdigit(code) > 0 && i >= 3 && strcmp(array[1], "372") != 0) {
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

extern "C" __declspec(dllexport) void FreeArray() {

};
