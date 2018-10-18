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

typedef struct info_s
{
	char *command;
	char *file_name;
	char *line;
	char *shell;
	FILE *file;
	int rc;
	int fd_master;
	int fd_slave;
	bool is_open;
} info_t;

//
// ─── INIT ───────────────────────────────────────────────────────────────────────
//
int get_args(int, char **, info_t *);
int create_file(info_t *info);
int init_master(info_t *info);
void init_struct(info_t *, char *);

//
// ─── MYSCRIPT ───────────────────────────────────────────────────────────────────
//
int my_script(info_t *);
void send_data_to_master(info_t *info, fd_set *fd_in, char *input);
void send_data_to_stdout(info_t *info, fd_set *fd_in, char *input, int fd);
void wait_for_data(info_t *info);
void set_raw_mode(info_t *info);
void update_streams(info_t *info);

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