#include "inverted_search.h"

int search_database(Hash_t *hashTable)
{
    char word[100];

    printf("Enter the word to search: ");
    scanf("%99s", word);

    /* Find hash index */
    int index;

    if(isalpha(word[0]))
        index = tolower(word[0]) - 'a';
    else
        index = 26;

    /* Go to that hash bucket */
    Mlist *mtemp = hashTable[index].link;

    /* Search the word in Mlist */ 
    while(mtemp)
    {
        if(strcmp(mtemp->word, word) == 0)
        {
            printf("\n[%s] is found in %d files:\n", mtemp->word, mtemp->fileCount);

            /* Search all files containing this word */
            Slist *stemp = mtemp->sublink;

            while(stemp)
            {
                printf("\t%s : %d times\n", stemp->fileName, stemp->wordCount);
                stemp = stemp->link;
            }

            printf("\n");
            return SUCCESS;
        }
        mtemp = mtemp->link;
    }

    printf("Word '%s' is not present in the database\n", word);

    return SUCCESS;
}