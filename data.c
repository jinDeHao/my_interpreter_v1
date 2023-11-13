#include "header/datano.h"
use global;

void instractions(ht_d *obj, FILE *file, char *line, int numS)
{
	if (numS == 2 && !strcmp(global.code[0], "import"))
	{
		import(global.code[1], obj);
		return;
	}
	if (numS == 3 && !strcmp(global.code[1], "="))
	{
		if (hasvar(obj, global.code[2]))
			setvar(obj, global.code[0], getvar(obj, global.code[2]));
		else
			setvar(obj, global.code[0], global.code[2]);
	}
	if (numS >= 5 && !strcmp(global.code[1], "="))
	{
		operation(obj, global.code[0], 2);
	}
	if (numS == 2 && !strcmp(global.code[0], "show"))
	{
		if (hasvar(obj, global.code[1]))
			printf("%s\n", getvar(obj, global.code[1]));
	}
	if (numS >= 2 && !strcmp(global.code[0], "if"))
	{
		operation(obj, "__tmp", 1);
		int i = 0;
		if (!atoi(getvar(obj, "__tmp")))
		{
			while (global.code[0][0] != ';')
			{
				if (!i)
					free2D(global.code);
				fgets(line, 1024, file);
				line[strcspn(line, "\n")] = '\0';
				char *fixedLine = line;
				int numS = countargs(&fixedLine, ' ');

				/* tokenaize */
				global.code = tokenize(fixedLine, numS);
			}
		}
	}
	free2D(global.code);
}

void operation(ht_d *obj, char *var, int start)
{
	char math[1024] = "";
	char *operation = check_math_op(start, obj, math);
	if (!operation)
	{
		fprintf(stderr, "**********not math\n");
		exit(1);
	}
	FILE *fp;
	char result_buffer[1024];
	char echobuf[1032] = "echo -n $((";

	// Open a pipe to a command with "r" for reading
	operation = strcat(operation, "))");
	strcat(echobuf, operation);
	fp = popen(echobuf, "r");
	if (fp == NULL)
	{
		perror("popen");
		exit(EXIT_FAILURE);
	}

	// Read the output of the command
	fgets(result_buffer, sizeof(result_buffer), fp);

	// Close the pipe
	if (pclose(fp) == -1)
	{
		perror("pclose");
		exit(EXIT_FAILURE);
	}
	setvar(obj, var, result_buffer);
	/* +++++++++++++++++++++++++++++++++ */
}

int is_math(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 40 || str[i] > 57)
		{
			if (str[i] != '&' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '=' && str[i] != '!')
				return (0);
		}
		i++;
	}
	return (1);
}

char *check_math_op(int index, ht_d *obj, char *math)
{
	int i = index;
	char *tmp;

	while (global.code[i])
	{
		if (hasvar(obj, global.code[i]))
		{
			tmp = global.code[i];
			global.code[i] = strdup(getvar(obj, global.code[i]));
			free(tmp);
		}
		if (!is_math(global.code[i]))
			return (NULL);
		strcat(math, global.code[i]);
		i++;
	}
	return (math);
}

int main(int argc, char *argv[])
{
	data_t *ldata = NULL;

	if (argc < 2)
	{
		fprintf(stderr, RED "Error usage\n");
		return (1);
	}
	if (argc > 2 && *argv[1] == '-')
	{
		if (*(argv[1] + 1) == 'd')
			global.flag = 1;
	}
	int fileIndex = argc - 1;

	FILE *file = fopen(argv[fileIndex], "r");
	char line[1024];

	if (!file)
	{
		fprintf(stderr, RED "Error file doesn't exist\n" RESET);
		return (1);
	}
	create_data(&ldata, argv[fileIndex]);

	ht_d *obj = create_data_type(ldata, argv[fileIndex], "str", 256);

	while (fgets(line, 1024, file))
	{
		line[strcspn(line, "\n")] = '\0';
		char *fixedLine = line;
		int numS = countargs(&fixedLine, ' ');

		/* tokenaize */
		global.code = tokenize(fixedLine, numS);

		/* instractions */
		instractions(obj, file, line, numS);
		// if (numS == 2 && !strcmp(global.code[0], "import"))
		// {
		// 	import(global.code[1], obj);
		// 	continue;
		// }
		// if (numS == 3 && !strcmp(global.code[1], "="))
		// {
		// 	if (hasvar(obj, global.code[2]))
		// 		setvar(obj, global.code[0], getvar(obj, global.code[2]));
		// 	else
		// 		setvar(obj, global.code[0], global.code[2]);
		// }
		// if (numS >= 5 && !strcmp(global.code[1], "="))
		// {
		// 	operation(obj, global.code[0], 2);
		// }
		// if (numS == 2 && !strcmp(global.code[0], "show"))
		// {
		// 	if (hasvar(obj, global.code[1]))
		// 		printf("%s\n", getvar(obj, global.code[1]));
		// }
		// if (numS > 2 && !strcmp(global.code[0], "if"))
		// {
		// 	operation(obj, "__tmp", 1);
		// 	while (global.code[0][0] != ';')
		// 	{
		// 		free2D(global.code);
		// 		fgets(line, 1024, file);
		// 		line[strcspn(line, "\n")] = '\0';
		// 		char *fixedLine = line;
		// 		int numS = countargs(&fixedLine, ' ');

		// 		/* tokenaize */
		// 		global.code = tokenize(fixedLine, numS);
		// 		if (getvar(obj, '__tmp'))
		// 		{
		// 		}
		// 	}
		// }
		// free2D(global.code);
	}
	fclose(file);
	freedata(&global.data);
	return (0);
}
