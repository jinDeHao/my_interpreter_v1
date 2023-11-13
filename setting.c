#include "header/datano.h"

size_t setdata(data_t *data, char *data_name, char *varname, char *value)
{
	size_t index, i = 0;
	list_d *tmp, *nd;

	while (data)
	{
		if (!strcmp(data->name, data_name))
			break;
		data = data->next;
	}
	if (!data || !data->dataHT)
	{
		return (0);
	}
	index = hash_it(value, data->dataHT->type);
	tmp = data->dataHT->array[index];
	while (i < data->dataHT->size)
	{
		tmp = data->dataHT->array[i];
		while (tmp)
		{
			if (!strcmp(tmp->name, varname))
			{
				free(tmp->value);
				tmp->value = strdup(value);
				return (1);
			}
			tmp = tmp->next;
		}
		i++;
	}
	tmp = data->dataHT->array[index];
	nd = malloc(sizeof(list_d));
	if (!nd)
		return (-1);
	nd->name = strdup(varname);
	nd->value = strdup(value);
	nd->next = tmp;
	data->dataHT->array[index] = nd;

	return (1);
}

size_t setvar(ht_d *table, char *varname, char *value)
{
	size_t index, i = 0;
	list_d *tmp, *nd;

	if (!table)
		return (0);
	index = hash_it(value, table->type);
	tmp = table->array[index];
	while (i < table->size)
	{
		tmp = table->array[i];
		while (tmp)
		{
			if (!strcmp(tmp->name, varname))
			{
				free(tmp->value);
				tmp->value = strdup(value);
				return (1);
			}
			tmp = tmp->next;
		}
		i++;
	}
	tmp = table->array[index];
	nd = malloc(sizeof(list_d));
	if (!nd)
		return (-1);
	nd->name = strdup(varname);
	nd->value = strdup(value);
	nd->next = tmp;
	table->array[index] = nd;

	return (1);
}
