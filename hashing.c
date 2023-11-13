#include "header/datano.h"

size_t inthash(char *key)
{
	return (atoi(key) % 10);
}

size_t strhash(char *key)
{
	return (*key % 255);
}
/* hash_d *(*f)(hash_d *__hash__, char *type_h, int size_h); */

size_t hash_it(char *name, char *type)
{
	int i = 0;
	hashop dictionary[] = {
		{"int", inthash},
		{"str", strhash},
		{NULL, NULL}};

	while (dictionary[i].type)
	{
		if (!strcmp(dictionary[i].type, type))
			return (dictionary[i].f(name));
		i++;
	}
	return (0);
}
