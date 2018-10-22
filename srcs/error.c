/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** error
*/

#include "my_script.h"

int errors(int ac, char **av)
{
	if (check_flags(av, ac) == FAILURE && av[1][1]) {
		fprintf(stderr, "script: invalid option -- '%c'\nTry ", av[1][1]);
		fprintf(stderr, "'script --help' for more information.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}