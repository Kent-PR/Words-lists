
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int schit = 0, schit1 = 0,col = 0, col1 = 0;
	int i = 0;

	
	
	int len, dlin = 0;

	int N;

	FILE* txt = fopen("project.txt", "r");

	if (txt == 0)
	{ printf("Osh\n"); }

	fscanf(txt, "%d", &N);

	char A[100] = { 0 };

	fgets(A, 100, txt);
	for (i = 0; i < N; i++)
	{
		schit1 = 0;
		schit = 0;
		col = 0;
		col1 = 0;

		int dlinD = 0;
		int vs = 0;
		int c = 0;
		
		char  poln[53000] = { 0 };
		char g[100] = { 0 };
		char k[100] = { 0 };

		fgets(g, 100, txt);

		len = strlen(g);

		if (i < N - 1)
		{ len--; }
		int ii = 0;
		for (; ii < len; ii++)
			k[ii] = g[ii];

		FILE* file = fopen(k, "r");
		g[len - 1] = 'w';
		g[len] = 'c';

		if (file == 0) printf("osh 2");
		FILE* novF = fopen(g, "w");

		while (feof(file) == 0)
		{
			char x[5000] = { '\0' };
			fgets(x, 5000, file);

			dlin = strlen(x);
			dlinD = dlinD + dlin;
			for (int q = dlinD - dlin, t = 0; q < dlinD; q++, t++)
			{
				poln[q] = x[t];
			}
		}
		int q = 0;
		for ( q = 0; q < dlinD && poln[q] != '\0'; q++)
		{
			if (col == 1 && poln[q] != '\'')
			{
				if (poln[q] == '\\' && (poln[q + 1] == '\'' || poln[q + 1] == '\\'))
					schit++;
				else { schit = 0; }
			}
			if (col1 == 1 && poln[q] != '\"' && poln[q] != '\n')
			{
				if (poln[q] == '\\' && ((poln[q + 1] == '\"') || poln[q + 1] == '\\' || poln[q + 1] == '\n'))
					schit1++;
				else 
				{ schit1 = 0; }
			}
			if (poln[q] == '\'' && col1 == 0 && vs == 0 && c == 0 && col == 1)//0
			{
				if (schit % 2 == 0)
				{
					col = 0;
				}
				schit = 0;
			}
			else if (poln[q] == '\'' && col1 == 0 && vs == 0 && c == 0 && col == 0)//1
			{
				col = 1;
				
			}
			else if (poln[q] == '\"' && col1 == 0 && vs == 0 && c == 0 && col == 0)
			{
				col1 = 1;
			}
			else if (poln[q] == '\"' && col1 == 1 && vs == 0 && c == 0 && col == 0)
			{
				if (schit1 % 2 == 0)
				{
					col1 = 0;
				}
				schit1 = 0;
			}
			if (col1 == 0 && poln[q] == '/' && poln[q + 1] == '/' && vs == 0 && col == 0)
			{
				c = 1;
			}
			else if (col1 == 0 && poln[q] == '/' && poln[q + 1] == '*' && c == 0 && col == 0 && poln[q + 2] != '/n' && vs == 0)
			{
				vs = 1;
				poln[q + 1] = ' ';
			}
			else if (col1 == 0 && poln[q] == '*' && poln[q + 1] == '/' && c == 0 && col == 0 && poln[q + 2] != '/n' && vs == 1)
			{
				vs = 0;
				poln[q] = ' ';
				poln[q + 1] = ' ';
			}
			if (poln[q] != '\\' && vs == 1 && col1 == 0 && c == 0 && poln[q] != '\n' && col == 0)
			{
				poln[q] = ' ';
			}
			else if (poln[q] != '\\' && vs == 0 && col1 == 0 && c == 1 && poln[q] != '\n' && col == 0)
			{
				poln[q] = ' ';
			}
			if (poln[q] != '\\' && poln[q + 1] == '\n')
			{
				c = 0;
				col1 = 0;
			}
			else if (poln[q] == '\\' && poln[q + 1] == '\n' && (schit1 % 2 == 0) && col1 == 1)
				col1 = 0;
			if (poln[q] == '\n')
			{
				col = 0;
				schit = 0;
				schit1 = 0;
			}
			if (poln[q] == '\\' && poln[q + 1] != '\n' && vs == 0 && col1 == 0 && c == 1 && poln[q] != '\n' && col == 0)
				poln[q] = ' ';
			else if (poln[q] == '\\' && poln[q + 1] != '\n' && vs == 1 && col1 == 0 && c == 0 && poln[q] != '\n' && col == 0)
				poln[q] = ' ';
			else if (poln[q] == '\\' && poln[q + 1] == '\n' && col1 == 0 && (c == 1 || vs == 1))
				poln[q] = ' ';
			fprintf(novF, "%c", poln[q]);
		}
		fclose(file);

		fclose(novF);
	}
	fclose(txt);




















	return 0;
}