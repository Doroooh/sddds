#ifndef _UNIQUE_SHELL_H_
#define _UNIQUE_SHELL_H_

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

/* Read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Number conversion flags */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* System getline usage flag */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".unique_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * Struct for a singly linked list node
 */
typedef struct list_node {
    int number;
    char *string;
    struct list_node *next;
} list_t;

/**
 * Struct for passing information to functions
 */
typedef struct info {
    char *argument;
    char **arguments;
    char *path;
    int argument_count;
    unsigned int line_count;
    int error_number;
    int line_count_flag;
    char *filename;
    list_t *environment;
    list_t *command_history;
    list_t *alias;
    char **environment_copy;
    int environment_changed;
    int status;
    char **command_buffer;
    int command_buffer_type;
    int read_file_descriptor;
    int history_count;
} info_t;

#define INFO_INITIALIZER \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 * Struct for builtin commands and their related functions
 */
typedef struct builtin_command {
    char *command;
    int (*function)(info_t *);
} builtin_table;

/* Function prototypes */

/* Shell loop */
int shell_loop(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* Parser */
int is_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_path(info_t *, char *, char *);

/* Main loop */
int main_loop(char **);

/* Error handling */
void error_puts(char *);
int error_putchar(char);
int put_file_descriptor(char, int);
int put_string_file_descriptor(char *, int);

/* String operations */
int string_length(char *);
int string_compare(char *, char *);
char *starts_with(const char *, const char *);
char *string_concatenate(char *, char *);

/* More string operations */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void output_string(char *);
int output_character(char);

/* Exit functions */
char *string_copy_n(char *, char *, int);
char *string_concatenate_n(char *, char *, int);
char *string_character(char *, char);

/* Tokenizer */
char **split_string(char *, char *);
char **split_string2(char *, char);

/* Memory reallocation */
char *memory_set(char *, char, unsigned int);
void free_memory(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* Memory management */
int block_free(void **);

/* String to integer */
int interactive_mode(info_t *);
int delimiter(char, char *);
int is_alpha(int);
int ascii_to_integer(char *);

/* Error handling continued */
int error_ascii_to_integer(char *);
void print_error_message(info_t *, char *);
int print_decimal(int, int);
char *convert_integer(long int, int, int);
void remove_comment(char *);

/* Built-in commands */
int exit_shell(info_t *);
int change_directory(info_t *);
int shell_help(info_t *);

/* More built-in commands */
int shell_history(info_t *);
int shell_alias(info_t *);

/* Input retrieval */
ssize_t get_input_stream(info_t *);
int get_line(info_t *, char **, size_t *);
void interrupt_signal_handler(int);

/* Information retrieval */
void clear_information(info_t *);
void set_information(info_t *, char **);
void free_information(info_t *, int);

/* Environment handling */
char *get_environment_variable(info_t *, const char *);
int shell_environment(info_t *);
int set_shell_environment(info_t *);
int unset_shell_environment(info_t *);
int populate_environment_list(info_t *);

/* Environment retrieval */
char **get_shell_environment(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* History management */
char *get_history_filename(info_t *info);
int write_shell_history(info_t *info);
int read_shell_history(info_t *info);
int build_shell_history_list(info_t *info, char *buffer, int line_count);
int renumber_shell_history(info_t *info);

/* Linked lists */
list_t *add_list_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_node_at_position(list_t **, unsigned int);
void free_list_memory(list_t **);

/* More linked list functions */
size_t list_length(const list_t *);
char **list_to_string_array(list_t *);
size_t print_node_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_position(list_t *, list_t *);

/* Variable handling */
int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_command_alias(info_t *);
int replace_variables(info_t *);
int replace_substring(char **, char *);

#endif /* _UNIQUE_SHELL_H_ */

