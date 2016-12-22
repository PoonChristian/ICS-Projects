#include <stdio.h>
#include <string.h>

int rtod(char symbol)
{
	switch (symbol)
	{
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		case 'D':
			return 500;
		case 'M':
			return 1000;
		default:
			return 0;
	}
}

int add_to_decimal(char *roman_numeral, int decimal, int index)
{	
	for (int i = index; i > 0; --i)
	{
		int decimal_current = rtod(roman_numeral[i]); 
		int decimal_next = rtod(roman_numeral[i-1]);
		if (decimal_next < decimal_current)	{ decimal -= decimal_next; }
		else { decimal += decimal_next; }
    }
	return decimal;
}

int main()
{
    char roman_numeral[100];
	while (scanf("%99[^\n]%*c", roman_numeral) == 1)
	{	
		int index = strlen(roman_numeral) - 1;
		int decimal_v = rtod(roman_numeral[index]);
		decimal_v = add_to_decimal(roman_numeral, decimal_v, index);
		printf("%s => %d\n", roman_numeral, decimal_v);
	}
	return 0;
}
