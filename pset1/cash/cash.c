#include<stdio.h>
#include<math.h>
#include<cs50.h>

int main(void)
{
    int c = 0, x, y, z;
    float dollar = 0.00;
    
    do
    {
        dollar = get_float("Change owed: ");
    }
    while (dollar <= 0.00);
    
    //converting dollar into cents
    int cents = round(dollar * 100);
    
    // while quarter can be used
    while (cents >= 25)
    {
        c++;
        cents -= 25;
    }

    // while dimes can be used
    while (cents >= 10)
    {
        c++;
        cents -= 10;
    }

    // while nickels can be used
    while (cents >= 5)
    {
        c++;
        cents -= 5;
    }

    // while pennies can be used
    while (cents >= 1)
    {
        c++;
        cents -= 1;
    }
    
    printf("%i\n", c);
    
}