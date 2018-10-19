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

options_t check[NB_OPTIONS] = {
	{"h", 0, &option_h},
	{"a", 0, &option_a},
	{"-append", 0, &option_a},
	{"q", 0, &option_q},
	{"V", 0, &option_v}
};

static void set_raw_mode(info_t *info)
{
	struct termios slave_orig_term_settings;
	struct termios new_term_settings;

	close(info->fd_master);
	info->rc = tcgetattr(info->fd_slave, &slave_orig_term_settings);
	new_term_settings = slave_orig_term_settings;
	cfmakeraw (&new_term_settings);
	tcsetattr (info->fd_slave, TCSANOW, &new_term_settings);
}

static void update_streams(info_t *info)
{
	close(0);
	close(1);
	close(2);

	dup(info->fd_slave);
	dup(info->fd_slave);
	dup(info->fd_slave);

	close(info->fd_slave);
}

int my_script(info_t *info)
{
	for (int j = 0; j < NB_OPTIONS; ++j) {
		if (check[j].ptr && check[j].on == 1)
			(check[j].ptr)(info);
	}
	write_status_to_file(info, true);
	if (init_master(info) == FAILURE)
		return (FAILURE);
	info->fd_slave = open(ptsname(info->fd_master), O_RDWR);

	if (fork()) {
		close(info->fd_slave);
		wait_for_data(info);
	} else {
		set_raw_mode(info);
		update_streams(info);
		setsid();
		ioctl(0, TIOCSCTTY, 1);
		info->rc = execlp(info->shell, info->shell, NULL, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}