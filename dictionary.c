// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 18276;

// Hash table
node *table[N];

//dict size
int DictSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashLocation = hash(word);
    if(table[hashLocation] == NULL)
    {
        return false;
    }
    node *cursor = table[hashLocation];
    while(cursor != NULL)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
            break;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hashValue = 0;
    //int strlength = strlen(word);
    for(int i = 0; i < strlen(word); i++)
    {
        if(i > strlen(word) / 2)
        {
            if(word[i] == 39)
            {
            continue;
            }
            hashValue += toupper(word[i] - 'A');
        }
        else
        {
            if(word[i] == 39)
            {
                continue;
            }
        hashValue += toupper(word[i]);
        }
        hashValue += 7;
    }
    //these ints count how many spaces inbewwten each letter in has table
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    node *ptr = NULL;
    FILE *source = fopen(dictionary, "r");
    if(source == NULL)
    {
        return false;
    }
    while(true)
    {
        if(fscanf(source, "%s", word) == EOF)
        {
            break;
        }
        node *wordNode = malloc(sizeof(node));
        if(wordNode == NULL)
        {
            return false;
        }
        int tableLocation = hash(word);

        strcpy(wordNode->word, word);
        wordNode->next = NULL;
        if(table[tableLocation] == NULL)
        {
            table[tableLocation] = wordNode;
        }
        else
        {
            wordNode->next = table[tableLocation];
            table[tableLocation] = wordNode;
        }
        DictSize += 1;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(DictSize == 0)
    {
        return 0;
    }
    else
    {
        return DictSize;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *tmp = table[i];
        //loop through all hash tables freeing memory
        while(head != NULL)
        {
            tmp = head;
            head = tmp->next;
            free(tmp);
        }
    }
    return true;
}

