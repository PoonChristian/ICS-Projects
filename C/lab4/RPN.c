#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int array_number[1024];
char RPE[1024];
char number[1024];
int index_array = 0;

void get_operator()
{
    int value;
    switch (number[0])
    {
        case '*':
            value = array_number[index_array - 1] * array_number[index_array - 2];
            index_array -= 2;
            array_number[index_array++] = value;
            break;
        case '/':
            value = array_number[index_array - 2] / array_number[index_array - 1];
            index_array -= 2;
            array_number[index_array++] = value;
            break;
        case '+':
            value = array_number[index_array - 2] + array_number[index_array - 1];
            index_array -= 2;
            array_number[index_array++] = value;
            break;
        case '-':
            value = array_number[index_array - 2] + array_number[index_array - 1];
            index_array -= 2;
            array_number[index_array++] = value;
            break;
        case 's':
            value = array_number[index_array - 1];
            array_number[index_array - 1] = array_number[index_array - 2];
            array_number[index_array - 2] = value;
            break;
        case 'p':
            printf("%d\n", array_number[index_array - 1]);
            break;
        case 'd':
            array_number[index_array++] = array_number[index_array - 1];
            break;
        default:
            value = atoi(number);
            array_number[index_array++] = value;
            break;   
    }
}

void convert_number(int index)
{
    if (index == 1)
        get_operator();
    else if (index > 1)
    {
        int value = atoi(number);
        array_number[index_array++] = value;
    }
        
}

int reset(int index)
{
    memset(number, 1024, index);
    return 0;
}

int getnumbers()
{
    int i = 0;
    int index = 0;
    while (RPE[i] != '\0')
    {
        switch (RPE[i])
        {
            case ' ':
                convert_number(index);
                index = reset(index);
                i++;
                break;
            default:
                number[index++] = RPE[i++];
                break;
        }
    }
    return index;
}

int main()
{
    int index;
    scanf("%[^\n]%*c", RPE);
    index = getnumbers();
    convert_number(index);
    return 0;
}
