#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
extern char **environ;
#define CMD_NORM 0
#define CMD_CHAIN 3
#define CMD_AND 2
#define CMD_OR 1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define HIST_F ".shell_history"
#define HIST_M 4096
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USE_GETLINE 0
#define USE_STRTOK 0

/**
 * struct strList - linked list
 * @num: number arg
 * @str: string arg
 * @next: next node
 */
typedef struct strList
{
	int num;
	char *str;
	struct strList *next;
} chain_t;

/**
 * struct passData - pseudo args for uniform prototype
 * @arg: args from getline
 * @argv: values of args
 * @path: path of cmd
 * @argc: number of args
 * @line_count: error count
 * @err_num: error codes
 * @linecount_flag: counts line of input
 * @fname: program filename
 * @env: copy of environ
 * @environ: modified copy from LL env
 * @history: history mode
 * @alias: alias mode
 * @env_changed: detects for environ changes
 * @status: status of last cmd
 * @cmd_buf: pointer to cmd_buf address
 * @cmd_buf_type: cmd type
 * @readfd: file descriptor to read input
 * @histcount: count of history line
 */
typedef struct passData
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	chain_t *env;
	chain_t *history;
	chain_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
	NULL, 0, 0, 0}

int hsh(data_t *, char**);
int is_cmd(data_t *, char *);
int loophsh(char **);
void _eputs(char *);
int _strlen(char *);
int find_builtin(data_t *);
char *dup_chars(char *, int, int);
int _eputchar(char);
int _strcmp(char *, char *);
void find_cmd(data_t *);
char *find_path(data_t *, char *, char*);
int _putfd(char c, int fd);
char *starts_with(const char *, const char *);
void fork_cmd(data_t *);
int _putsfd(char *str, int fd);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strncpy(char *, char *, int);
char **strtow(char *, char *);
char *_memset(char *, char, unsigned int);
int bfree(void **);
int interactive(data_t *);
char *_strdup(const char *);
char *_strncat(char *, char *, int);
char **strstow2(char *, char);
void ffree(char **);
int is_delim(char, char *);
void _puts(char *);
char *_strchr(char *, char);
void *_realloc(void *, unsigned int, unsigned int);
int _isalpha(int);
int _putchar(char);
int _atoi(char *);

/**
 * struct builtin - built in strings and funcs
 * @type: command flag
 * @func: function to run
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_t;

int _erratoi(char *);
int shellExit(data_t *);
int printHistory(data_t *);
ssize_t get_input(data_t *);
void clear_info(data_t *);
void print_error(data_t *, char *);
int chDir(data_t *);
int _alias(data_t *);
int _getline(data_t *, char **, size_t *);
void set_info(data_t *, char **);
int print_d(int, int);
int helpCall(data_t *);
void siginitHandler(int);
void free_info(data_t *, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
char *envGet(data_t *, const char *);
char **environGet(data_t *);
char *historyFileGet(data_t *);
chain_t *add_node(chain_t **, const char *, int);
int printEnv(data_t *);
int _unsetenv(data_t *);
int historyWrite(data_t *data);
chain_t *add_node_end(chain_t **, const char *, int);
int setEnv(data_t *);
int _setEnv(data_t *, char *, char *);
int historyRead(data_t *data);
size_t printListStr(const chain_t *);
int unsetEnv(data_t *, char *);
int historyListBuild(data_t *data, char *buf, int linecount);
int delete_node_at_index(chain_t **, unsigned int);
int envList(data_t *);
int historyRenumber(data_t *data);
void free_list(chain_t **);
size_t list_len(const chain_t *);
int is_chain(data_t *, char *, size_t *);
char **list_to_strings(chain_t *);
void check_chain(data_t *, char *, size_t *, size_t, size_t);
size_t printList(const chain_t *);
int replace_alias(data_t *);
chain_t *node_starts_with(chain_t *, char *, char);
int replace_vars(data_t *);
ssize_t get_node_index(chain_t *, chain_t *);
int replace_string(char **, char *);
#endif /* SHELL_H */

