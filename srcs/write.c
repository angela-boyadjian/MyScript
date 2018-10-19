/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** write
*/

#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#include "my_script.h"

void write_status_to_file(info_t *info, bool is_start)
{
	static char dt[50];
	time_t time_struct = time(NULL);
	struct tm *tm = gmtime(&time_struct);
	char tmp[20];

	strftime(tmp, 20, "%X", tm);
	strftime(dt, 20, "%F", tm);
	strcat(dt, " ");
	strcat(dt, tmp);
	if (is_start)
		write(info->fd, "Script started on ", 18);
	else
		write(info->fd, "Script done on ", 15);
	write(info->fd, dt, strlen(dt));
	write(info->fd, "\n", 1);
}

void write_status_to_stdout(info_t *info, bool is_start)
{
	if (is_start)
		write(1, "Script start, file is ", 22);
	else
		write(1, "Script done, file is ", 21);
	write(1, info->file_name, strlen(info->file_name));
	write(1, "\n", 1);
}