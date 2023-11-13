#ifndef DATANO_H
#define DATANO_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* colors */

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

/* end colors */

/*
*typedef struct linked_list
{
	char name;
	struct linked_list *next;
} list_names;

* typedef struct var_list_s
{
	char *value;
	list_names *names;
	struct var_list_s *next;
} list_d;
**/

/**
 * struct var_list_s - the linked list thet hold variables
 * @value: the variable value
 * @name: valriable name
 * @next: pointer of the next variable
 */
typedef struct var_list_s
{
	char *value;
	char *name;
	struct var_list_s *next;
} list_d;

/**
 * struct ht_data - the hash table
 * @type: type of data
 * @size: size of hash table
 * @array: the pointer of arrray that holds linked lists
 */
typedef struct ht_data
{
	char *type;
	int size;
	list_d **array;
} ht_d;

/**
 * struct data_s - the linked list thet hold variables
 * @dataHT: the pointer to the hash table
 * @name: data name
 * @next: pointer of the next data
 */
typedef struct data_s
{
	ht_d *dataHT;
	char *name;
	struct data_s *next;
} data_t;

/**
 * struct hashop_s - the hashing operations
 * @type: type of hash
 * @f: the operation
 */
typedef struct hashop_s
{
	char *type;
	size_t (*f)(char *key);
} hashop;

/**
 * struct used - golobal var that helps me in code
 * @data: ponter of the data used
 * @code: the current line of code as an array
 * @flag: the interpriter flags
 */
typedef struct used
{
	data_t *data;
	char **code;
	int flag;
	int bol;
} use;
extern use global;

/**
 * struct functions - functions infrastructer
 * @dofun: function name
 * @f: the soft function
 */
typedef struct functions
{
	char *dofun;
	size_t (*f)(ht_d obj);
} func;

/* functions */

data_t *
create_data(data_t **exist_data, char *name);
ht_d *create_data_type(data_t *data, char *name, char *type, int size);

size_t inthash(char *key);
size_t hash_it(char *name, char *type);

size_t hasdata(data_t *data, char *data_name, char *varname, char *value);
size_t hasvar(ht_d *table, char *varname);

size_t setdata(data_t *data, char *data_name, char *varname, char *value);
size_t setvar(ht_d *table, char *varname, char *value);

char *getdata(data_t *data, char *data_name, char *varname, char *value);
char *getvar(ht_d *table, char *varname);

void free_dataHT(ht_d *dataHT);
void freedata(data_t **exist_data);

/* getting code from file */
char **tokenize(char *str, int size);
void free2D(char **args);
int countargs(char **str, char c);

/* instractions */
void import(char *filepath, ht_d *obj);

int is_math(char *str);
char *check_math_op(int index, ht_d *obj, char *math);
void operation(ht_d *obj, char *var, int start);
void instractions(ht_d *obj, FILE *file, char *line, int numS);

/* global var */

#endif
