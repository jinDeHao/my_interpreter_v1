#include "header/datano.h"
void import(char *filepath, ht_d *obj)
{
	FILE *subfile = fopen(filepath, "r");
	char line[1024];

	free2D(global.code);
	while (fgets(line, 1024, subfile))
	{
		line[strcspn(line, "\n")] = '\0';
		char *fixedLine = line;
		int numS = countargs(&fixedLine, ' ');

		/* tokenaize */
		global.code = tokenize(fixedLine, numS);
		instractions(obj, subfile, line, numS);
	}
	fclose(subfile);
}
