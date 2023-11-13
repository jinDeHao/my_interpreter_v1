#include "header/datano.h"
/**
 * create_data - creates a data and give it a name
 * @exist_data: it can be the old data if you want to append data,
 * but if you want to create a new data make it a pointer
 * that hold and address of null
 * @name: the name of the new data
 * Return: the created data
 */
data_t *create_data(data_t **exist_data, char *name)
{
	data_t *new_data = malloc(sizeof(data_t));

	if (!new_data)
		return (NULL);
	fprintf(stdout, global.flag
						? GREEN "data created succesfuly" RESET "\n"
						: "");
	/* ---------------------------------- */
	/* ---------------------------------- */
	new_data->name = strdup(name);
	new_data->dataHT = NULL;
	new_data->next = *exist_data;
	*exist_data = new_data;
	/* intializate the global data */
	global.data = new_data;
	/* +++++++++++++++++++++ */
	return (new_data);
}
/**
 * free_dataHT - free specific hash table
 * @dataHT: hash table to free
 */
void free_dataHT(ht_d *dataHT)
{
	if (!dataHT)
		return;
	free(dataHT->type);
	for (size_t i = 0; i < dataHT->size; i++)
	{
		list_d *tmp;

		while (dataHT->array[i])
		{
			tmp = dataHT->array[i];
			dataHT->array[i] = dataHT->array[i]->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
	}
	free(dataHT->array);
	free(dataHT);
}

/**
 * freedata - free the entire data
 * @exist_data: data to free
 */
void freedata(data_t **exist_data)
{
	data_t *tmp;

	while (*exist_data)
	{
		tmp = *exist_data;
		*exist_data = (*exist_data)->next;
		free_dataHT(tmp->dataHT);
		free(tmp->name);
		free(tmp);
	}
	fprintf(stdout, global.flag ? GREEN "data freed succesfuly" RESET "\n" : "");
}

/**
 * create_data_type - creates a hash table that hold a type of data
 * @data: where my data is stored
 * @name: the name of my data where i want to create a hash table
 * @type: the type of hash table data
 * @size: size of the hash table
 * Return: the hash table created
 */
ht_d *create_data_type(data_t *data, char *name, char *type, int size)
{
	while (data)
	{
		if (!strcmp(data->name, name))
			break;
		data = data->next;
	}
	if (!data)
	{
		fprintf(stdout,
				RED "<error>" RESET "\n" RED
					"Disc: no data find with the name %s" RESET "\n",
				name);
		return (NULL);
	}
	data->dataHT = malloc(sizeof(ht_d));
	if (!data->dataHT)
		return (NULL);
	data->dataHT->size = size;
	data->dataHT->array = malloc(sizeof(list_d *) * data->dataHT->size);
	if (!data->dataHT->array)
	{
		free(data->dataHT);
		return (NULL);
	}
	for (size_t i = 0; i < data->dataHT->size; i++)
		data->dataHT->array[i] = NULL;

	data->dataHT->type = strdup(type);
	fprintf(stdout,
			global.flag
				? BLUE "data of type " RESET "%s" BLUE " with size " RESET
					   "%d" BLUE " created in <" RESET "%s" BLUE "> data" RESET "\n"
				: "",
			data->dataHT->type, data->dataHT->size, data->name);
	return (data->dataHT);
}
