#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters();
int count_words();
int count_sent();
void grade();

int c, x;

int main(void)
{
    string s = get_string("Text: ");

    grade(s);
}

int count_letters(string s)
{
    c = 0;
    x = strlen(s);

    for (int i = 0; i < x; i++)
    {
        if (isalpha(s[i]))
        {
            c++;
        }
    }
    return c;
}

int count_words(string s)
{
    c = 0;
    x = strlen(s);

    for (int i = 0; i < x; i++)
    {
        if ((s[i + 1] == '\0') || (s[i + 1] == ' '))
        {
            c++;
        }
    }

    return c;
}

int count_sent(string s)
{
    c = 0;
    x = strlen(s);

    for (int i = 0; i < x; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            c++;
        }
    }

    return c;
}

void grade(string s)
{
    float L = (float)count_letters(s) / (float)count_words(s) * 100, S = (float)count_sent(s) / (float)count_words(s) * 100;
    float g = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(g);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}