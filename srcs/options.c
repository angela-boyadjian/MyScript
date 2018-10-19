/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** options
*/

#include <stdio.h>

#include "my_script.h"

void option_a(info_t *info)
{
	write(1, "flag a\n", 8);
}

void option_q(info_t *info)
{
	write(1, "flag q\n", 8);
}

void option_h(info_t *info)
{
	write(1, "flag h\n", 8);
}

void option_v(info_t *info)
{
	write(1, "flag V\n", 8);
}