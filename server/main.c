/*(c) 2018-19 Aryeh Klempner <arayaydev@gmail.com>
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License (GPL) as published by the Free
Software Foundation, either version 3 of the GPL, or (at your option) any
later version. This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GPL for more details. You should
have received a copy of the GPL with this program. If not, see
<http://www.gnu.org/licenses/>.*/
/*#define _REENTRANT
#include "include/tesla.h"*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSS_VALID_ARGC 4

uint8_t global_flags;

static inline void parse_args(int argc, char* argv[]){
	register bool notify = true;
	for(int i = 1; i < argc && i <= MAX_POSS_VALID_ARGC; i++){
//TODO: "-h --help" needs 2 only gen 1 msg
		if(!strncmp((const char*)(argv[i]), "-h", 2) ||
		!strncmp((const char*)(argv[i]), "--help", 6)){
			puts("Try \"info tesla\"");
			exit(EXIT_SUCCESS);
		}
		else if(!strncmp((const char*)(argv[i]), "--config=/", 10)){
			global_flags |= 0x01;
			puts("Config file location overridden:");
			puts((const char*)(argv[i] + 9));
		}
		else if(!strncmp((const char*)(argv[i]), "--dataset=/", 11)){
			global_flags |= 0x02;
			puts("Default dataset overridden:");
			puts((const char*)(argv[i] + 10));
		}
		else if(notify){
			puts("Unknown arg detected:");
			puts((const char*)(argv[i]));
			puts("Is this a typo? See \"info tesla\" for help");
			notify = false;
		}
	}
}
int main(int argc, char* argv[]){
	if(argc > 1) parse_args(argc, argv);
	else puts("No args given, trying default options");
	exit(EXIT_SUCCESS);
}
