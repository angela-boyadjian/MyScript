/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** my_script
*/

#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <termios.h>
#include <string.h>

#include "my_script.h"

options_t check[NB_OPTIONS] = { // Flags
	{"h", 0},
	{"-help", 0},
	{"a", 0},
	{"-append", 0},
	{"q", 0},
	{"-quiet", 0},
	{"V", 0},
	{"-version", 0},
	{"c", 0},
	{"-command", 0}
};

//
// ─── SET RAW MODE ON THE SLAVE SIDE OF THE PTY ───────────────────────────────────────────────────────────────────────
//
static void set_raw_mode(info_t *info)
{
	struct termios slave_orig_term_settings; // Save terminal settings
	struct termios new_term_settings; // Current terminal settings

	close(info->fd_master);
	info->rc = tcgetattr(info->fd_slave, &slave_orig_term_settings); // Save the default parameters of the slave side of the PTY
	new_term_settings = slave_orig_term_settings;
	cfmakeraw (&new_term_settings); // Set RAW mode on the slave side of the PTY
	tcsetattr (info->fd_slave, TCSANOW, &new_term_settings);
}

//
// ─── THE SLAVE SIDE BECOMES THE STANDARD INPUT AND OUTPUT OF THE CHILD PROCESS ───────────────────────────────────────────────────────────────────────
//
static void update_streams(info_t *info)
{
	// The slave side of the PTY becomes the standard input and output of the child process
	close(0); // Close standard input (current terminal)
	close(1); // Close standard output (current terminal)
	close(2); // Close standard error (current terminal)

	dup(info->fd_slave); // PTY becomes standard input (0)
	dup(info->fd_slave); // PTY becomes standard ouput (1)
	dup(info->fd_slave); // PTY becomes standard error (2)

	close(info->fd_slave); // Now the original fd becomes useless
}

int my_script(info_t *info)
{
	write_status_to_file(info, true);
	if (init_master(info) == FAILURE)
		return (FAILURE);
	info->fd_slave = open(ptsname(info->fd_master), O_RDWR); // Open the slave side of PTY
	if (fork()) { // Create child process
		// FATHER
		close(info->fd_slave); // Close the slave side of the PTY
		wait_for_data(info);
	} else {
		// CHILD
		set_raw_mode(info);
		update_streams(info);
		setsid(); // Make the current process a new session leader
		// As the child is a session leader, set the controlling terminal to be the slave side of the PTY
		// (Mandatory for programs like the shell to make them manage correctly their outputs)
		ioctl(0, TIOCSCTTY, 1);
		if (check[C].on || check[C_ALT].on)
			info->rc = execl(info->shell, info->shell, "-c", info->command, NULL);
		else
			info->rc = execlp(info->shell, info->shell, NULL, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}