#include "header/datano.h"

size_t hasdata(data_t *data, char *data_name, char *varname, char *value)
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
	/* index = hash_it(value, data->dataHT->type); */
	/* tmp = data->dataHT->array[index]; */
	while (index < data->dataHT->size)
	{
		tmp = data->dataHT->array[index];
		while (tmp)
		{
			if (!strcmp(tmp->name, varname))
				return (1);
			tmp = tmp->next;
		}
		index++;
	}
	return (0);
}

size_t hasvar(ht_d *table, char *varname)
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
				return (1);
			tmp = tmp->next;
		}
		index++;
	}
	return (0);
}
