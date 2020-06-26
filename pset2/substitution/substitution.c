#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string toUpperCase();
int onlyLetters();
int len();
int unique();
string toCipher();

int main(int argc, string argv[])
{
    string key = argv[1];

    //Checks for single command-line argument
    if (argc != 2 || key == NULL)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (onlyLetters(key) == 1 || len(key) == 1 || unique(key) == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string s = get_string("plaintext: ");
    printf("ciphertext: %s\n", toCipher(s, key));
    return 0;
}

//converting each character of the string to uppercase
//to avoid checking for both lowercase key is converted to uppercase
string toUpperCase(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        x[i] = toupper(x[i]);
    }
    return x;
}

//checks if all the characters in the key are alpha
int onlyLetters(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        if (!isalpha(x[i]))
        {
            return 1;
        }
    }
    return 0;
}

int len(string x)
{
    if (strlen(x) != 26)//making sure the key is exactly 26 characters long.
    {
        return 1;
    }
    return 0;
}

int unique(string x)
{
    string y = toUpperCase(x);
    int c = 0;

    //Function loops through the alphabet checking each character of the key as it goes.
    for (char currentChar = 'A'; currentChar <= 'Z'; currentChar++)
    {
        for (int i = 0; i < strlen(y); i++)
        {
            //If the key contains the current letter, it incriments the counter variable (containsLetter) and then moves on to the next letter.
            if (currentChar == y[i])
            {
                c++;
                //Break statement is essential as once it see's a character in the key it stops and moves on to the next alphabetic character, this checks for duplicate letters within the key.
                break;
            }
        }
    }

    //If the counter was successfully incremented to 26 i.e it contains each letter once and only once, result is then assigned true and returned.
    if (c != 26)
    {
        return 1;
    }
    return 0;
}

string toCipher(string s, string key)
{
    string cipher = s;

    for (int i = 0; i < strlen(cipher); i++)
    {
        //If block to ignore punctuation.
        if (!isalpha(s[i]))
        {
            //DO NOTHING
        }
        //Checks if the plaitext is a capital letter, if so it takes off 65 to get the index to 0 and assigns the corresponding key value to the ciphertext.
        if (s[i] >= 65 && s[i] <= 90)
        {
            cipher[i] = key[s[i] - 65];
        }
        //Same as previous step but for lowercase letters. Takes off 97 this time and then converts the assigned character to lowercase as the key is all uppercase characters.
        if (s[i] >= 97 && s[i] <= 122)
        {
            cipher[i] = key[s[i] - 97];
            cipher[i] = tolower(cipher[i]);
        }
    }
    return cipher;
}