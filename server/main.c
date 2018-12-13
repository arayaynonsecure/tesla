/* (c) 2018 Aryeh Klempner <arayaydev@gmail.com>
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version. This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details. You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSS_VALID_ARGC 2

int main(int argc, char *argv[]){
	if(argc > 1) for(int i = 1; i < argc && i <= MAX_POSS_VALID_ARGC; i++){
		if(!strncmp((const char*)(argv[i]), "-h", 2) ||
		!strncmp((const char*)(argv[i]), "--help", 6))
			puts("Try \"info tesla\"");
		else puts("Args not recognized, try \"info tesla\"");
	}
	else puts("No args given, attempting default options");
	exit(EXIT_SUCCESS);
}
