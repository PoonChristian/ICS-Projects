#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void getNumbers(char number[128], int numbers[128], int* num_len)
{
	while (1)
	{
		fgets(number, 128, stdin);
		number[strcspn(number, "\n")] = '\0';
		if (number[0] == '\0')
			break;
		else if (!(isdigit(number[0])))
			continue;
		else
		{
			int current_num = atoi(number);
			numbers[*num_len] = current_num;
			*num_len += 1;
		}
	}	
}

void generate_product_arrays(int numbers[128], int products_below[128], int products_above[128], int num_len)
{
	int product;

	product = 1;
	for (int i = 0; i < num_len; ++i)
	{
		products_below[i] = product;
		product *= numbers[i];
	}

	product = 1;
	for (int i = num_len - 1; i >= 0; --i)
	{
		products_above[i] = product;
		product *= numbers[i];
	}	
}

void print_final_products(int products[128], int products_below[128], int products_above[128], int num_len)
{
	for (int i = 0; i < num_len; ++i)
	{
		products[i] = products_below[i] * products_above[i];
		printf("%d\n", products[i]);
	}	
}

int main()
{
	char number[128];
	int numbers[128];
	int num_len = 0;

	getNumbers(number, numbers, &num_len);

	int products[128];
	int products_below[128];
	int products_above[128];
	
	generate_product_arrays(numbers, products_below, products_above, num_len);
	print_final_products(products, products_below, products_above, num_len);

	return 0;
}
