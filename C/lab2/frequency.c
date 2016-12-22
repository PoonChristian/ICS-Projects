#include <stdio.h>
#include <string.h>

FILE* open_file(char* filename, char* mode)
{
	FILE* filepath = fopen(filename, mode);
	return filepath;
}

int inc_whitespace_count(char code, int whitespace_count)
{
	switch (code)
	{	
		case ' ':
		case '\t':
		case '\n':
			whitespace_count++;
			return whitespace_count;
		default:
			return whitespace_count;
	}
}

int inc_other_count(char code, int other_count)
{
	if (code < 32)
	{
		switch (code)
		{
			case '\t':
			case '\n':
				return other_count;;
			default:
			{
				other_count++;
				return other_count;
			}
		}
	}
	return other_count;
} 

int main(int argc, char* argv[])
{
	char* filename = argv[1];
	FILE* filepath = open_file(filename, "r");
	int frequency_array[127] = {0};
	int whitespace_count = 0;
	int other_count = 0;
	char ascii;

	while (fscanf(filepath, "%c", &ascii) == 1)
	{
		whitespace_count = inc_whitespace_count(ascii, whitespace_count);
		other_count = inc_other_count(ascii, other_count);
		frequency_array[ascii]++;
	}
	
	for (int i = 32; i < 127; ++i)
	{
		if (frequency_array[i] > 0)
			printf("'%c' %d\n", i, frequency_array[i]);
	}
	printf("whitespace characters %d\n", whitespace_count);
	printf("other characters %d\n", other_count);
	return 0;
}
