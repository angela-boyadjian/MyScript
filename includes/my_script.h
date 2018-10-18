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
#include <sys/select.h>

#define SUCCESS 0
#define FAILURE 84
#define ERROR -1

typedef struct info_s
{
	char *file_name;
	char *line;
	char *shell;
	FILE *file;
	int fd;
	ssize_t rc;
	int fd_master;
	int fd_slave;
	bool is_open;
	struct timeval timeval;
} info_t;

//
// ─── INIT ───────────────────────────────────────────────────────────────────────
//
int get_args(int, char **, info_t *);
int init_master(info_t *);
void init_struct(info_t *, char *);

//
// ─── MYSCRIPT ───────────────────────────────────────────────────────────────────
//
int my_script(info_t *);
void wait_for_data(info_t *);
void write_status_to_file(info_t *, bool);
void write_status_to_stdout(info_t *, bool);

//
// ─── CLEAN ───────────────────────────────────────────────────────────────────────
//
void free_resources(info_t *);

#endif /* !MY_SCRIPT_HPP_ */