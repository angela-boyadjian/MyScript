/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** options
*/

#include <stdio.h>
#include <stdlib.h>

#include "my_script.h"

void option_h(void)
{
	printf("%s%s%s%s%s\n", MSG1, MSG2, MSG3, MSG4, MSG5);
	exit(SUCCESS);
}

void option_v(void)
{
	printf("script from util-linux 2.31.1\n");
	exit(SUCCESS);
}