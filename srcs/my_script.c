/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** my_script
*/

#include "my_script.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct termios orig_termios;
void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int my_script(info_t *info)
{
	fprintf(info->file, "Script done on ");
	write_time(info->file);
	enableRawMode();
	char c;
	char *save = malloc(sizeof(char) * 6);

	for (size_t i = 0; read(STDIN_FILENO, &c, 1) == 1 && c != 'q'; ++i) {
			if (i >= 5) {
				save[i + 1] = 0;
				i = 0;
				fprintf(info->file, "%s\n", save);
			}
			write(1, &c, 1);
			save[i] = c;
	}

	if (info->is_open) {
		fclose(info->file);
		info->is_open = false;
	}
	return (SUCCESS);
}