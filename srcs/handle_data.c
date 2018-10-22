/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** handle_data
*/

#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>

#include "my_script.h"

static const int SIZE = 150;

static void send_data_to_master(info_t *info, fd_set *fd_in, char *input)
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

static void send_data_to_stdout(info_t *info, fd_set *fd_in, char *input)
{
	if (FD_ISSET(info->fd_master, fd_in)) {
		info->rc = read(info->fd_master, input, sizeof(input));
		if (info->rc > 0) {
			write(1, input, info->rc);
		} else {
			fprintf(stderr, "Error %d on read master PTY\n", errno);
			exit(FAILURE);
		}
	}
}

static void check_exit(info_t *info, char *input)
{
	if (strncmp(input, "exit", 4) == SUCCESS) {
		write_status_to_file(info, false);
		if (!check[Q].on && !check[Q_ALT].on)
			write_status_to_stdout(info, false);
		exit(SUCCESS);
	}
}

void wait_for_data(info_t *info)
{
	fd_set fd_in;
	char input[SIZE];

	while (1) {
		FD_ZERO(&fd_in);
		FD_SET(0, &fd_in);
		FD_SET(info->fd_master, &fd_in);

		info->rc = select(info->fd_master + 1, &fd_in, NULL, NULL, NULL);
		if (info->rc == ERROR) {
				fprintf(stderr, "Error %d on select()\n", errno);
				exit(FAILURE);
		} else {
			send_data_to_master(info, &fd_in, input);
			send_data_to_stdout(info, &fd_in, input);
			write(info->fd, input, info->rc);
			check_exit(info, input);
		}
	}
}