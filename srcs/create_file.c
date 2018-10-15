/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** create_file
*/

#include <time.h>

#include "my_script.h"

static void writing(int nb, FILE *file, bool is_seconds)
{
	if (!is_seconds)
		nb < 10 ? fprintf(file, "0%d:", nb) : fprintf(file, "%d:", nb);
	else
		nb < 10 ? fprintf(file, "0%d\n", nb) : fprintf(file, "%d\n", nb);
}

void write_time(FILE *file)
{
	time_t time_struct = time(NULL);
	struct tm tm = *localtime(&time_struct);

	fprintf(file, "%d-%d-%d ", tm.tm_year + 1900,
		tm.tm_mon + 1, tm.tm_mday);
	writing(tm.tm_hour, file, false);
	writing(tm.tm_min, file, false);
	writing(tm.tm_sec, file, true);
}

int create_file(info_t *info)
{
	FILE *file = fopen(info->file_name, "w");

	if (!file) {
		perror("fopen");
		return (FAILURE);
	}
	info->file = file;
	info->is_open = true;
	fprintf(file, "Script started on ");
	write_time(info->file);
	printf("%s\n", info->line);
	return (SUCCESS);
}