#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

int* buffer;
FILE* fin; FILE* fout; FILE* FROM; FILE* TO;

typedef struct finite
{
	int N_to; // длина слова, на которое заменяем
	int* inscription_to; // слово, на которое заменяем
}minor;

typedef struct initial
{
	int num; // порядковый номер структурной единицы в списке
	int N_from; // длина слова, которое заменяем
	int* inscription_from; // слово, которое меняем
	bool does_not_contradict; // переменная, отвечающася за соответствие
	struct finite* replacement; // ссылка на структуру "finite"
	struct initial* next; // указатель на следующий элемент
}major;

struct NODE* ROOT = NULL;
struct NODE* HEAD = NULL;

void opening(void);
void key_words_reading(FILE* FROM, FILE* TO);
void addelem_initial(int number, char* word1, int sym_cnt1, char* word2, int sym_cnt2);
struct list* addelem_finite(char* word2, int sym_cnt2);
void listprint(void);

int main(void)
{
	opening();
	key_words_reading(FROM, TO);
	listprint();
	return 0;
}

void opening(void)
{
	FROM = fopen("1.txt", "r");
	TO = fopen("2.txt", "r");
	fin = fopen("in.xml", "r");
	fout = fopen("out.xml", "w");
}

struct list* addelem_finite(char* word2, int sym_cnt2)
{
	struct finite* lst;

	lst = /*(struct finite*)*/malloc(sizeof(struct finite) + sizeof(int*) * sym_cnt2);
	lst->N_to = sym_cnt2;
	//
	lst->inscription_to = malloc(sym_cnt2 * sizeof(int));
	//memcpy(word, word2, sym_cnt2); // копирует (sym_cnt2) символов из word2 в поле данных "inscription_to"
	for (int i = 0; i < sym_cnt2; i++)
	{
		*((lst->inscription_to) + i) = (int)word2[i];
	}
	//
	return(lst);
}

void addelem_initial(int number, char* word1, int sym_cnt1, char* word2, int sym_cnt2)
{
	struct initial* lst;
	if (!number) // если номер = 0 (то есть список не создан), то создаём первый элемент списка и присваиваем ему "статус" корня
	{
		lst = /*(struct initial*)*/malloc(sizeof(struct initial) + sizeof(int*) * sym_cnt1); // выделение памяти под корень списка
		ROOT = lst;
	}
	else
	{
		lst = HEAD;
		struct initial* tmp;

		tmp = /*(struct initial*)*/malloc(sizeof(struct initial));
		lst->next = tmp; // связываем созданный только что узел с "головой состава"
		lst = lst->next; // переход на этот самый узел
		free(tmp);
		
	}
	lst->does_not_contradict = false;
	lst->num = number;
	lst->N_from = sym_cnt1;
	//
	lst->inscription_from = malloc(sym_cnt1 * sizeof(int));
	for (int i = 0; i < sym_cnt1; i++)
	{
		*((lst->inscription_from)+i) = (int)word1[i];
	}
	
	//
	lst->replacement = addelem_finite(word2, sym_cnt2);

	HEAD = lst;
	lst->next = NULL; // это (пока что) последний узел списка
}

void key_words_reading(FILE* FROM, FILE* TO)
{
	int counter = 0, len1=0, len2=0;

	while (1)
	{
		if (feof(FROM)) return;
		char tmp1[20], tmp2[20];
		/*int* word1;
		int* word2;*/
		
		fscanf(FROM, "%s", &tmp1);
		len1 = strlen(tmp1);
		/*word1 = malloc(len1 * sizeof(int));
		for (int i = 0; i < len1; i++)
		{
			word1[i] = (int)tmp1[i];
		}*/
		
		fscanf(TO, "%s", &tmp2);
		len2 = strlen(tmp2);
		/*word2 = malloc(len2 * sizeof(int));
		for (int i = 0; i < len2; i++)
		{
			word2[i] = tmp2[i];
		}*/

		addelem_initial(counter, tmp1, len1, tmp2, len2);
		counter++;
	}
}

void listprint(void)
{
	struct initial* lst = ROOT;
	while (lst != NULL)
	{
		for (int i = 0; i < lst->N_from; i++)
		{
			printf("%c", (char)*((lst->inscription_from) + i));
		}
		printf(" changes to ");

		for (int i = 0; i < lst->replacement->N_to; i++)
		{
			printf("%c", (char)*((lst->replacement->inscription_to)+i));
		}
		printf("\n");

		lst = lst->next;
	}
	free(lst);
}