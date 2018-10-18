/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** handle_data
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

void send_data_to_master(info_t *info, fd_set *fd_in, char *input)
{
	if (FD_ISSET(0, fd_in)) {
		info->rc = read(0, input, sizeof(input));
		if (info->rc > 0) {
			write(info->fd_master, input, info->rc);
		} else {
			fprintf(stderr, "Error %d on read standard input\n", errno);
			exit(FAILURE);
		}
	}
}

void send_data_to_stdout(info_t *info, fd_set *fd_in, char *input, int fd)
{
	if (FD_ISSET(info->fd_master, fd_in)) {
		info->rc = read(info->fd_master, input, sizeof(input));
		if (info->rc > 0) {
			write(fd, input, info->rc);
			write(1, input, info->rc);
		} else {
			fprintf(stderr, "Error %d on read master PTY\n", errno);
			exit(FAILURE);
		}
	}
}

void wait_for_data(info_t *info)
{
	fd_set fd_in;
	char input[150];
	int fd = open(info->file_name, O_RDWR | O_TRUNC);

	while (1) {
		FD_ZERO(&fd_in);
		FD_SET(0, &fd_in);
		FD_SET(info->fd_master, &fd_in);

		info->rc = select(info->fd_master + 1, &fd_in, NULL, NULL, NULL);
		switch(info->rc) {
			case -1 :
				fprintf(stderr, "Error %d on select()\n", errno);
				exit(1);
			default : {
				send_data_to_master(info, &fd_in, input);
				send_data_to_stdout(info, &fd_in, input, fd);
			}
		}
	}
	close(fd);
}