#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    //checking for single command line argument, a non-negative integer
    if (argc != 2 || argv[1] <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    int l = strlen(argv[1]); //length of string
    
    //checking if it is a non numeric key
    for (int i = 0; i < l; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    int k = atoi(argv[1]); //changing from string to integer
    
    string s = get_string("plaintext: "); //get text
    
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(s); i < n; i++) //cipher
    {
        if islower(s[i])
        {
            printf("%c", (((s[i] + k) - 'a') % 26) + 'a');
        }
        else if isupper(s[i])
        {
            printf("%c", (((s[i] + k) - 'A') % 26) + 'A');
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}