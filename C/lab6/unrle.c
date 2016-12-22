#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int peekc()
{
	int c;
	c = getchar();
	ungetc(c, stdin);
	return c;
}

void init_alphabet(char alphabet[26])
{
	int pos = 0;
	for (int i = 'A'; i <= 'Z'; ++i)
		alphabet[pos++] = i;
	alphabet[pos] = '\0';
}

int char_check(int c)
{
	if (c >= 65 && c <= 90)
	{
		return c;
	}
	return 0;
}

int digit_check(int c)
{
	if (c >= 48 && c <= 57)
	{
		return c;
	}
	return 0;
}

void print_character(char c, char next, char count[3], int* count_pos)
{
	for (int i = 0; i < atoi(count); ++i)
	{
		printf("%c", next);
		fflush(stdout);
	}
	memset(count, 0, strlen(count));
	*count_pos = 0;	
}

void scan_characters(char c, char count[3], int count_pos)
{
	while ((c = getchar()) != '\n')
	{
		char next = peekc();
		if (digit_check(c) != 0)
		{
			count[count_pos++] = c;
		}
		if (char_check(next) != 0)
		{
			print_character(c, next, count, &count_pos);
		}
	}
	printf("\n");	
}

int main()
{
	char alphabet[27];
	char count[3];
	int count_pos = 0;
	count[0] = '\0';
	init_alphabet(alphabet);
	char c;
	scan_characters(c, count, count_pos);
	return 0;
}
