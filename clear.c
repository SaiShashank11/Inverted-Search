#include"inverted_search.h"
void free_flist(Flist **head)
{
    Flist *temp;
    while(*head){
        temp = *head;
        *head = (*head)->link;

        free(temp->arr);
        free(temp);
    }
}



void free_database(Hash_t *hashTable)
{
    for(int i = 0; i < 27; i++)
    {
        Mlist *mtemp = hashTable[i].link;

        while(mtemp)
        {
            Mlist *mnext = mtemp->link;
            Slist *stemp = mtemp->sublink;

            while(stemp)
            {
                Slist *snext = stemp->link;

                free(stemp->fileName);
                free(stemp);

                stemp = snext;
            }

            free(mtemp->word);
            free(mtemp);

            mtemp = mnext;
        }

        hashTable[i].link = NULL;
    }
}