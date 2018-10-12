/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** main
*/
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "my_script.h"

static void init(info_t *info, char *file_name)
{
	char *save = strdup("Script started, file is ");
	info->file_name = strdup(file_name);

	save = realloc(save, strlen(save) + strlen(file_name) + 1);
	strcat(save, file_name);
	info->line = save;
}

int main(int ac, char **av)
{
	info_t *info = malloc(sizeof(info_t));

	ac == 1 ? init(info, "typescript") : init(info, av[1]);
	if (create_file(info) == FAILURE || my_script(info) == FAILURE)
			return (FAILURE);
	free_resources(info);
	return (SUCCESS);
}