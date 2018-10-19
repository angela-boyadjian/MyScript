/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** error
*/

#include "my_script.h"

int errors(int ac, char **av)
{
	if (check_flags(av, ac) == FAILURE) {
		fprintf(stderr, "Invalid option\n");
		return (FAILURE);
	}
	return (SUCCESS);
}