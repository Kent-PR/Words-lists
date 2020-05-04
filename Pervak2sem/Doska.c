#define _CRT_SECURE_NO_WARNINGS
#define ML 24

#include <stdio.h>
#include <math.h>

char Doska[ML][ML];
int sizeofdoska;
int figures_left;
int N, L, K;
int first_flag = 1;

FILE* fin; FILE* fout;
void openfire(void);
void closefire(void);

void set_figures_left(void);
void set_begins(int y, int x);
void set_doska(void);

void getsize(void);

void input(void);

void output(void);

void place(int y, int x);
void map_building(int tilenum);

void ban(int y, int x);
void queen(int y, int x);
void horse(int y, int x);
void king(int y, int x);

void check(void);

void delete_last(int num);


void print(void);


int main(void)
{
	openfire();
	input();
	set_doska();
	check();
	getsize();
	set_figures_left();
	map_building(0);
	if (first_flag) fputs("no solutions", fout);
	closefire();
	return 0;
}

void openfire(void)
{
	fin = fopen("input.txt", "r");
	fout = fopen("output.txt", "w");
}
void closefire(void)
{
	fclose(fin);
	fclose(fout);
}

void set_figures_left(void)
{
	figures_left = L;
}
void set_begins(int y, int x)
{
	Doska[y][x] = 'S';
}
void set_doska(void)
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (Doska[y][x] != 'S')
				Doska[y][x] = ' ';
		}
	}
}

void getsize(void)
{
	sizeofdoska = N * N;
}

void input(void)
{
	int c;
	int sw = 0;
	char matrix[3][50]; int counter[3] = { 0 };
	int i = 0;
	while (1)
	{
		c = fgetc(fin);
		if ((c == '\n') || (c == EOF)) break;
		if (c == ' ')
		{
			matrix[sw][i] = '\0';
			sw++;
			c = fgetc(fin);
			i = 0;
		}
		matrix[sw][i] = c;
		counter[sw]++;
		i++;
	}
	matrix[sw][i] = '\0';

	N = 0; L = 0; K = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = counter[i] - 1; j >= 0; j--)
		{
			if (!i)
			{
				N += (matrix[i][j] - 48) * pow(10, (counter[i] - 1 - j));
			}
			if (i == 1)
			{
				L += (matrix[i][j] - 48) * pow(10, (counter[i] - 1 - j));
			}
			if (i == 2)
			{
				K += (matrix[i][j] - 48) * pow(10, (counter[i] - 1 - j));
			}
		}
	}

	if (K)
	{
		while ((c = fgetc(fin)) != EOF)
		{
			int x_b[2], y_b[2];
			int x, y;
			int flag = 0;
			x_b[0] = c - 48;
			if ((c = fgetc(fin)) != ' ')
			{
				x_b[1] = c - 48;
				flag++;
			}
			if (flag)
			{
				x = x_b[0] * 10 + x_b[1];
				c = fgetc(fin);
			}
			else
				x = x_b[0];
			c = fgetc(fin);
			flag = 0;

			y_b[0] = c - 48;
			if ((c = fgetc(fin)) != '\n')
			{
				y_b[1] = c - 48;
				flag++;
			}
			if (flag)
			{
				y = y_b[0] * 10 + y_b[1];
				c = fgetc(fin);
			}
			else
				y = y_b[0];

			set_begins(y, x);

		}
	}
}

void output(void)
{
	if (!first_flag) fputc('\n', fout);
	first_flag = 0;
	int flag = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((Doska[i][j] == '*') || (Doska[i][j] == 'S'))
			{
				if (flag) fputc(' ', fout);
				fputc('(', fout);
				if (j < 10)
				{
					fputc(j + 48, fout);
				}
				else
				{
					fputc((j / 10) + 48, fout);
					fputc((j % 10) + 48, fout);
				}
				fputc(',', fout);
				if (i < 10)
				{
					fputc(i + 48, fout);
				}
				else
				{
					fputc((i / 10) + 48, fout);
					fputc((i % 10) + 48, fout);
				}
				fputc(')', fout);
				flag = 1;
			}
		}
	}
}

void place(int y, int x)
{
	Doska[y][x] = '*';
	figures_left--;
	//print();
	check();
	//print();
}
void map_building(int tilenum)
{
	int counter = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((counter >= tilenum) && (Doska[i][j] == ' '))
			{
				tilenum = counter;
				place(i, j);
				if (!figures_left)
				{
					//print();
					output();
					delete_last(tilenum);
				}
				else
				{
					map_building(tilenum);
					delete_last(tilenum);
				}
			}
			counter++;
		}
	}
}

void ban(int y, int x)
{

	king(y, x);
	horse(y, x);
	//queen(y, x);

}

void queen(int y, int x)
{
	int k = 0;
	while (k < 24)
	{
		if ((x - k) >= 0)
		{
			if (Doska[y][x - k] == ' ')
				Doska[y][x - k] = '#';
		}
		if ((x + k) < N)
		{
			if (Doska[y][x + k] == ' ')
				Doska[y][x + k] = '#';
		}
		if ((y - k) >= 0)
		{
			if (Doska[y - k][x] == ' ')
				Doska[y - k][x] = '#';
		}
		if ((y + k) < N)
		{
			if (Doska[y + k][x] == ' ')
				Doska[y + k][x] = '#';
		}
		k++;
	}
	//

	//diag
	k = 0;
	while (k < 24)
	{

		if (((x + k) < N) && ((y + k) < N))
		{
			if (Doska[y + k][x + k] == ' ')
			{
				Doska[y + k][x + k] = '#';
			}
		}
		if (((x + k) < N) && ((y - k) >= 0))
		{
			if (Doska[y - k][x + k] == ' ')
			{
				Doska[y - k][x + k] = '#';
			}
		}
		if (((x - k) >= 0) && ((y + k) < N))
		{
			if (Doska[y + k][x - k] == ' ')
			{
				Doska[y + k][x - k] = '#';
			}
		}
		if (((x - k) >= 0) && ((y - k) >= 0))
		{
			if (Doska[y - k][x - k] == ' ')
			{
				Doska[y - k][x - k] = '#';
			}
		}
		k++;
	}
	//
}
void horse(int y, int x)
{
	if ((x + 2) < N)
	{
		if ((y - 1) >= 0)
		{
			if (Doska[y - 1][x + 2] == ' ')
				Doska[y - 1][x + 2] = '#';
		}
		if ((y + 1) < N)
		{
			if (Doska[y + 1][x + 2] == ' ')
				Doska[y + 1][x + 2] = '#';
		}
	}
	if ((x - 2) >= 0)
	{
		if ((y - 1) >= 0)
		{
			if (Doska[y - 1][x - 2] == ' ')
				Doska[y - 1][x - 2] = '#';
		}
		if ((y + 1) < N)
		{
			if (Doska[y + 1][x - 2] == ' ')
				Doska[y + 1][x - 2] = '#';
		}
	}
	if ((y + 2) < N)
	{
		if ((x - 1) >= 0)
		{
			if (Doska[y + 2][x - 1] == ' ')
				Doska[y + 2][x - 1] = '#';
		}
		if ((x + 1) < N)
		{
			if (Doska[y + 2][x + 1] == ' ')
				Doska[y + 2][x + 1] = '#';
		}
	}
	if ((y - 2) >= 0)
	{
		if ((x - 1) >= 0)
		{
			if (Doska[y - 2][x - 1] == ' ')
				Doska[y - 2][x - 1] = '#';
		}
		if ((x + 1) < N)
		{
			if (Doska[y - 2][x + 1] == ' ')
				Doska[y - 2][x + 1] = '#';
		}
	}
}
void king(int y, int x)
{
	if ((x + 1) < N)
	{
		if (Doska[y][x + 1] == ' ')
			Doska[y][x + 1] == '#';
		if ((y + 1) < N)
		{
			if (Doska[y + 1][x + 1] == ' ')
				Doska[y + 1][x + 1] == '#';
		}
		if ((y - 1) >= 0)
		{
			if (Doska[y - 1][x + 1] == ' ')
				Doska[y - 1][x + 1] == '#';
		}
	}
	if ((x - 1) >= 0)
	{
		if (Doska[y][x - 1] == ' ')
			Doska[y][x - 1] == '#';
		if ((y + 1) < N)
		{
			if (Doska[y + 1][x - 1] == ' ')
				Doska[y + 1][x - 1] == '#';
		}
		if ((y - 1) >= 0)
		{
			if (Doska[y - 1][x - 1] == ' ')
				Doska[y - 1][x - 1] == '#';
		}
	}
}

void check(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Doska[i][j] == '#')
				Doska[i][j] = ' ';
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((Doska[i][j] == '*') || (Doska[i][j] == 'S'))
			{
				ban(i, j);
			}
		}
	}
}

void delete_last(int num)
{
	int counter = 0;
	int flag = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (counter == num)
			{
				Doska[i][j] = ' ';
				//print();
				check();
			}
			counter++;
		}
	}
	//	print();
	figures_left++;
}



void print(void)
{
	system("cls");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("(%c)", Doska[i][j]);
		}
		printf("\n");
	}
	getchar();
}