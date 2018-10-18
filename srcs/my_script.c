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
#include <termios.h>
#include <string.h>

#include "my_script.h"

int my_script(info_t *info)
{
	init_master(info);
	info->fd_slave = open(ptsname(info->fd_master), O_RDWR);

	if (fork()) {
		close(info->fd_slave);
		wait_for_data(info);
	} else {
		set_raw_mode(info);
		update_streams(info);
		setsid();
		ioctl(0, TIOCSCTTY, 1);
		info->rc = execl(info->shell, info->shell, NULL, NULL);
		return (FAILURE);
	}
	fprintf(info->file, "Script done on ");
	write_time(info->file);
	return (SUCCESS);
}