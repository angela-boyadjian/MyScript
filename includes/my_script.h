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
#define NB_OPTIONS 10
#define MSG1 "\nUsage:\n script [options] [file]\n\nMake a typescript of a "
#define MSG2 "terminal session.\n\nOptions:\n -a, --append\t\t\tappend the "
#define MSG3 "output\n -c, --command <command>\trun command rather than "
#define MSG4 "interactive shell\n -q, --quiet\t\t\tbe quiet\n -h, --help\t\t"
#define MSG5 "\tdisplay this help\n -V, --version\t\t\tdisplay version"

enum flags {
	H,
	H_ALT,
	A,
	A_ALT,
	Q,
	Q_ALT,
	V,
	V_ALT,
	C,
	C_ALT
};

typedef struct info_s
{
	char *file_name;
	char *line;
	char *shell;
	char *command;
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
void option_h(void);
void option_v(void);
int check_flags(char **, int);

//
// ─── ERROR HANDLING ───────────────────────────────────────────────────────────────────────
//
int errors(int, char **);

//
// ─── CLEAN ───────────────────────────────────────────────────────────────────────
//
void free_resources(info_t *);

#endif /* !MY_SCRIPT_HPP_ */