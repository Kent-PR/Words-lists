#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

int* buffer;
FILE* fin; FILE* fout; FILE* FROM; FILE* TO;

typedef struct finite
{
	int N_to; // ����� �����, �� ������� ��������
	int* inscription_to; // �����, �� ������� ��������
}minor;

typedef struct initial
{
	int num; // ���������� ����� ����������� ������� � ������
	int N_from; // ����� �����, ������� ��������
	int* inscription_from; // �����, ������� ������
	bool does_not_contradict; // ����������, ����������� �� ������������
	struct finite* replacement; // ������ �� ��������� "finite"
	struct initial* next; // ��������� �� ��������� �������
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

	lst = (struct finite*)malloc(sizeof(struct finite));
	lst->N_to = sym_cnt2;
	//
	int* word = lst->inscription_to;
	word = (int*)malloc(sym_cnt2 * sizeof(int));
	//memcpy(word, word2, sym_cnt2); // �������� (sym_cnt2) �������� �� word2 � ���� ������ "inscription_to"
	for (int i = 0; i < sym_cnt2; i++)
	{
		word[i] = (int)word2[i];
	}
	free(word);
	//
	return(lst);
}

void addelem_initial(int number, char* word1, int sym_cnt1, char* word2, int sym_cnt2)
{
	struct initial* lst;
	if (!number) // ���� ����� = 0 (�� ���� ������ �� ������), �� ������ ������ ������� ������ � ����������� ��� "������" �����
	{
		lst = (struct initial*)malloc(sizeof(struct initial)); // ��������� ������ ��� ������ ������
		ROOT = lst;
	}
	else
	{
		lst = HEAD;
		struct initial* tmp;

		tmp = (struct initial*)malloc(sizeof(struct initial));
		lst->next = tmp; // ��������� ��������� ������ ��� ���� � "������� �������"
		lst = lst->next; // ������� �� ���� ����� ����
		free(tmp);
		
	}
	lst->does_not_contradict = false;
	lst->num = number;
	lst->N_from = sym_cnt1;
	//
	int* word = lst->inscription_from;
	word = (int*)malloc(sym_cnt1 * sizeof(int));
	for (int i = 0; i < sym_cnt1; i++)
	{
		word[i] = (int)word1[i];
	}
	//memcpy(word, word1, sym_cnt1); // �������� (sym_cnt1) �������� �� word1 � ���� ������ "inscription_from"
	free(word);
	//
	lst->replacement = addelem_finite(word2, sym_cnt2);

	HEAD = lst;
	lst->next = NULL; // ��� (���� ���) ��������� ���� ������
}

void key_words_reading(FILE* FROM, FILE* TO)
{
	int counter = 0, len1=0, len2=0;

	while (1)
	{
		if (feof(FROM)) return;
		char tmp1[100], tmp2[100];
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
		int* word1 = lst->inscription_from; //��������� �� ������, � ������� �������� ������ ����� (������� ��������)
		for (int i = 0; i < lst->N_from; i++)
		{
			char c = (char)word1[i];
			printf("%c", c);
		}
		printf(" changes to ");

		int* word2 = lst->replacement->inscription_to; //��������� �� ������, � ������� �������� ������ ����� (�� ������� ��������)
		for (int i = 0; i < lst->replacement->N_to; i++)
		{
			printf("%c", word2[i]);
		}
		printf("\n");

		lst = lst->next;
	}
	free(lst);
}