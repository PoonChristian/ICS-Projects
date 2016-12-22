#include <stdio.h>
#include <string.h>
#include <ctype.h>

void split_string(char string[1024], char* string_tokens[1024])
{
	const char delim[100] = " ";
	char* token = strtok(string, delim);
	int pos = 0;
	while (token != NULL)
	{
		string_tokens[pos++] = token;
		token = strtok(NULL, delim);
	}
}

void convert_text_to_morse(char alnum_array[40], char* morse_array[40], char* text)
{
	for (int i = 0; text[i]; ++i)
	{
		text[i] = toupper(text[i]);
		if (isalnum(text[i]))
		{
			char text_as_string[2];
			text_as_string[0] = text[i];
			text_as_string[1] = '\0';
			printf("%s   ", morse_array[strcspn(alnum_array, text_as_string)]);
			memset(text_as_string, 0, strlen(text_as_string));
		}
	}
}

int main()
{
	char alnum_array[40] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	char* morse_array[40] = {". -", "- . . .", "- . - .", "- . .", ".", ". . - .",
							"- - .", ". . . .", ". .", ". - - -", "- . -", ". - . .",
							"- -", "- .", "- - -", ". - - .", "- - . -", ". - .",
							". . .", "-", ". . -", ". . . -", ". - -", "- . . -",
							"- . - -", "- - . .", ". - - - -", ". . - - -", ". . . - -",
							". . . . -", ". . . . .", "- . . . .", "- - . . .", "- - - . .",
							"- - - - .", "- - - - -"};
	char input_string[1024];
	char* string_tokens[1024];
	fgets(input_string, 1024, stdin);
	input_string[strcspn(input_string, "\n")] = '\0';
	split_string(input_string, string_tokens);
	for (int i = 0; string_tokens[i]; ++i)
	{
		convert_text_to_morse(alnum_array, morse_array, string_tokens[i]);
		printf("       ");
	}
	printf("\n");
	return 0;
}
