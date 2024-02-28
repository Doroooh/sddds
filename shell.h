#ifndef  SHELL_H
#define SHELL_H

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

/* for the read or write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for the task commands chaining */
#define CMD_NORM	0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN	3

/* to convert the number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED 2

/* 1 if  system getline() is used */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".the_simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - the singly linked lists
 * @num: this is the field of numbers
 * @str:  the string
 * @next: this are the points to get or reach next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - this has the pseudo-arguments that pass into the function to allow prototype uniformity for the function pointer structure.  
 *@arg: the string resulting from the getline that contains arguments
 *@argv: the array of strings that are generated from the string arg
 *@path: this is the string path for the shell’s current command
 *@argc: argument count
 *@line_count: error count
 *@err_num: error code for shell_exit()s
 *@linecount_flag: if it’s on count this line of input
 *@fname: program filename
 *@env: the linked list local copy of environ
 *@environ: the custom modified copy of environ from LL env
 *@history: shell history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: history of line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and a related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* shell_pointer.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/*shell_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*shell _string1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* shell_string2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* shell_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* shell_towz.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/*shell_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* shell_mem.c */
int bfree(void **);

/* shell_intera.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _intera(char *);

/* shell_errors1.c */
int shell_errintera(char *);
void print_shell_error(info_t *, char *);
int print_d(int, int);
char *convert_shell_number(long int, int, int);
void remove_shell_comments(char *);

/* shell_builtin2.c */
int shell_myexit(info_t *);
int shell_mycd(info_t *);
int shell_myhelp(info_t *);

/* shell_builtin2.c */
int shell_myhistory(info_t *);
int shell_myalias(info_t *);

/*shell_getline.c */
ssize_t get_input(info_t *);
int shell_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* shell_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* shell_environ.c */
char *shell_getenv(info_t *, const char *);
int shell_myenv(info_t *);
int shell_mysetenv(info_t *);
int shell_myunsetenv(info_t *);
int populate_env_list(info_t *);

/* _getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* shell_get_history.c */
char *shell_get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* shell_lists1.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* shell_lists2.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* shell_vars_file.c */
int is_shell_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_shell_alias(info_t *);
int replace_shell_vars(info_t *);
int replace_shell_string(char **, char *);


#endif
