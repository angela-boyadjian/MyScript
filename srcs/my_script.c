/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** my_script
*/

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "my_script.h"

// int my_script(info_t *info)
// {
// 	(void)info;
// 	// Open a pseudo-terminal master
// 	int ptmx = open("/dev/ptmx", O_RDWR | O_NOCTTY);

// 	if (ptmx == -1) {
// 		printf("Failed to open pseudo-terminal master-slave for use with xterm. Aborting...");
// 		exit(-1); // closes any open streams and exits the program
// 	} else if (unlockpt(ptmx) != 0) {
// 		printf("Failed to unlock pseudo-terminal master-slave for use with xterm (errno. %d). Aborting...", errno);
// 		close(ptmx);
// 		exit(-1);
// 	} else if (grantpt(ptmx) != 0) {
// 		printf("Failed to grant access rights to pseudo-terminal master-slave for use with xterm (errno. %d). Aborting...", errno);
// 		close(ptmx);
// 		exit(-1);
// 	}

// 	// open the corresponding pseudo-terminal slave (that's us)
// 	char *pts_name = ptsname(ptmx);
// 	printf("Slave-master terminal: %s", pts_name);
// 	int pts = open(pts_name, O_RDWR | O_NOCTTY);

// 	// launch an xterm that uses the pseudo-terminal master we have opened
// 	char *xterm_cmd;
// 	asprintf(&xterm_cmd, "xterm -S%s/%d", pts_name, ptmx);
// 	FILE *xterm_stdout = popen(xterm_cmd, "r");
// 	if (xterm_stdout <= 0) {
// 		printf("Failed to open xterm process. Aborting...");
// 		ptmx = 0;
// 		close(ptmx);
// 		exit(-1);
// 	}
// 	// Set the stdin / stdout to be the pseudo-terminal slave
// 	dup2(pts, STDIN_FILENO);
// 	dup2(pts, STDOUT_FILENO);

// 	printf("This appears in the terminal window.\n");
// 	return (42);
// }

int my_script(info_t *info)
{
	fprintf(info->file, "Script done on ");
	write_time(info->file);

	int ptmx = getpt();
	if (ptmx == -1) {
		printf("Failed to open pseudo-terminal master-slave for use with xterm. Aborting...");
		exit(-1); // closes any open streams and exits the program
	} else if (unlockpt(ptmx) != 0 || grantpt(ptmx) != 0) {
		printf("Failed to unlock pseudo-terminal master-slave for use with xterm (errno. %d). Aborting...", errno);
		close(ptmx);
		exit(-1);
	}
	// open the corresponding pseudo-terminal slave (that's us)
	char *pts_name = ptsname(ptmx);
	printf("Slave-master terminal: %s", pts_name);
	int pts = open(pts_name, O_RDWR | O_NOCTTY);

	// info->shell = getenv("SHELL");
	// if (!info->shell)
		info->shell = "/bin/sh";
	// launch an xterm that uses the pseudo-terminal master we have opened
	info->slavepid = fork();
	if (info->slavepid == 0) {
		execlp(info->shell, info->shell, NULL);
		dup2(pts, STDIN_FILENO);
		dup2(pts, STDOUT_FILENO);
	} else {
		char Output[100];

		while (1) {
			memset(Output, 0, sizeof(Output));
			read(ptmx, Output, sizeof(Output));
			printf("%s\n", Output);

		}
	}
	return (SUCCESS);
}