#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSS_ARGC 2

int main(int argc, char *argv[]){
	if(argc > 1) for(int i = 1; i < argc && i <= MAX_POSS_ARGC; i++){
		if(!strncmp((const char*)(argv[i]), "-h", 2) ||
		!strncmp((const char*)(argv[i]), "--help", 6))
			puts("Try \"info tesla\"");
		else puts("Args not recognized, try \"info tesla\"");
	}
	else puts("No args given, attempting default options");
	exit(EXIT_SUCCESS);
}
