/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** main
*/
#include <stdlib.h>

#include "my_script.h"

int main(int ac, char *av[])
{
	info_t *info = malloc(sizeof(info_t));

	ac == 1 ? init_struct(info, "typescript") : init_struct(info, av[1]);
	if (create_file(info) == FAILURE || my_script(info) == FAILURE)
			return (FAILURE);
	free_resources(info);
	return (SUCCESS);
}