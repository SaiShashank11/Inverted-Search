#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define FILE_EXISTS -2

// File list node
typedef struct node{
    char *arr;
    struct node *link;
}Flist;

// Sub node
typedef struct sub_node{
    int wordCount;
    char *fileName;
    struct sub_node *link;
}Slist;

// Main node
typedef struct main_node{
    int fileCount;
    char *word;
    struct main_node *link; 
    Slist *sublink;
}Mlist;

// Hash table
typedef struct hash_table{
    int index;
    Mlist *link;
}Hash_t;


/* File validation and insertion */
int read_and_validation(int argc, char **argv, Flist **head);
int insert_fileName(char *fileName, Flist **head);

/* Database operations */
int create_database(Flist *f_head, Hash_t *hashTable);
int display_database(Hash_t *hashTable);
int search_database(Hash_t *hashTable);
int save_database(Hash_t *hashTable);
int update_database(Hash_t *hashTable, Flist **head);

/* Utility functions */
int file_exists(Flist *head, char *fileName);

/* Memory cleanup */
void free_flist(Flist **head);
void free_database(Hash_t *hashTable);

#endif