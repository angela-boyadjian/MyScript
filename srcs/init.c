/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** init
*/
#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include "my_script.h"

static void get_name(info_t *info, int ac, char **av)
{
	for (int i = 1; i < ac; ++i) {
		if (av[i][0] != '-') {
			info->file_name = strdup(av[i]);
			return;
		}
	}
	info->file_name = strdup("typescript");
}

static void get_name_cmd(info_t *info, char **av, int i)
{
	if (av[i + 2])
		info->file_name = strdup(av[i + 2]);
	else
		info->file_name = strdup("typescript");
}

static void get_cmd(info_t * info, int ac, char **av)
{
	for (int i = 1; i < ac; ++i) {
		if (av[i + 1] && (strcmp(av[i], "-c") ||
			strcmp(av[i], "--command"))) {
			info->command = strdup(av[i + 1]);
			get_name_cmd(info, av, i);
			return;
		} else {
			fprintf(stderr, "Not enough arguments\n");
			exit(FAILURE);
		}
	}
}

void init_struct(info_t *info, int ac, char **av)
{
	if (check[C].on || check[C_ALT].on) {
		get_cmd(info, ac, av);
	} else {
		ac == 1 ? info->file_name = strdup("typescript") :
			get_name(info, ac, av);
	}
	info->shell = getenv("SHELL");
	if (!info->shell)
		info->shell = "/bin/sh";
}

int init_master(info_t *info)
{
	info->fd_master = posix_openpt(O_RDWR);
	if (info->fd_master < 0) {
		fprintf(stderr, "Error %d on posix_openpt()\n", errno);
		return (FAILURE);
	}
	info->rc = grantpt(info->fd_master);
	if (info->rc != SUCCESS) {
		fprintf(stderr, "Error %d on grantpt()\n", errno);
		return FAILURE;
	}
	info->rc = unlockpt(info->fd_master);
	if (info->rc != SUCCESS) {
		fprintf(stderr, "Error %d on unlockpt()\n", errno);
		return FAILURE;
	}
	return (SUCCESS);
}