// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // lower case first

    char *tmpword = malloc(LENGTH + 1);

    strcpy (tmpword, word);

    for (int i = 0; i < strlen(word); i++)
    {
        tmpword[i] = tolower(word[i]);
    }

    // check hash number

    int hash_number = hash(tmpword);

    // check dictionary

    node *tmp = table[hash_number];

    if (tmp != NULL)
    {
        while (tmp != NULL)
        {
            
            if (strcmp(tmpword, tmp->word) == 0)
                {
                    free(tmpword);
                    return true;
                }
            tmp = tmp->next;
        }
    }
    free(tmpword);
    return false;
}

// TODO Hashes word to a number

unsigned int hash(const char *word)
{

    if (N == 26)
    {
        return toupper(word[0]) - 'A';
    }
    if (N == 26 * 26)
    {
        if (word[1] == '\0')
        {
            return toupper(word[0]) - 'A';
        }
        return toupper(word[0]) - 'A' + toupper(word[1]) - 'A';
    }

    if (N == 26 * 26 * 26)
    {
        if (word[1] == '\0')
        {
            return toupper(word[0]) - 'A';
        }
        if (word[2] == '\0')
        {
            return toupper(word[0]) - 'A' + toupper(word[1]) - 'A';
        }
        return toupper(word[0]) - 'A' + toupper(word[1]) - 'A' + toupper(word[1]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // open dictionary

    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("failed to open dict");
        fclose(dict);
    }

    char *buffer = malloc(LENGTH + 1);

    if (buffer == NULL)
    {
        return false;
    }

    // buffer = NULL;

    // scan for each line

    while (fscanf(dict, "%s", buffer) != EOF)
    {
        for (int i = 0; i < LENGTH; i++)
        {
            // printf("%c", buffer[i]);

            // check hash number

        }

        // printf("%s\n", buffer);

        int hash_number = hash(buffer);
        // printf("%i\n", hash_number);

        // insert into hash table then linked list

        node *bufferfornode = malloc(sizeof(node));

        if (bufferfornode == NULL)
        {
            free(bufferfornode);
            return false;
        }

        strcpy(bufferfornode->word, buffer);

        // linked list

        if(table[hash_number] == NULL)
        {
            table[hash_number] = bufferfornode;
        }
        else
        {
            bufferfornode->next = table[hash_number];
            table[hash_number] = bufferfornode;
        }


    }
    // printf("%s\n", table[2]->word);
    // printf("%s\n", table[2]->next->word);

    // free(bufferfornode);
    free(buffer);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    int count_of_word = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        count_of_word ++;
    }
    // printf("%i\n", count_of_word);
    return count_of_word;

    if (count_of_word == 0)
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // free(table[1]->next);

        if (table[i] == NULL)
        {
            free(table[i]);
        }
        else
        {
            node *tmp = table[i];
            while (tmp != NULL)
            {
                node *tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2);
            }

        }
    }
    return true;
}
