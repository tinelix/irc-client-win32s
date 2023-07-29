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

#define EXPORT extern "C" __declspec (dllexport)

EXPORT char* CALLBACK ParseLine(char* original_line, int length);
EXPORT char* CALLBACK ParsePacket(char original_packet[4096]);