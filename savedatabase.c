#include "inverted_search.h"
int save_database(Hash_t *hashTable){

    char fileName[100];
    printf("Enter the file name to save database: ");
    scanf("%99s", fileName);

    FILE *fptr = fopen(fileName, "w");

    if(fptr == NULL)
        {
            printf("ERROR: Unable to open database.txt\n");
            return FAILURE;
        }
    
    for(int i = 0; i < 27; i++)
    {

        Mlist *mtemp = hashTable[i].link;
        while(mtemp)
        {
            fprintf(fptr, "#[%d];%s;%d;", i, mtemp->word, mtemp->fileCount);

            Slist *stemp = mtemp->sublink;
            while(stemp)
            {
                fprintf(fptr, "%s;%d", stemp->fileName, stemp->wordCount);
                stemp = stemp->link;
            }
            fprintf(fptr, "#\n");
            mtemp = mtemp->link;
        }
    }

    fclose(fptr);
    
    printf("INFO: Database saved successfully\n");

    return SUCCESS;
}