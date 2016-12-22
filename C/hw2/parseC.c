#include <stdio.h>
#include <string.h>
#include <ctype.h>

int peekc()
{
	int c;
	c = getchar();
	ungetc(c, stdin);
	return c;
}

void parse_error(char *msg, char ch)
{
	fprintf(stderr, "ERROR: %s: %c\n", msg, ch);	
}

void getToken()
{
	int in_ch;
	char lexeme[BUFSIZ];
	int lexeme_pos = 0;
	while ((in_ch = getchar()) != EOF)
	{
		switch (in_ch)
		{
			case ' ':
			case '\t':
			case '\n':
				break;
			case '&':
			case '|': 
			case '<':
			case '>': 
			case '#':
			case '.':
			case ':':
			case '_':
			case '[':
			case ']':
			case '(':
			case ')':
			case '*':
			case '\'':
			case '"':
			case '/':
			case '%':
			case '+':
			case '-':
			{
				printf("%c\n", in_ch);
				break;
			}
			default:
			{
				char next_char = peekc();
				if ((isdigit(next_char)) || (isalpha(next_char)))
				{
					lexeme[lexeme_pos++] = in_ch;
				}
				else if (!(isdigit(next_char)) || !(isalpha(next_char)))
				{
					lexeme[lexeme_pos++] = in_ch;
					printf("%s\n", lexeme);
					memset(lexeme, 0, sizeof(lexeme));
					lexeme_pos = 0;
				}
				else
					parse_error("Illegal character", in_ch);
			}
		}
	}
}

int main() /* EXCEEDING 5 LINES BY 1 */ 
{
	getToken();
	return 0;
}
