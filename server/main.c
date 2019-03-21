/*(c) 2018-19 Aryeh Klempner <arayaydev@gmail.com>
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License (GPL) as published by the Free
Software Foundation, either version 3 of the GPL, or (at your option) any
later version. This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GPL for more details. You should
have received a copy of the GPL with this program. If not, see
<http://www.gnu.org/licenses/>.*/
//glibc feature test macros?
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_POSS_VALID_ARGC 4

uint8_t global_flags;
volatile uint8_t sigflags;

void handl_alrm(int sig){
	sigflags &= 0xFE;
}

void clean_exit(int sig){
	if(isatty(STDIN_FILENO)) tcflush(STDIN_FILENO, TCIFLUSH);
	if(isatty(STDOUT_FILENO)) tcdrain(STDOUT_FILENO);
	if(isatty(STDERR_FILENO)) tcdrain(STDERR_FILENO);
	_exit(EXIT_SUCCESS);
}

void chk_dbl(int sig){
	if(!(sigflags & 0x01)){
	    sigflags |= 0x01;
	    alarm(1U);
	}
/*Note that the first signal received **need not** be SIGTSTP*/
	else if(sig == SIGTSTP) raise(SIGSTOP);
	else clean_exit(sig);
}

static inline void helpchk(int argc, char* argv[]){
	for(int i = 1; i < argc && i <= MAX_POSS_VALID_ARGC; i++){
		if(!strncmp((const char*)(argv[i]), "-h", 2) ||
		!strncmp((const char*)(argv[i]), "--help", 6)){
			puts("Try \"info tesla\"");
			exit(EXIT_SUCCESS);
		}
	}
}

static inline void register_handlers(void){
	struct sigaction sigstruct;
	sigset_t blkmask;
	sigemptyset(&blkmask);
	sigaddset(&blkmask, SIGALRM);
	sigaddset(&blkmask, SIGHUP);
	sigaddset(&blkmask, SIGINT);
	sigaddset(&blkmask, SIGQUIT);
	sigaddset(&blkmask, SIGTERM);
	sigaddset(&blkmask, SIGTSTP);
	sigstruct.sa_flags = SA_RESTART;
	sigstruct.sa_mask = blkmask;
	sigstruct.sa_handler = handl_alrm;
	if(sigaction(SIGALRM, &sigstruct, NULL) == -1) goto err;
	sigstruct.sa_handler = clean_exit;
	if(sigaction(SIGHUP, &sigstruct, NULL) == -1) goto err;
	if(sigaction(SIGTERM, &sigstruct, NULL) == -1) goto err;
	sigstruct.sa_handler = chk_dbl;
	if(sigaction(SIGINT, &sigstruct, NULL) == -1) goto err;
	if(sigaction(SIGQUIT, &sigstruct, NULL) == -1) goto err;
	if(sigaction(SIGTSTP, &sigstruct, NULL) == -1) goto err;
	return;
err:perror("Signal handler setup failed");
	exit(EXIT_FAILURE);
}

static inline uint8_t parse_args(int argc, char* argv[]){
	register bool notify = true;
	register uint8_t flags = 0;
	for(int i = 1; i < argc && i <= MAX_POSS_VALID_ARGC; i++){
		if(!strncmp((const char*)(argv[i]), "--config=/", 10)){
			flags |= 0x01;
			puts("Config file location overridden:");
			puts((const char*)(argv[i] + 9));
		}
		else if(!strncmp((const char*)(argv[i]), "--dataset=/", 11)){
			flags |= 0x02;
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
	return flags;
}

int main(int argc, char* argv[]){
	helpchk(argc, argv);
	register_handlers();
	if(argc > 1) global_flags = parse_args(argc, argv);
	else puts("No args given, trying default options");
	exit(EXIT_SUCCESS);
}
