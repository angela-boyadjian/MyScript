/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** print
*/

#include <stdio.h>

#include "my_script.h"

void print_file_content(info_t *info)
{
	char ch;

	if (info->is_open) {
		while((ch = fgetc(info->file)) != EOF)
			printf("%c", ch);
	} else {
		printf("Error: File is not open\n");
	}
}