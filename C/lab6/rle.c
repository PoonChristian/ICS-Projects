#include <stdio.h>
#include <string.h>

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

void char_check(char alphabet[26], char c, int* count)
{
	for (int i = 0; alphabet[i]; ++i)
	{
		if (c == alphabet[i])
		{
			*count += 1;
		}
	}
}

void scan_characters(char c, char alphabet[26], int count)
{
	while ((c = getchar()) != '\n')
	{
		char_check(alphabet, c, &count);
		char next = peekc();
		if (c != next && strchr(alphabet, c) != NULL) 
		{
			printf("%d%c", count, c);
			count = 0;
		}
	}
	printf("\n");	
}

int main()
{
	char alphabet[26];
	init_alphabet(alphabet);
	int count = 0;
	char c;
	scan_characters(c, alphabet, count);
	return 0;
}
