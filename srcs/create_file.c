/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** create_file
*/

#include "my_script.h"

int create_file(info_t *info)
{
	FILE *file = fopen(info->file_name, "w");

	if (!file) {
		perror("fopen");
		return (FAILURE);
	}
	info->file = file;
	info->is_open = true;
	fprintf(file, "%s\n", info->line);
	return (SUCCESS);
}