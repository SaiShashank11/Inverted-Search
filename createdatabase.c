#include "inverted_search.h"
int create_database(Flist *f_head, Hash_t *hashTable)
{
Flist *temp = f_head;

    while(temp)
    {
        FILE *fptr = fopen(temp->arr, "r");

        if(fptr == NULL)
        {
            printf("ERROR: Unable to open %s\n", temp->arr);
            return FAILURE;
        }

        char word[100];

        while(fscanf(fptr, "%99s", word) != EOF)
        {
            int index;
            /* Find hash index */
            if(isalpha(word[0]))
                index = tolower(word[0]) - 'a';
            else
                index = 26;

            // printf("word = %s, Index = %d\n", word, index);

            /* Search word in Mlist */
            Mlist *mtemp = hashTable[index].link;
            while(mtemp)
            {
                if(strcmp(mtemp->word, word) == 0)
                    break;
                mtemp = mtemp->link;
            }

            /*  ***** CASE 1: Word does NOT exist *****  */

            if(mtemp == NULL)
            {
                Mlist *newM = malloc(sizeof(Mlist));

                if(newM == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                newM->word = malloc(strlen(word) + 1);

                if(newM->word == NULL)
                {
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(newM->word, word);

                newM->fileCount = 1;

                /* Create first Slist node */
                Slist *newS = malloc(sizeof(Slist));

                if(newS == NULL)
                {
                    free(newM->word);
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }

                newS->fileName = malloc(strlen(temp->arr) + 1);

                if(newS->fileName == NULL)
                {
                    free(newS);
                    free(newM->word);
                    free(newM);
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(newS->fileName, temp->arr);

                newS->wordCount = 1;
                newS->link = NULL;

                newM->sublink = newS;

                /* Insert Mlist node at beginning */
                newM->link = hashTable[index].link;
                hashTable[index].link = newM;
            }

            /*  ***** CASE 2: Word already exists *****  */

            else
            {
                /* Search filename in Slist */
                Slist *stemp = mtemp->sublink;
                while(stemp != NULL)
                {
                    if(strcmp(stemp->fileName, temp->arr) == 0)
                        break;
                    stemp = stemp->link;
                }

                /* Same word + same file */
                if(stemp != NULL)
                    stemp->wordCount++;

                /* Same word + different file */
                else
                {
                    Slist *newS = malloc(sizeof(Slist));

                    if(newS == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }

                    newS->fileName = malloc(strlen(temp->arr) + 1);

                    if(newS->fileName == NULL)
                    {
                        free(newS);
                        fclose(fptr);
                        return FAILURE;
                    }

                    strcpy(newS->fileName, temp->arr);

                    newS->wordCount = 1;
                    newS->link = NULL;

                    /* Insert Slist node at beginning */
                    newS->link = mtemp->sublink;
                    mtemp->sublink = newS;

                    /* New file contains this word */
                    mtemp->fileCount++;
                }
            }
        }

        fclose(fptr);
        temp = temp->link;
    }
    return SUCCESS;
}
