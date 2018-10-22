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
	int fd;

	if (check[A].on || check[A_ALT].on)
		fd = open(info->file_name, O_RDWR | O_APPEND);
	else
		fd = open(info->file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	info->fd = fd;
	info->is_open = true;
	if (!check[Q].on && !check[Q_ALT].on)
		write_status_to_stdout(info, true);
	return (SUCCESS);
}

int main(int ac, char *av[])
{
	info_t *info = malloc(sizeof(info_t));

	if (errors(ac, av) == FAILURE)
		return (FAILURE);
	if (check[H].on || check[H_ALT].on)
		option_h();
	else if (check[V].on || check[V_ALT].on)
		option_v();
	init_struct(info, ac, av);
	if (create_file(info) == FAILURE || my_script(info) == FAILURE)
			return (FAILURE);
	free_resources(info);
	return (SUCCESS);
}