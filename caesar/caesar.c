#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(int n, char c);

int main(int argc, string argv[])
{
    if (argc == 1 || argc >= 3)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    else if (only_digits(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    else
    {
        int key = atoi(argv[1]);
        string plaintext = get_string("text? ");

        char *ciphertext = malloc(strlen(plaintext) + 1);
        if (ciphertext != NULL)
        {
            strcpy(ciphertext, plaintext);
        }

        for (int i = 0, n = strlen(ciphertext); i < n; i++)
        {
            ciphertext[i] = rotate(key, ciphertext[i]);
        }

        // print both
        printf("plaintext:  %s\n", plaintext);
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }

}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return 0;
        }
    }
    return 1;
}

char rotate(int n, char c)
{
    if (islower(c))
    {
        // mapping
        int displacement = n % 26;
        if ((int) c + displacement <= 122)
        {
            char new_c = (int) c + displacement;
            return new_c;
        }
        else
        {
            char new_c = (int) c - 26 + displacement;
            return new_c;
        }
    }
    else if (isupper(c))
    {
        // mapping
        int displacement = n % 26;
        if ((int) c + displacement <= 90)
        {
            char new_c = (int) c + displacement;
            return new_c;
        }
        else
        {
            char new_c = (int) c + displacement - 26;
            return new_c;
        }
    }

    else
    {
        return c;
    }
}