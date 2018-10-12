/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** my_script
*/

#include "my_script.h"

int my_script(info_t *info)
{
	if (info->is_open) {
		fclose(info->file);
		info->is_open = false;
	}
	return (SUCCESS);
}