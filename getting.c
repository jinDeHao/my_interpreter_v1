#include "header/datano.h"

char *getdata(data_t *data, char *data_name, char *varname, char *value)
{
	(void)value;
	size_t index = 0;
	list_d *tmp;

	while (data)
	{
		if (!strcmp(data->name, data_name))
			break;
		data = data->next;
	}
	if (!data || !data->dataHT)
		return (0);
	while (index < data->dataHT->size)
	{
		tmp = data->dataHT->array[index];
		while (tmp)
		{
			if (!strcmp(tmp->name, varname))
				return (tmp->value);
			tmp = tmp->next;
		}
		index++;
	}
	return (NULL);
}

char *getvar(ht_d *table, char *varname)
{
	size_t index = 0;
	list_d *tmp;

	if (!table)
		return (0);
	while (index < table->size)
	{
		tmp = table->array[index];
		while (tmp)
		{
			if (!strcmp(tmp->name, varname))
				return (tmp->value);
			tmp = tmp->next;
		}
		index++;
	}
	fprintf(stderr, RED "ERROR: no variable %s in this table :**\n" RESET, varname);
	freedata(&global.data);
	exit(1);
}
