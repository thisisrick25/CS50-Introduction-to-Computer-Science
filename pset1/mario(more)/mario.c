#include<stdio.h>
#include<cs50.h>

int main(void)
{
    //input height
    int a = get_int("Height: ");
    while (!(a > 0 && a < 9))
    {
        a = get_int("Height: ");
    }
    //generating pattern
    for (int i = 1; i <= a; i++)
    {
        for (int j = a - 1; j >= i; j--)
        {
            printf(" ");
        }

        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
