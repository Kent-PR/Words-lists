#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <malloc.h>

int N, S;
int* Arr;

void input(void)
{
	scanf("%d", &N);
	Arr = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &Arr[i]);
	}
	scanf("%d", &S);
}

int middle(int begin, int end)
{
	int interval = end - begin;
	int shift = interval / 2;
	int destiny = begin + shift;
	return(destiny);
}

int bin_search(int begin, int end)
{
	if (S > Arr[begin] && S < Arr[end] && (end - begin) <= 1)
	{
		return -1;
	}
	int tmp = middle(begin, end);
	if (S < Arr[tmp]) 
	{
		return(bin_search(begin, tmp));
	}
	if (S > Arr[tmp])
	{
		return(bin_search(tmp, end));
	}
	if (S == Arr[tmp])
		return(tmp);
}

int main(void) 
{
	input();
	int index = bin_search(0, N);
	if (index > -1) 
	{ printf("%d", index); }
	else
	{
		printf("notfound");
	}
	return 0;
}