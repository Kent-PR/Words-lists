#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 10000
#define NAME 33

#include <stdio.h>
#include <string.h>
#include <math.h>

int buffer[2][MAX_LEN];

FILE* fin; 
FILE* fout;

void bufering();
void output(int end);
void analysis(int end);
void clear(void);

int main(void)
{
	FILE* project = fopen("project.txt", "r");
	char array_num[MAX_LEN];
	fgets(array_num, MAX_LEN, project);
	int num = 0, len = strlen(array_num)-1;
	for (int i = 0; i < len; i++)
	{
		num += ((int)array_num[len - i - 1] - 48) * pow(10, i);
	}
	while (num>0)
	{
		char NOF[NAME]; char NOUT[NAME];
		fgets(NOF, NAME, project);
		if(NOF[strlen(NOF) - 1] == '\n') NOF[strlen(NOF)-1]='\0';
		strcpy(NOUT, NOF);
		NOUT[strlen(NOF) - 1] = '\0';
		strcat(NOUT, "wc");
		fin = fopen(NOF, "r");
		fout = fopen(NOUT, "w");
		bufering();

		fclose(fout);
		fclose(fin);

		clear();
		num--;
	}
	fclose(project);
	return 0;
}

void clear(void)
{
	for (int i = 0; i < MAX_LEN; i++)
	{
		buffer[0][i] = 0;
		buffer[1][i] = 0;
	}
}

void bufering(void)
{
	int c;
	int counter = 0;
	while ((c = fgetc(fin)) != EOF)
	{
		buffer[0][counter] = c;
		counter++;
	}
	analysis(counter);
}

void analysis(int end)
{
	for (int i = 0; i < end; i++)
	{
		if (buffer[0][i] == '\'')
		{
			buffer[1][i] = 4;
		}
		if (buffer[0][i] == '\"')
		{
			buffer[1][i] = 3;
		}
		if (buffer[0][i] == '/')
		{
			if (buffer[0][i+1] == '/')
			{
				buffer[1][i] = 1;
			}
			if (buffer[0][i + 1] == '*')
			{
				buffer[1][i] = 2;
			}
			if (buffer[0][i - 1] == '*')
			{
				buffer[1][i] = 21;
			}
		}
		if (buffer[0][i] == '\\' && buffer[0][i + 1] == '\n')
		{
			buffer[1][i+1] == 5;
		}
	}
	output(end);
}

void output(int end)
{
	for (int i = 0; i < end; i++)
	{
		if(buffer[1][i]==0)
		{
			fputc(buffer[0][i], fout);
		}
		if (buffer[1][i]==4)
		{
			fputc(buffer[0][i], fout);
			i++;
			while (buffer[1][i] != 4)
			{
				fputc(buffer[0][i], fout);
				i++;
			}
			fputc(buffer[0][i], fout);
		}
		if (buffer[1][i]==3)
		{
			fputc(buffer[0][i], fout);
			i++;
			while (buffer[1][i] != 3)
			{
				fputc(buffer[0][i], fout);
				i++;
			}
			fputc(buffer[0][i], fout);
		}
		if (buffer[1][i] == 2)
		{
			i++;
			while (buffer[1][i] != 21)
			{
				i++;
			}
		}
		if (buffer[1][i] == 1)
		{
			i++;
			while (buffer[0][i] != '\n' || buffer[1][i]!=0)
			{
				i++;
			}
		}
	}
}