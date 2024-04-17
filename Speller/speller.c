// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

//global variables
int word_count = 0;

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
    char buff[LENGTH + 1];
    strcpy(buff, word);

    //hash word to get key
    int key = 0;
    key = hash(buff);
    //traverse table[key] list to check IF word exists ? return TRUE : return FALSE
    node *cursor = table[key];
    while (cursor != NULL)
    {
        int result = strcasecmp(buff, cursor->word);
        if (result == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Get first character of string
    char c = word[0];
    //convert To lower
    c = tolower(c);
    //Minus ASCII value to equate index (e.1 A (97))  return = letter – a(97) z – a = 25
    int key = (int)c - 97;

    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open the "dictionaries/large or small" file for reading, to store the dictionary into a hash table
    FILE *pdict = NULL;
    pdict = fopen(dictionary, "r");
    //check NULL
    if (pdict == NULL)
    {
        return false;
    }

    int key = 0;

    //loop through every word in the dictionary
    char buff[LENGTH + 1];
    while (fscanf(pdict, "%s", buff) != EOF)
    {


        //create new node
        node *n = (node *)malloc(sizeof(node));
        //check NULL
        if (n == NULL)
        {
            return false;
        }

        //copy buff to n->word
        strcpy(n->word, buff);

        //set n->next to NULL
        n->next = NULL;

        //hash word
        key = hash(buff);

        //IF table[hash] is empty ? add node : insert node at head
        if (table[key] == NULL)
        {
            //add node
            table[key] = n;
            word_count++;
        }
        else
        {
            //insert node
            //point new_node to head->next
            n->next = table[key];
            //point head->next to new_node
            table[key] = n;
            word_count++;
        }
    }

    //close read
    fclose(pdict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    //loop though all elements in table[N]
    for (int i = 0; i < N; i++)
    {

        //set cursor to 1st node
        node *cursor = table[i];
        node *temp = table[i];

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }

    }
    return true;
}

