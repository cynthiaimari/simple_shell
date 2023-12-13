#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int _find_builtin(info_t *);
void _find_cmd(info_t *);
void _fork_cmd(info_t *);

/* toem_parser.c */
int _is_cmd(info_t *, char *);
char *_dup_chars(char *, int, int);
char *_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_err.c */
void _iputs(char *);
int _iputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _str_len(char *);
int _str_cmp(char *, char *);
char *_starts_wth(const char *, const char *);
char *_str_cat(char *, char *);

/* toem_string2.c */
char *_str_cpy(char *, char *);
char *_str_dup(const char *);
void _puts(char *);
int _put_char(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tkenizer.c */
char **_str_tow(char *, char *);
char **_str_tow2(char *, char);

/* toem_realloc.c */
char *_mem_set(char *, char, unsigned int);
void _ffree_strn(char **);
void *_real_loc(void *, unsigned int, unsigned int);

/* toem_mem.c */
int _free_it(void **);

/* toem_atoi.c */
int interact(info_t *);
int delim_check(char, char *);
int _alpha(int);
int _atoi(char *);

/* toem_err2.c */
int _err_atoi(char *);
void _print_error(info_t *, char *);
int _print_d(int, int);
char *_convert_number(long int, int, int);
void _remove_comments(char *);

/* toem_builtin.c */
int _myend(info_t *);
int _mycf(info_t *);
int _myhell(info_t *);

/* toem_builtin2.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t _get_input(info_t *);
int _get_line(info_t *, char **, size_t *);
void _sigint_Handler(int);

/* toem_geinfo.c */
void _clearinfo(info_t *);
void _setinfo(info_t *, char **);
void _freeinfo(info_t *, int);

/* toem_environ.c */
char *_gitenv(info_t *, const char *);
int _mienv(info_t *);
int _misetenv(info_t *);
int _miunsetenv(info_t *);
int pop_env_list(info_t *);

/* toem_getenv.c */
char **_get_environ(info_t *);
int _unset_env(info_t *, char *);
int _set_env(info_t *, char *, char *);

/* toem_hist.c */
char *_get_history_file(info_t *info);
int _write_history(info_t *info);
int _read_history(info_t *info);
int _build_history_list(info_t *info, char *buf, int linecount);
int _re_number_history(info_t *info);

/* toem_lists.c */
list_t *_add_node(list_t **, const char *, int);
list_t *_add_node_end(list_t **, const char *, int);
size_t _print_list_str(const list_t *);
int _delete_node_at_index(list_t **, unsigned int);
void _free_list(list_t **);

/* toem_lists2.c */
size_t _list_len(const list_t *);
char **_list_to_strings(list_t *);
size_t _print_list(const list_t *);
list_t *_node_starts_with(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
