#include "inverted_search.h"

int display_database(Hash_t *hashTable)
{
    printf("\n***** DATABASE *****\n");

    for(int i = 0; i < 27; i++)
    {
        /* Check whether this index contains Mlist */
        if(hashTable[i].link == NULL)
            continue;

        Mlist *mtemp = hashTable[i].link;

        while(mtemp)
        {
            printf("\n[%d] [%s] -> %d files\n", i, mtemp->word, mtemp->fileCount);
            Slist *stemp = mtemp->sublink;

            while(stemp)
            {
                printf("\tfile : %s : %d times\n", stemp->fileName, stemp->wordCount);
                stemp = stemp->link;
            }
            mtemp = mtemp->link;
        }
    }

    return SUCCESS;
}