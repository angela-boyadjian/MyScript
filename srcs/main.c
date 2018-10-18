/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** main
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
#include<string.h>

#include "my_script.h"

void send_data_to_master(info_t *info, fd_set *fd_in, char *input)
{
	if (FD_ISSET(0, fd_in)) {
		info->rc = read(0, input, sizeof(input));
		if (info->rc > 0) {
			write(info->fd_master, input, info->rc);
		} else {
			fprintf(stderr, "Error %d on read standard input\n", errno);
			exit(1);
		}
	}
}

void send_data_to_stdout(info_t *info, fd_set *fd_in, char *input, int fd)
{

	if (FD_ISSET(info->fd_master, fd_in)) {
		info->rc = read(info->fd_master, input, sizeof(input));
		if (info->rc > 0) {
			write(fd, input, info->rc); // Write output to file
			write(1, input, info->rc);
		} else {
			if (info->rc < 0) {
				fprintf(stderr, "Error %d on read master PTY\n", errno);
				exit(1);
			}
		}
	}
}

void wait_for_data(info_t *info)
{
	fd_set fd_in;
	char input[150];
	int fd = open("test", O_RDWR | O_TRUNC);

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
}

void set_raw_mode(info_t *info)
{
	struct termios slave_orig_term_settings;
	struct termios new_term_settings;

	close(info->fd_master);
	info->rc = tcgetattr(info->fd_slave, &slave_orig_term_settings);
	new_term_settings = slave_orig_term_settings;
	cfmakeraw (&new_term_settings);
	tcsetattr (info->fd_slave, TCSANOW, &new_term_settings);
}

void update_streams(info_t *info)
{
	close(0);
	close(1);
	close(2);

	dup(info->fd_slave);
	dup(info->fd_slave);
	dup(info->fd_slave);

	close(info->fd_slave);
}

int main(int ac, char *av[])
{
	info_t *info = malloc(sizeof(info_t));

	ac == 1 ? init_struct(info, "typescript") : init_struct(info, av[1]);
	if (create_file(info) == FAILURE || my_script(info) == FAILURE)
			return (FAILURE);
	free_resources(info);
	return (SUCCESS);
}