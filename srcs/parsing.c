/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** parsing
*/
#include <string.h>

#include "my_script.h"

//
// ─── CHECK IF FLAG IS VALID AND SET ON 1 IF SO ───────────────────────────────────────────────────────────────────────
//
static int validate_flags(char *av)
{
	int j;

	for (int i = 0; av[i]; ++i) {
		for (j = 0; j < NB_OPTIONS; ++j) {
			if (strcmp(check[j].flag, av) == 0) {
				check[j].on = 1;
				break;
			}
		}
		if (j == NB_OPTIONS)
			return (FAILURE);
	}
	return (SUCCESS);
}

//
// ─── CHECK IF THERE ARE FLAGS ───────────────────────────────────────────────────────────────────────
//
int check_flags(char **av, int ac)
{
	for (int i = 1; i < ac; ++i) {
		if (av[i][0] == '-' && validate_flags(av[i] + 1) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}