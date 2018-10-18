/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** main
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "my_script.h"

static int create_file(info_t *info)
{
	int fd = open(info->file_name, O_RDWR | O_TRUNC);

	info->fd = fd;
	info->is_open = true;
	write_status_to_stdout(info, true);
	return (SUCCESS);
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