#include <string.h>
#include <stdio.h>

#define require(e) if (!(e)) fprintf(stderr, "FAILED line %d        %s: %s       %s\n", __LINE__, __FILE__, __func__, #e)


int CPstrlen(const char *str)
{
	int length = 0;
	for (int i = 0; str[i]; i++)
	{
		length++;
	}
	return length;
}

int CPstrcmp(const char *str1, const char *str2)
{
	int i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0' && str2[i] == '\0')	{ return 0; };
		i++;
	}
	return str1[i] - str2[i];
}

int CPstrncmp(const char *str1, const char *str2, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (str1[i] != str2[i])
			return str1[i] - str2[i]; 
	}
	return 0;
}

int CPstrspn(const char *str1, const char *str2)
{
	int i;
	for (i = 0; str1[i]; ++i)
	{
		if (str1[i] != str2[i])
			return i;
	}
	return i;
}

int CPstrcspn(const char *str1, const char *str2)
{
	int i;
	for (i = 0; str1[i]; ++i)
	{
		for (int j = 0; str2[j]; ++j)
		{
			if (str1[i] == str2[j])
				return i;
		}
	}
	return i;
}

char *CPstrcpy(char *dest, const char *src)
{
	int i;
	for (i = 0; src[i]; ++i)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return dest;
}

char *CPstrncpy(char *dest, const char *src, int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return dest;
}
char *CPstrchr(const char *str, int c)
{
	for (int i = 0; str[i]; ++i)
	{
		if (str[i] == c)
			return ((char *)str + i);
	}
	return NULL;
}

char *CPstrrchr(const char *str, int c)
{
	for (int i = CPstrlen(str); i > 0; --i)
	{
		if (str[i] == c)
			return ((char *)str + i);
	}
	return NULL;
}

char *CPstrcat(char *dest, const char *src)
{
	CPstrcpy(dest + CPstrlen(dest), src);
	return dest;
}

char *CPstrncat(char* dest, const char *src, int n)
{
	CPstrncpy(dest + CPstrlen(dest), src, n);
	return dest;
}

char *CPstrpbrk(const char *str1, const char *str2)
{
	char *str;
	int first_occurrence = CPstrcspn(str1, str2);
	str = CPstrchr(str1, str1[first_occurrence]);
	return str;
}

char *CPstrstr(const char *haystack, const char *needle)
{
	char *str = CPstrchr(haystack, *needle);
	if (str != NULL)
	{
		if (CPstrcmp(str, needle) >= 0)
			return str;
	}
	return NULL;
}

char *CPstrtok(char *str, const char *delim) // call strchr and strspn
{
	int delim_index = CPstrcspn(str, delim);
	char *str_token = CPstrpbrk(str, delim);;
	str[delim_index] = 0;
	return str;
}

void test_strlen()
{
	char *name = "Christian";
	require(CPstrlen("") == 0);
	require(CPstrlen("hello") == 5);
	require(CPstrlen(name) == 9);
}

void test_strcmp()
{
	char *str1 = "sorry", *str2 = "not", *str3 = "sorry";
	require(CPstrcmp(str1, str3) == 0);
	require(CPstrcmp(str2, str1) < 0);
	require(CPstrcmp(str3, str2) > 0);
}

void test_strncmp()
{
	char *str1 = "Hello", *str2 = "Helen", *str3 = "Christian";
	require(CPstrncmp(str1, str2, 3) == 0);
	require(CPstrncmp(str1, str2, 4) > 0);
	require(CPstrncmp(str3, str2, 1) < 0);
}

void test_strspn()
{
	char *str1 = "Christian", *str2 = "Chris", *str3 = "Alright", *str4 = "All";
	require(CPstrspn(str1, str2) == 5);
	require(CPstrspn(str1, str3) == 0);
	require(CPstrspn(str2, str3) == 0);
	require(CPstrspn(str3, str4) == 2);
}

void test_strcspn()
{
	char *str1 = "command", *str2 = "wall", *str3 = "air", *str4 = "well";
	require(CPstrcspn(str1, str2) == 4);
	require(CPstrcspn(str1, str3) == 4);
	require(CPstrcspn(str2, str3) == 1);
	require(CPstrcspn(str3, str4) == 3);
}

void test_strchr()
{
	char str1[] = "Sorry Not Sorry";
	char *str2, *str3, *str4; 
	str2 = CPstrchr(str1, 'N');
	str3 = CPstrchr(str1, 'S');
	require(CPstrcmp(str2, "Not Sorry") == 0);
	require(CPstrcmp(str3, "Sorry Not Sorry") == 0);
	require(CPstrchr(str1, 'u') == NULL);
	
}

void test_strrchr()
{
	char str1[] = "What do you mean?";
	char* str2, *str3, *str4;
	str2 = CPstrrchr(str1, 'y');
	str3 = CPstrrchr(str1, 'd');
	require(CPstrcmp(str2, "you mean?") == 0);
	require(CPstrcmp(str3, "do you mean?") == 0);
	require(CPstrrchr(str1, 'b') == NULL);
}

void test_strcpy()
{
	char *src1  = "Hello", *src2 = "World";
	char dest1[20], dest2[20];
	CPstrcpy(dest1, src1);
	CPstrcpy(dest2, dest1);
	CPstrcpy(dest2, src2);
	require(CPstrcmp(dest1, "Hello") == 0);
	require(CPstrcmp(dest2, "World") == 0);	
	CPstrcpy(dest2, "People");
	require(CPstrcmp(dest2, "People") == 0);
}

void test_strncpy()
{
	char *src1 = "Christian", *src2 = "Tommy", *src3 = "Poon";
	char dest1[10], dest2[10], dest3[10];
	CPstrncpy(dest1, src1, 5);
	CPstrncpy(dest2, src2, 3);
	CPstrncpy(dest3, src3, 1);
	require(CPstrcmp(dest1, "Chris") == 0);
	require(CPstrcmp(dest2, "Tom") == 0);
	require(CPstrcmp(dest3, "P") == 0);	
}

void test_strcat()
{
	char dest1[100] = "Computer ", dest2[100] = "I am a ", dest3[100] = "All of ";
	char *src1 = "Science", *src2 = "Leader in ", *src3 = "Me";
	CPstrcat(dest1, src1);
	CPstrcat(dest2, src2);
	CPstrcat(dest3, src3);
	require(CPstrcmp(dest1, "Computer Science") == 0);
	require(CPstrcmp(dest2, "I am a Leader in ") == 0);	
	require(CPstrcmp(dest3, "All of Me") == 0);
}

void test_strncat()
{
	char dest1[100] = "All my friends ", dest2[100] = "You are a happy ";
	char *src1 = "are kind yet mean", *src2 = "individual", *src3 = " and fun";
	CPstrncat(dest1, src1, 8);
	CPstrncat(dest2, src2, 10);
	require(CPstrcmp(dest1, "All my friends are kind") == 0);
	require(CPstrcmp(dest2, "You are a happy individual") == 0);
	CPstrncat(dest1, src3, 8);
	require(CPstrcmp(dest1, "All my friends are kind and fun") == 0);
}

void test_strpbrk()
{
	char src1[100] = "I do not know what to do";
	char src2[100] = "kwah";
	char src3[100] = "climbing";
	char *str1;
	char *str2;
	str1 = CPstrpbrk(src1, src2);
	str2 = CPstrpbrk(src1, src3);
	require(CPstrcmp(str1, "know what to do") == 0);
	require(CPstrcmp(str2, "not know what to do") == 0);
	require(CPstrpbrk(src2, src3) == NULL);
}

void test_strstr()
{
	char haystack1[10] = "Soulstar", haystack2[10] = "Daydream";
    char needle1[10] = "Soul", needle2[10] = "star";
	char needle3[10] = "Day",  needle4[10] = "dream";
   	char *str1, *str2,  *str3, *str4;
   	str1 = CPstrstr(haystack1, needle1);
	str2 = CPstrstr(haystack1, needle2);
	str3 = CPstrstr(haystack2, needle3);
	str4 = CPstrstr(haystack2, needle4);
	require(CPstrcmp(str1, "Soulstar") == 0);
	require(CPstrcmp(str2, "star") == 0);
	require(CPstrcmp(str3, "Daydream") == 0);
	require(CPstrcmp(str4, "dream") == 0);
}

void test_strtok()
{
	char str1[50] = "This is me", str2[50] = "We-are-young", str3[50] = "Can't see";
    char *delim = " -'";
    char *token1 = CPstrtok(str1, delim);
	char *token2 = CPstrtok(str2, delim);
	char *token3 = CPstrtok(str3, delim);
	require(CPstrcmp(str1, "This") == 0);
	require(CPstrcmp(str2, "We") == 0);
	require(CPstrcmp(str3, "Can") == 0);
}

int main()
{
	test_strlen();
	test_strcmp();
	test_strncmp();
	test_strspn();
	test_strcspn();
	test_strchr();
	test_strrchr();	
	test_strcpy();	
	test_strncpy();
	test_strcat();
	test_strncat();
	test_strpbrk();
	test_strstr();
	test_strtok();

	return 0;
}



