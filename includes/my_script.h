/*
** EPITECH PROJECT, 2018
** MyScript
** File description:
** my_script
*/

#ifndef MY_SCRIPT_H
#define MY_SCRIPT_H

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define SUCCESS 0
#define FAILURE 84
#define ERROR -1
#define WRITE_END 1
#define READ_END 0
typedef struct info_s
{
	char *command;
	char *file_name;
	char *line;
	char *shell;
	FILE *file;
	pid_t masterpid;
	pid_t slavepid;
	bool is_open;
} info_t;

//
// ─── INIT ───────────────────────────────────────────────────────────────────────
//
int get_args(int, char **, info_t *);
int create_file(info_t *info);

//
// ─── MYSCRIPT ───────────────────────────────────────────────────────────────────
//
int my_script(info_t *);

//
// ─── PRINT ──────────────────────────────────────────────────────────────────────
//
void print_file_content(info_t *);

//
// ─── WRITE ───────────────────────────────────────────────────────────────────────
//
void write_time(FILE *);

//
// ─── CLEAN ───────────────────────────────────────────────────────────────────────
//
void free_resources(info_t *);

#endif /* !MY_SCRIPT_HPP_ */