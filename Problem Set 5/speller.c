// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// counting the number of nodes;
unsigned long int node_count = 0;
unsigned long int *count_ptr = &node_count;

// Hash table
node *table[N];

void init_hash_table();

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    long int index = hash(word);
    
    node *index_ptr =  NULL;
    
    int wordlength = strlen(word);//store length of word
    char* dup = malloc((wordlength + 1) * sizeof(char));
    
    for (int i = 0; i <= wordlength; i++)
    {
        dup[i] = word[i];
    }
    
    index_ptr = table[index];
    
    while(index_ptr != NULL)
    {
        if (strcasecmp(index_ptr->word, dup) == 0)
        {
            free(dup);
            return true;
        }
        
        index_ptr = index_ptr->next;
    }
    free(dup);
    return false;
}

// Hashes word to a number
// Inspired by Engineering Man on YouTube
// Video link: https://www.youtube.com/watch?v=wg8hZxMRwcw&t=369s
unsigned int hash(const char *word)
{
    unsigned long int value = 1;
    unsigned int i = 0;
    unsigned int key = strlen(word);
    
    // making a duplicate to change the string to upper case
    char *duplicate = malloc(key + 1);
    strcpy(duplicate, word);
    
    for(; i < key; i++)
    {
        duplicate[i] = toupper(duplicate[i]);
        value = value * 59 + duplicate[i];
    }
    
    value = value % N;
    free(duplicate);
    return value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        return 1;
    }
    
    //setting all pointers to NULL
    init_hash_table();
    
    char tmp_word[LENGTH];
    char *tmp_word_ptr = &tmp_word[0];
    while(true)
    {
        node *ptr = malloc(sizeof(node));
        int end = fscanf(dict, "%s", tmp_word);
        if (end == EOF)
        {
            free(ptr);
            fclose(dict);
            return true;
        }
        
        if (ptr == NULL)
        {
            unload();
            return false;
        }
        
        strcpy(ptr->word, tmp_word_ptr);
        
        
        int hash_num = hash(tmp_word_ptr);
        
        if (table[hash_num] == NULL)
        {
            table[hash_num] = ptr;
            (*count_ptr)++;
            table[hash_num]->next = NULL;
        }
        else 
        {
            ptr->next = table[hash_num];
            table[hash_num] = ptr;
            (*count_ptr)++;
        }
    }
    fclose(dict);
    return 0;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return *count_ptr;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;
    for (int i = 0; i <= N; i++)
    {
        tmp = table[i];
        if (table[i] != NULL)
        {
            if (table[i]->next == NULL)
            {
                free(tmp);
            }
            
            else
            {
                cursor = table[i]->next;    
                while (cursor != NULL)
                {
                    free(tmp);
                    tmp = cursor;
                    cursor = cursor->next;
                }
            }
        }
    }
    return true;
}

// Set hash table pointers to NULL initially
void init_hash_table()
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}
