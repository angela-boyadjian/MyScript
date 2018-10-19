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
#define NB_OPTIONS 5
#define MSG1 "\nUsage:\n\tscript [options] [file]\n\nMake a typescript of a "
#define MSG2 "terminal session.\n\nOptions:\n\t-a, --append"
#define MSG3 ""
#define MSG4 ""
#define MSG5 ""

enum flags {
	H,
	A,
	A_ALT,
	Q,
	V
};

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

typedef struct options_s {
	char *flag;
	int on;
	void (*ptr)(info_t *);
} options_t;

//
// ─── INIT ───────────────────────────────────────────────────────────────────────
//
int get_args(int, char **, info_t *);
int init_master(info_t *);
void init_struct(info_t *, int, char **);

//
// ─── MYSCRIPT ───────────────────────────────────────────────────────────────────
//
options_t check[NB_OPTIONS];
int my_script(info_t *);
void wait_for_data(info_t *);
void write_status_to_file(info_t *, bool);
void write_status_to_stdout(info_t *, bool);
void option_a(info_t *info);
void option_h(info_t *info);
void option_q(info_t *info);
void option_v(info_t *info);
int check_flags(char **av, int ac);


int errors(int ac, char **av);


//
// ─── CLEAN ───────────────────────────────────────────────────────────────────────
//
void free_resources(info_t *);

#endif /* !MY_SCRIPT_HPP_ */