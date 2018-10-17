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
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "my_script.h"

struct termios slave_orig_term_settings; // Saved terminal settings
struct termios new_term_settings; // Current terminal settings


int my_script(info_t *info)
{
	fprintf(info->file, "Script done on ");
	write_time(info->file);
	int rc;
	int ptmx = getpt();

	if (ptmx == -1) {
		printf("Failed to open pseudo-terminal master-slave for use with xterm. Aborting...");
		exit(-1);
	} else if (unlockpt(ptmx) != 0 || grantpt(ptmx) != 0) {
		printf("Failed to unlock pseudo-terminal master-slave for use with xterm (errno. %d). Aborting...", errno);
		close(ptmx);
		exit(-1);
	}

	// open the corresponding pseudo-terminal slave (that's us)
	char *pts_name = ptsname(ptmx);
	int pts = open(pts_name, O_RDWR | O_NOCTTY);

	// info->shell = getenv("SHELL");
	// if (!info->shell)
		info->shell = "/bin/sh";
	info->slavepid = fork();
	if (info->slavepid == 0) {
		char *shell = "/bin/sh";

		close(ptmx);

		// Save the default parameters of the slave side of the PTY
		rc = tcgetattr(ptmx, &slave_orig_term_settings);

		// Set raw mode on the slave side of the PTY
		new_term_settings = slave_orig_term_settings;
		cfmakeraw (&new_term_settings);
		tcsetattr (ptmx, TCSANOW, &new_term_settings);

		// The slave side of the PTY becomes the standard input and outputs of the child process
		close(0); // Close standard input (current terminal)
		close(1); // Close standard output (current terminal)
		close(2); // Close standard error (current terminal)
		int i = 0;
		setsid();
		ioctl(pts, TIOCSCTTY, &i);
		dup2(pts, STDIN_FILENO);
		dup2(pts, STDOUT_FILENO);
		dup2(pts, STDERR_FILENO);
		execlp(info->shell, info->shell, NULL);
		exit(1);
	} else {
		close(pts);
		while (1) {
			char input[256];
			// Get the child's answer through the PTY
			rc = read(ptmx, input, sizeof(input) - 1);
			if (rc > 0) {
				// Make the answer NUL terminated to display it as a string
				input[rc] = '\0';
				fprintf(stderr, "%s", input);
			} else {
				break;
			}
		} // End while
		// int status;
		// char buf[256];
		// int fd = fileno(info->file);
		// waitpid(info->slavepid, &status, 0);
		// read(0, buf, sizeof(buf));
		// fwrite(buf, sizeof(char), 256, info->file);
	}
	return (SUCCESS);
}