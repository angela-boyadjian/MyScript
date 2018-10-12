/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** free
*/

#include <stdlib.h>

#include "my_script.h"

void free_resources(info_t *info)
{
	if (info->file_name)
		free(info->file_name);
	if (info->line)
		free(info->line);
	free (info);

}