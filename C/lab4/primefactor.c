#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int prime_array[100];
int pos = 0;

void factor(int number)
{
    int divisor = 2;
    while (number != 1)
    {
        if (number % divisor == 0)
        {
            number /= divisor;
            prime_array[pos++] = divisor;
        }
        else
        {
            divisor++;
        }
    }
}

void print_factorization(int number)
{
    int count = 0;
    printf("Prime factorization of %d is ", number);
    while (count != pos)
    {
        printf("%d ", prime_array[count++]);
        if (count != pos)
        {
            printf("x ");
        }
    }
    printf("\n");
}

int main()
{
    char input[28];
    while (1)
    {
        fgets(input, 28, stdin);
        input[strcspn(input, "\n")] = '\0';
        if (input[0] == '\0')
            break;
        else
        {
            int number = atoi(input);
            factor(number);
            print_factorization(number);
            pos = 0;
        }
    }

    return 0;
}
