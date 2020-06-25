#include<stdio.h>
#include<math.h>
#include<cs50.h>
#include<stdlib.h>

int main(void)
{
    long n = 0;
    do
    {
        n = get_long("Number: ");
    }
    while (n <= 0);

    //copy of the card number to be used
    long temp = n;

    //counter for counting number of digits in the card number
    int c = 0;

    //counting number of digits in the card number
    while (temp > 0)
    {
        temp = temp / 10;
        c++;
    }

    //if the entered number doesnt have right number of digits then declare invalid
    if (c != 13 && c != 15 && c != 16)
    {
        printf("INVALID\n");
        exit(0);
    }

    temp = n;

    //isolating the first two digit of the card number and storing it in variable id
    while (temp > 100)
    {
        temp = temp / 10;
    }

    int id = temp;

    // Print the type of credit card depending on the company ID and amount of digits.

    if (id > 50 && id < 56 && c == 16)
    {
        printf("MASTERCARD\n") ;
    }
    else if ((id == 34 || id == 37) && (c == 15))
    {
        printf("AMEX\n") ;
    }
    else if ((id / 10 == 4) && (c == 13 || c == 16))
    {
        printf("VISA\n") ;
    }
    else
    {
        printf("INVALID\n");
        exit(0);
    }

    //validating luhns algo
    int sum = 0;
    temp = n;

    for (int i = 1; i <= c; i++)
    {
        int d = temp % 10;
        if (i % 2 == 0)
        {
            if (d * 2 > 9)
            {
                sum += (d * 2) - 9;
            }
            else
            {
                sum += d * 2;
            }
        }
        else
        {
            sum += d;
        }
        temp = temp / 10;
    }

    // Checking the validity of the number according to Luhn's algorithm

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
}